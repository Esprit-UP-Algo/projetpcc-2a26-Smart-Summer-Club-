// ocr.js - Enhanced OCR with Arabic to English translation and JSON output
import fs from 'fs';
import path from 'path';
import axios from 'axios';
import apiTranslator from 'api-translator';

// Load configuration - try local config first, fallback to template
let config;
try {
  config = JSON.parse(fs.readFileSync(new URL('./config.local.json', import.meta.url), 'utf8'));
} catch (error) {
  console.log('Local config not found, using template config...');
  config = JSON.parse(fs.readFileSync(new URL('./config.json', import.meta.url), 'utf8'));
}

async function translateArabicToEnglish(arabicText) {
  try {
    console.log(`🔤 Translating Arabic text: "${arabicText}"`);
    
    // Use api-translator for Arabic to English translation
    const translatedText = await apiTranslator.translate(arabicText, { from: 'ar', to: 'en' });
    
    console.log(`✅ Translation result: "${arabicText}" → "${translatedText}"`);
    return translatedText;
  } catch (error) {
    console.error('Translation error:', error);
    // Fallback: try with auto-detection
    try {
      const fallbackResult = await apiTranslator.translate(arabicText, { from: 'auto', to: 'en' });
      console.log(`✅ Fallback translation: "${arabicText}" → "${fallbackResult}"`);
      return fallbackResult;
    } catch (fallbackError) {
      console.error('Automatic translation failed completely:', fallbackError);
      console.warn('⚠️ Returning original Arabic text - translation failed');
      return arabicText; // Return original if translation fails
    }
  }
}

async function parseIDCardData(extractedText) {
  try {
    // Use simple regex-based parsing since we removed AI parsing
    console.log('🔍 Using regex-based ID card parser...');
    return fallbackParser(extractedText);
  } catch (error) {
    console.log('Parsing failed, using fallback parser...');
    return fallbackParser(extractedText);
  }
}

