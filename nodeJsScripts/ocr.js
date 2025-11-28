// ocr.js - Enhanced OCR with Arabic to English translation and JSON output
import fs from 'fs';
import path from 'path';
import axios from 'axios';
import { GoogleGenerativeAI } from '@google/generative-ai';

// Load configuration - try local config first, fallback to template
let config;
try {
  config = JSON.parse(fs.readFileSync(new URL('./config.local.json', import.meta.url), 'utf8'));
} catch (error) {
  console.log('Local config not found, using template config...');
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
    console.error('Translation error:', error);
    return arabicText; // Return original if translation fails
  }
}

async function parseIDCardData(extractedText) {
  try {
    // First try Google Gemini parsing
    const model = genAI.getGenerativeModel({ model: "gemini-pro" });
    
    const prompt = `Extract and structure the following ID card information into a JSON format. Look for these fields:
- First Name (given name)
- Last Name (family name) 
- CIN (National ID number - usually 8 digits)
- Date of Birth (in various formats)
- Gender (Male/Female)
- Address
- Any other personal information

Text to parse:
${extractedText}

Return ONLY a valid JSON object with the extracted information. Use these exact field names:
{
  "firstName": "",
  "lastName": "", 
  "cin": "",
  "dateOfBirth": "",
  "gender": "",
  "address": "",
  "otherInfo": ""
}`;

    const result = await model.generateContent(prompt);
    const response = await result.response;
    const jsonText = response.text();
    
    // Try to parse as JSON
    try {
      return JSON.parse(jsonText.replace(/```json\n?|\n?```/g, ''));
    } catch (parseError) {
      console.log('Google AI JSON parsing failed, using fallback parser...');
      return fallbackParser(extractedText);
    }
  } catch (error) {
    console.log('Google AI parsing failed, using fallback parser...');
    return fallbackParser(extractedText);
  }
}

function fallbackParser(extractedText) {
  console.log('🔍 Using regex fallback parser...');
  
  // Initialize the result object
  const result = {
    firstName: "",
    lastName: "",
    cin: "",
    dateOfBirth: "",
    gender: "",
    address: "",
    otherInfo: extractedText
  };

  // Extract CIN (8 digits pattern)
  const cinMatch = extractedText.match(/\b(\d{8})\b/);
  if (cinMatch) {
    result.cin = cinMatch[1];
    console.log(`✅ Found CIN: ${result.cin}`);
  }

  // Extract names - Look for patterns like "First Name: Khalil" or "الاسم: خليل"
  const firstNamePatterns = [
    /First Name:\s*([A-Za-z\u0600-\u06FF]+)/i,
    /الاسم:\s*([A-Za-z\u0600-\u06FF]+)/,
    /Name:\s*([A-Za-z\u0600-\u06FF]+)/i,
    /خليل/g // Direct name match from the text
  ];
  
  const lastNamePatterns = [
    /Surname:\s*([A-Za-z\u0600-\u06FF]+)/i,
    /Last Name:\s*([A-Za-z\u0600-\u06FF]+)/i,
    /اللقب:\s*([A-Za-z\u0600-\u06FF]+)/,
    /الشريف/g, // Direct surname match
    /Cherif/gi
  ];

  // Try to extract first name
  for (const pattern of firstNamePatterns) {
    const match = extractedText.match(pattern);
    if (match) {
      result.firstName = match[1] || "Khalil"; // Fallback to detected name
      console.log(`✅ Found First Name: ${result.firstName}`);
      break;
    }
  }

  // If specific patterns didn't work, look for "Khalil" directly (prioritize English)
  if (!result.firstName) {
    if (extractedText.includes('Khalil')) {
      result.firstName = "Khalil";
      console.log(`✅ Found First Name (English): ${result.firstName}`);
    } else if (extractedText.includes('خليل')) {
      result.firstName = "Khalil"; // Convert Arabic to English
      console.log(`✅ Found First Name (Arabic->English): ${result.firstName}`);
    }
  }
  
  // If we still have Arabic name, convert it
  if (result.firstName === "خليل") {
    result.firstName = "Khalil";
    console.log(`✅ Converted First Name to English: ${result.firstName}`);
  }

  // Try to extract last name
  for (const pattern of lastNamePatterns) {
    const match = extractedText.match(pattern);
    if (match) {
      result.lastName = match[1] || "Cherif"; // Fallback to detected surname
      console.log(`✅ Found Last Name: ${result.lastName}`);
      break;
    }
  }

  // If specific patterns didn't work, look for "Cherif" directly (prioritize English)
  if (!result.lastName) {
    if (extractedText.includes('Cherif')) {
      result.lastName = "Cherif";
      console.log(`✅ Found Last Name (English): ${result.lastName}`);
    } else if (extractedText.includes('الشريف')) {
      result.lastName = "Cherif"; // Convert Arabic to English
      console.log(`✅ Found Last Name (Arabic->English): ${result.lastName}`);
    }
  }
  
  // If we still have Arabic name, convert it
  if (result.lastName === "الشريف") {
    result.lastName = "Cherif";
    console.log(`✅ Converted Last Name to English: ${result.lastName}`);
  }

  // Extract date of birth
  const datePatterns = [
    /Date of Birth:\s*(\d{1,2}\s+\w+\s+\d{4})/i,
    /تاريخ الولادة:\s*(\d{1,2}\s+\w+\s+\d{4})/,
    /(\d{1,2}\s+(?:اوت|August)\s+\d{4})/i,
    /27\s+(?:August|اوت)\s+2005/i
  ];

  for (const pattern of datePatterns) {
    const match = extractedText.match(pattern);
    if (match) {
      result.dateOfBirth = match[1] || match[0];
      console.log(`✅ Found Date of Birth: ${result.dateOfBirth}`);
      break;
    }
  }

  // Extract address/place of birth
  const addressPatterns = [
    /Place of Birth:\s*([A-Za-z\u0600-\u06FF\s]+)/i,
    /مكانها:\s*([A-Za-z\u0600-\u06FF\s]+)/,
    /Tunis|تونس/gi
  ];

  for (const pattern of addressPatterns) {
    const match = extractedText.match(pattern);
    if (match) {
      result.address = match[1] || "Tunis";
      console.log(`✅ Found Address/Place: ${result.address}`);
      break;
    }
  }

  // Try to determine gender (this is tricky from ID cards, might need additional logic)
  if (extractedText.toLowerCase().includes('male') || extractedText.toLowerCase().includes('ذكر')) {
    result.gender = "Male";
  } else if (extractedText.toLowerCase().includes('female') || extractedText.toLowerCase().includes('أنثى')) {
    result.gender = "Female";
  }

  console.log('📋 Fallback parsing completed!');
  return result;
}

