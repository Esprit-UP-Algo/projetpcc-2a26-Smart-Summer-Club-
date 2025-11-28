// ocr_minimal.js - Minimal OCR script for Qt integration (JSON output only)
import fs from 'fs';
import path from 'path';
import axios from 'axios';
import { GoogleGenerativeAI } from '@google/generative-ai';

// Load configuration - try local config first, fallback to template
let config;
try {
  config = JSON.parse(fs.readFileSync(new URL('./config.local.json', import.meta.url), 'utf8'));
} catch (error) {
  config = JSON.parse(fs.readFileSync(new URL('./config.json', import.meta.url), 'utf8'));
}

// Initialize Google Gemini AI for translation
const genAI = new GoogleGenerativeAI(config.apis.googleGemini.apiKey);

async function translateArabicToEnglish(arabicText) {
  try {
    const model = genAI.getGenerativeModel({ model: "gemini-pro" });
    
    const prompt = `Translate the following Arabic text to English. If there are any personal information fields like names, dates, or ID numbers, preserve their structure and format:

${arabicText}

Please provide a clean English translation.`;

    const result = await model.generateContent(prompt);
    const response = await result.response;
    return response.text();
  } catch (error) {
    return arabicText; // Return original if translation fails
  }
}

async function parseIDCardData(extractedText) {
  try {
    // Try Google Gemini parsing first
    const model = genAI.getGenerativeModel({ model: "gemini-pro" });
    
    const prompt = `Extract and structure the following ID card information into a JSON format. Look for these fields:
- First Name (given name)
- Last Name (family name) 
- CIN (National ID number - usually 8 digits)
- Date of Birth (in various formats)
- Gender (Male/Female)
- Address

Text to parse:
${extractedText}

Return ONLY a valid JSON object with the extracted information. Use these exact field names:
{
  "firstName": "",
  "lastName": "", 
  "cin": "",
  "dateOfBirth": "",
  "gender": "",
  "address": ""
}`;

    const result = await model.generateContent(prompt);
    const response = await result.response;
    let jsonText = response.text();
    
    // Clean up the response to extract just the JSON
    jsonText = jsonText.replace(/```json\n?/g, '').replace(/```\n?/g, '').trim();
    
    try {
      const parsedData = JSON.parse(jsonText);
      return parsedData;
    } catch (parseError) {
      // Fallback to regex parsing
      return fallbackParser(extractedText);
    }
  } catch (error) {
    // Fallback to regex parsing
    return fallbackParser(extractedText);
  }
}

function fallbackParser(text) {
  const result = {
    firstName: '',
    lastName: '',
    cin: '',
    dateOfBirth: '',
    gender: '',
    address: ''
  };

  // Extract CIN (8 digit number)
  const cinMatch = text.match(/\b\d{8}\b/);
  if (cinMatch) {
    result.cin = cinMatch[0];
  }

  // Extract first name (common patterns)
  const firstNamePatterns = [
    /(?:First Name|Given Name|Prénom)[:\s]*([A-Za-zÀ-ÿ\u0600-\u06FF\s]+)/i,
    /(?:Name|Nom)[:\s]*([A-Za-zÀ-ÿ\u0600-\u06FF]+)/i
  ];
  
  for (const pattern of firstNamePatterns) {
    const match = text.match(pattern);
    if (match && match[1]) {
      result.firstName = match[1].trim();
      break;
    }
  }

  // Extract last name
  const lastNamePatterns = [
    /(?:Last Name|Family Name|Surname|Nom de famille)[:\s]*([A-Za-zÀ-ÿ\u0600-\u06FF\s]+)/i,
    /(?:Surname|Nom)[:\s]*([A-Za-zÀ-ÿ\u0600-\u06FF]+)/i
  ];
  
  for (const pattern of lastNamePatterns) {
    const match = text.match(pattern);
    if (match && match[1]) {
      result.lastName = match[1].trim();
      break;
    }
  }

  // Extract date of birth (various formats)
  const dobPatterns = [
    /(?:Date of Birth|DOB|Date de naissance|Né\(e\) le)[:\s]*(\d{1,2}[\/\-\.]\d{1,2}[\/\-\.]\d{4})/i,
    /(?:Birth|Naissance)[:\s]*(\d{1,2}[\/\-\.]\d{1,2}[\/\-\.]\d{4})/i,
    /(\d{1,2}[\/\-\.]\d{1,2}[\/\-\.]\d{4})/
  ];
  
  for (const pattern of dobPatterns) {
    const match = text.match(pattern);
    if (match && match[1]) {
      result.dateOfBirth = match[1];
      break;
    }
  }

  return result;
}

async function imageToText(imagePath) {
  try {
    // Read and encode image
    const imageBuffer = fs.readFileSync(imagePath);
    const base64Image = imageBuffer.toString('base64');

    // Call Perplexity API for OCR
    const response = await axios.post(config.apis.perplexity.baseUrl, {
      model: 'llama-3.2-90b-vision-preview',
      messages: [
        {
          role: 'user',
          content: [
            {
              type: 'text',
              text: 'Extract all visible text from this ID card image. Return ONLY the extracted text, no explanations or formatting.'
            },
            {
              type: 'image_url',
              image_url: {
                url: `data:image/jpeg;base64,${base64Image}`
              }
            }
          ]
        }
      ],
      max_tokens: 1000,
      temperature: 0.1
    }, {
      headers: {
        'Authorization': `Bearer ${config.apis.perplexity.apiKey}`,
        'Content-Type': 'application/json'
      }
    });

    const extractedText = response.data.choices[0].message.content.trim();
    
    // Translate to English if needed
    const translatedText = await translateArabicToEnglish(extractedText);
    
    // Parse and structure the data
    const structuredData = await parseIDCardData(translatedText);
    
    return {
      extractedData: extractedText,
      translatedText: translatedText,
      structuredData: structuredData
    };
    
  } catch (error) {
    throw new Error(`OCR processing failed: ${error.message}`);
  }
}

// Main execution for Qt integration
const inputImagePath = process.argv[2];
if (!inputImagePath) {
  const errorData = {
    error: true,
    message: 'No image path provided',
    cin: '', firstName: '', lastName: '', dateOfBirth: '', gender: '', address: '', rawText: ''
  };
  console.log(JSON.stringify(errorData));
  process.exit(1);
}

imageToText(inputImagePath)
  .then((result) => {
    // Output clean JSON only for Qt integration
    const outputData = {
      error: false,
      cin: result.structuredData.cin || '',
      firstName: result.structuredData.firstName || '',
      lastName: result.structuredData.lastName || '',
      dateOfBirth: result.structuredData.dateOfBirth || '',
      gender: result.structuredData.gender || '',
      address: result.structuredData.address || '',
      rawText: result.extractedData || ''
    };
    
    console.log(JSON.stringify(outputData));
  })
  .catch((error) => {
    // Output error as JSON
    const errorData = {
      error: true,
      message: error.message || 'Unknown error occurred',
      cin: '', firstName: '', lastName: '', dateOfBirth: '', gender: '', address: '', rawText: ''
    };
    console.log(JSON.stringify(errorData));
    process.exit(1);
  });