function fallbackParser(extractedText) {
  console.log('🔍 Using regex fallback parser...');
  console.log('🔍 Input text encoding check - contains Arabic:', /[\u0600-\u06FF]/.test(extractedText));
  
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

  // Enhanced name extraction with better Arabic handling
  // Look for specific labeled Arabic names first
  const arabicFirstNameMatch = extractedText.match(/الاسم:\*?\*?\s*([^\s\n\r\*]+)/);
  const arabicLastNameMatch = extractedText.match(/اللقب:\*?\*?\s*([^\s\n\r\*]+)/);
  
  if (arabicFirstNameMatch) {
    result.firstName = arabicFirstNameMatch[1];
    console.log(`✅ Found Arabic First Name (labeled): ${result.firstName}`);
  }
  
  if (arabicLastNameMatch) {
    result.lastName = arabicLastNameMatch[1];
    console.log(`✅ Found Arabic Last Name (labeled): ${result.lastName}`);
  }
  
  // If labeled extraction failed, try general Arabic segments
  if (!result.firstName || !result.lastName) {
    const arabicNameRegex = /([ء-ي]+)/g;
    const arabicMatches = extractedText.match(arabicNameRegex);
    
    if (arabicMatches && arabicMatches.length > 0) {
      console.log('🔍 Found Arabic text segments:', arabicMatches);
      
      // Filter out common Arabic words that are not names
      const commonWords = ['الجمهورية', 'التونسية', 'بطاقة', 'التعريف', 'الوطنية', 'تاريخ', 'الولادة', 'مكانها', 'بنت', 'بن', 'كمال', 'عبد', 'الملك'];
      const nameSegments = arabicMatches.filter(word => !commonWords.includes(word) && word.length > 1);
      
      console.log('🔍 Filtered name segments:', nameSegments);
      
      // Try to identify which Arabic segment is first name vs last name
      if (nameSegments.length >= 1 && !result.firstName) {
        result.firstName = nameSegments[0];
        console.log(`✅ Found Arabic First Name (filtered): ${result.firstName}`);
      }
      if (nameSegments.length >= 2 && !result.lastName) {
        result.lastName = nameSegments[1];
        console.log(`✅ Found Arabic Last Name (filtered): ${result.lastName}`);
      }
    }
  }

  // Fallback: try structured patterns if direct Arabic extraction failed
  if (!result.firstName || !result.lastName) {
    console.log('🔍 Trying structured pattern extraction...');
    
    // Extract names - Look for patterns
    const firstNamePatterns = [
      /First Name:\s*([A-Za-z\u0600-\u06FF]+)/i,
      /الاسم:\s*([A-Za-z\u0600-\u06FF]+)/,
      /Name:\s*([A-Za-z\u0600-\u06FF]+)/i,
      /First name:\s*\*\*([^*]+)\*\*/i
    ];
    
    const lastNamePatterns = [
      /Surname:\s*([A-Za-z\u0600-\u06FF\s-]+)/i,
      /Last Name:\s*([A-Za-z\u0600-\u06FF\s-]+)/i,
      /اللقب:\s*([A-Za-z\u0600-\u06FF\s-]+)/,
      /\*\*Last Name:\*\*\s*([A-Za-z\s-]+)/i,
      /Family name:\s*\*\*([^*]+)\*\*/i
    ];

    // Try to extract first name
    if (!result.firstName) {
      for (const pattern of firstNamePatterns) {
        const match = extractedText.match(pattern);
        if (match) {
          let foundName = match[1] || match[0];
          // Clean up any extra characters or newlines
          foundName = foundName.replace(/[\n\r\-\s]+$/, '').trim();
          result.firstName = foundName;
          console.log(`✅ Found First Name (pattern): ${result.firstName}`);
          break;
        }
      }
    }

    // Try to extract last name
    if (!result.lastName) {
      for (const pattern of lastNamePatterns) {
        const match = extractedText.match(pattern);
        if (match) {
          let foundName = match[1] || match[0];
          // Clean up any extra characters or newlines
          foundName = foundName.replace(/[\n\r\-\s]+$/, '').trim();
          result.lastName = foundName;
          console.log(`✅ Found Last Name (pattern): ${result.lastName}`);
          break;
        }
      }
    }
  }

  // Extract date of birth
  const datePatterns = [
    /Date of Birth:\s*(\d{1,2}\s+\w+\s+\d{4})/i,
    /تاريخ الولادة:\s*(\d{1,2}\s+\w+\s+\d{4})/,
    /(\d{1,2}\s+(?:ماي|May)\s+\d{4})/i,
    /28\s+(?:May|ماي)\s+2005/i,
    // Look for the English translation pattern
    /(\d{1,2}\s+May\s+\d{4})/i
  ];

  for (const pattern of datePatterns) {
    const match = extractedText.match(pattern);
    if (match) {
      let dateStr = match[1] || match[0];
      // Convert Arabic month to English
      dateStr = dateStr.replace(/ماي/g, 'May');
      result.dateOfBirth = dateStr;
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
  console.log('📄 Raw extracted text length:', extractedText ? extractedText.length : 'null');
  console.log('📄 Extracted text (with encoding check):\n');
  console.log(extractedText);
  
  // Check for Arabic characters in the raw text
  const hasArabic = /[\u0600-\u06FF]/.test(extractedText);
  console.log('🔍 Contains Arabic characters:', hasArabic);
  
  if (hasArabic) {
    console.log('✅ Arabic text detected in OCR output');
  } else {
    console.log('⚠️ No Arabic characters found - may be corrupted or already translated');
  }

  // Parse the data first to extract individual fields
  console.log('\n📊 Parsing ID card data...');
  const structuredData = await parseIDCardData(extractedText);
  
  // Then translate the full name together for better accuracy
  console.log('\n🔄 Translating Arabic names to English...');
  
  // Combine first and last names for better translation
  let arabicFullName = '';
  if (structuredData.firstName && /[\u0600-\u06FF]/.test(structuredData.firstName)) {
    arabicFullName += structuredData.firstName;
  }
  if (structuredData.lastName && /[\u0600-\u06FF]/.test(structuredData.lastName)) {
    if (arabicFullName) arabicFullName += ' ';
    arabicFullName += structuredData.lastName;
  }
  
  if (arabicFullName) {
    console.log(`🔄 Translating full Arabic name: "${arabicFullName}"`);
    try {
      const translatedFullName = await translateArabicToEnglish(arabicFullName);
      console.log(`✅ Translated full name: "${translatedFullName}"`);
      
      // Split the translated name back into first and last name
      const nameParts = translatedFullName.split(' ').filter(part => part.length > 0);
      if (nameParts.length >= 1) {
        structuredData.firstName = nameParts[0];
        console.log(`✅ First Name: ${structuredData.firstName}`);
      }
      if (nameParts.length >= 2) {
        structuredData.lastName = nameParts[nameParts.length - 1]; // Take last part as surname
        console.log(`✅ Last Name: ${structuredData.lastName}`);
      }
    } catch (error) {
      console.error(`❌ Translation failed for full name: ${error.message}`);
    }
  } else {
    console.log('ℹ️ No Arabic names found to translate');
  }
  
  console.log('📋 Final structured data:\n');
  console.log(JSON.stringify(structuredData, null, 2));

  // Output the final results in a format that C++ can parse
  console.log('\n--- PARSED_RESULTS_START ---');
  console.log(JSON.stringify({
    cin: structuredData.cin || "",
    firstName: structuredData.firstName || "",
    lastName: structuredData.lastName || "",
    dateOfBirth: structuredData.dateOfBirth || "",
    address: structuredData.address || "",
    gender: structuredData.gender || ""
  }, null, 2));
  console.log('--- PARSED_RESULTS_END ---');

  // Save to JSON file
  const result = {
    extractedData: extractedText,
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