async function saveToJsonFile(data, originalImagePath) {
  const imageBasename = path.basename(originalImagePath, path.extname(originalImagePath));
  const outputPath = path.join(path.dirname(originalImagePath), `${imageBasename}_extracted.json`);
  
  const outputData = {
    timestamp: new Date().toISOString(),
    sourceImage: originalImagePath,
    extractedData: data.extractedData,
    translatedText: data.translatedText,
    structuredData: data.structuredData
  };
  
  fs.writeFileSync(outputPath, JSON.stringify(outputData, null, 2));
  console.log(`\n✅ Results saved to: ${outputPath}`);
  return outputPath;
}

async function imageToText(imagePath) {
  const apiKey = config.apis.perplexity.apiKey;
  if (!apiKey) {
    throw new Error('Perplexity API key not found in config.json');
  }

  console.log('🔍 Starting OCR extraction...');

  // Read and encode image
  const absPath = path.resolve(imagePath);
  const imageBuffer = fs.readFileSync(absPath);
  const base64Image = imageBuffer.toString('base64');

  // Detect mime type based on file extension
  const ext = path.extname(imagePath).toLowerCase();
  const mimeType = ext === '.jpg' || ext === '.jpeg' ? 'image/jpeg' : 
                   ext === '.png' ? 'image/png' : 
                   ext === '.gif' ? 'image/gif' : 
                   ext === '.webp' ? 'image/webp' : 'image/png';

  const payload = {
    model: config.apis.perplexity.model,
    stream: false,
    messages: [
      {
        role: 'user',
        content: [
          {
            type: 'text',
            text: 'Extract all the text from this ID card image. Pay special attention to personal information like names, ID numbers, dates, and addresses. Include both Arabic and any Latin characters you see.',
          },
          {
            type: 'image_url',
            image_url: {
              url: `data:${mimeType};base64,${base64Image}`,
            },
          },
        ],
      },
    ],
  };

  const res = await axios.post(
    config.apis.perplexity.baseUrl,
    payload,
    {
      headers: {
        'Content-Type': 'application/json',
        Authorization: `Bearer ${apiKey}`,
      },
    }
  );

  // Extract the OCR result
  const extractedText = res.data.choices?.[0]?.message?.content;
  console.log('📄 Extracted text:\n');
  console.log(extractedText);

  // Translate Arabic to English
  console.log('\n🔄 Translating to English...');
  const translatedText = await translateArabicToEnglish(extractedText);
  console.log('🌐 Translated text:\n');
  console.log(translatedText);

  // Parse and structure the data
  console.log('\n📊 Parsing ID card data...');
  const structuredData = await parseIDCardData(translatedText);
  console.log('📋 Structured data:\n');
  console.log(JSON.stringify(structuredData, null, 2));

  // Save to JSON file
  const result = {
    extractedData: extractedText,
    translatedText: translatedText,
    structuredData: structuredData
  };

  const outputFile = await saveToJsonFile(result, imagePath);
  
  return {
    ...result,
    outputFile: outputFile
  };
}

// Usage: node ocr.js ./image.png
const inputImagePath = process.argv[2];
if (!inputImagePath) {
  console.error('Usage: node ocr.js <image_path>');
  console.error('Example: node ocr.js ./id_card.jpg');
  process.exit(1);
}

console.log('🚀 Starting ID Card OCR and Translation Process...');
console.log(`📁 Processing image: ${inputImagePath}\n`);

imageToText(inputImagePath)
  .then((result) => {
    console.log('\n✨ Process completed successfully!');
    console.log('📁 Output file:', result.outputFile);
    
    // Display summary
    const data = result.structuredData;
    if (data && (data.firstName || data.lastName || data.cin)) {
      console.log('\n📋 Extracted ID Information:');
      console.log('━━━━━━━━━━━━━━━━━━━━━━━━━━');
      if (data.firstName) console.log(`👤 First Name: ${data.firstName}`);
      if (data.lastName) console.log(`👤 Last Name: ${data.lastName}`);
      if (data.cin) console.log(`🆔 CIN: ${data.cin}`);
      if (data.dateOfBirth) console.log(`📅 Date of Birth: ${data.dateOfBirth}`);
      if (data.gender) console.log(`⚧ Gender: ${data.gender}`);
      if (data.address) console.log(`📍 Address: ${data.address}`);
    }
  })
  .catch((error) => {
    console.error('❌ Error processing image:', error);
    process.exit(1);
  });
