// forms_data_extractor.js - Extract detailed registration data for Qt Application
import path from 'node:path';
import fs from 'node:fs/promises';
import { fileURLToPath } from 'node:url';
import { authenticate } from '@google-cloud/local-auth';
import { google } from 'googleapis';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

// Paths
const CREDENTIALS_PATH = path.join(__dirname, 'credentials.json');
const TOKEN_PATH = path.join(__dirname, 'token.json');

// Your form ID
const FORM_ID = '1OqdKpCiUt_VozMOvb7_1Bz59MkM7xNGVQKNBUOOFJwI';

// Scopes needed
const SCOPES = [
  'https://www.googleapis.com/auth/forms.responses.readonly',
  'https://www.googleapis.com/auth/forms.body.readonly',
];

// Question mapping - adjust these based on your actual form structure
const QUESTION_MAPPING = {
  'name': ['name', 'full name', 'your name', 'nom'],
  'email': ['email', 'e-mail', 'email address', 'adresse email'],
  'activity': ['activity', 'preferred activity', 'activité', 'which activity'],
  'phone': ['phone', 'telephone', 'phone number', 'numéro'],
  'age': ['age', 'your age', 'âge']
};

async function loadSavedCredentialsIfExist() {
  try {
    const content = await fs.readFile(TOKEN_PATH);
    const credentials = JSON.parse(content);
    return google.auth.fromJSON(credentials);
  } catch (err) {
    return null;
  }
}

async function saveCredentials(client) {
  const content = await fs.readFile(CREDENTIALS_PATH);
  const keys = JSON.parse(content);
  const key = keys.installed || keys.web;
  const payload = JSON.stringify({
    type: 'authorized_user',
    client_id: key.client_id,
    client_secret: key.client_secret,
    refresh_token: client.credentials.refresh_token,
  });
  await fs.writeFile(TOKEN_PATH, payload);
}

async function authorize() {
  let client = await loadSavedCredentialsIfExist();
  if (client) {
    return client;
  }
  
  console.log('🔐 Starting OAuth flow...');
  client = await authenticate({
    scopes: SCOPES,
    keyfilePath: CREDENTIALS_PATH,
  });
  
  if (client.credentials) {
    await saveCredentials(client);
  }
  
  return client;
}

function findQuestionType(questionTitle, questionMap) {
  const title = questionTitle.toLowerCase();
  
  for (const [type, keywords] of Object.entries(QUESTION_MAPPING)) {
    for (const keyword of keywords) {
      if (title.includes(keyword.toLowerCase())) {
        return type;
      }
    }
  }
  
  return 'unknown';
}

function extractAnswerValue(answer) {
  if (answer.textAnswers && answer.textAnswers.answers) {
    return answer.textAnswers.answers[0]?.value || '';
  }
  return '';
}

async function main() {
  try {
    console.log('🔐 Authenticating with Google APIs...');
    const auth = await authorize();
    console.log('✅ Authentication successful');
    
    const forms = google.forms({ version: 'v1', auth });
    
    console.log('📋 Fetching form structure...');
    // Get form structure first
    const formRes = await forms.forms.get({ formId: FORM_ID });
    
    // Create question mapping
    const questionMap = {};
    const questionTypes = {};
    
    if (formRes.data.items) {
      formRes.data.items.forEach(item => {
        if (item.questionItem && item.questionItem.question) {
          const questionId = item.questionItem.question.questionId;
          const title = item.title || 'Untitled Question';
          questionMap[questionId] = title;
          questionTypes[questionId] = findQuestionType(title, questionMap);
        }
      });
    }
    
    console.log('📊 Form Information:');
    console.log(`Form Title: ${formRes.data.info?.title || 'Event Registration'}`);
    console.log(`Total Questions: ${Object.keys(questionMap).length}`);
    
    // Display question mapping for verification
    console.log('\n📝 Question Analysis:');
    Object.entries(questionMap).forEach(([id, title]) => {
      const type = questionTypes[id];
      console.log(`  ${title} → ${type}`);
    });
    
    console.log('\n📋 Fetching responses...');
    const responsesRes = await forms.forms.responses.list({ formId: FORM_ID });
    
    if (!responsesRes.data.responses) {
      console.log('❌ No responses found');
      // Create empty data file
      const emptyData = {
        formTitle: formRes.data.info?.title || 'Event Registration',
        lastUpdated: new Date().toISOString(),
        totalResponses: 0,
        responses: []
      };
      
      await fs.writeFile('forms_registration_data.json', JSON.stringify(emptyData, null, 2));
      console.log('📄 Empty data file created: forms_registration_data.json');
      return;
    }
    
    // Sort responses chronologically (oldest first)
    const sortedResponses = responsesRes.data.responses.sort((a, b) => {
      return new Date(a.createTime) - new Date(b.createTime);
    });
    
    console.log(`✅ Found ${sortedResponses.length} responses`);
    
    // Process responses into Qt application format
    const processedResponses = sortedResponses.map((response, index) => {
      const registration = {
        sequence: index + 1,
        responseId: response.responseId,
        createTime: response.createTime,
        createTimeReadable: new Date(response.createTime).toLocaleString('en-US', {
          year: 'numeric',
          month: '2-digit',
          day: '2-digit',
          hour: '2-digit',
          minute: '2-digit',
          timeZone: 'UTC'
        }),
        name: '',
        email: '',
        activityType: '',
        phoneNumber: '',
        age: '',
        paymentConfirmed: false
      };
      
      // Extract answers based on question types
      if (response.answers) {
        Object.entries(response.answers).forEach(([questionId, answer]) => {
          const questionType = questionTypes[questionId];
          const value = extractAnswerValue(answer);
          
          switch (questionType) {
            case 'name':
              registration.name = value;
              break;
            case 'email':
              registration.email = value;
              break;
            case 'activity':
              registration.activityType = value;
              break;
            case 'phone':
              registration.phoneNumber = value;
              break;
            case 'age':
              registration.age = value;
              break;
          }
        });
      }
      
      return registration;
    });
    
    // Create final data structure
    const registrationData = {
      formTitle: formRes.data.info?.title || 'Event Registration',
      lastUpdated: new Date().toISOString(),
      totalResponses: processedResponses.length,
      responses: processedResponses
    };
    
    // Save to file
    await fs.writeFile('forms_registration_data.json', JSON.stringify(registrationData, null, 2));
    console.log('📄 Registration data saved to: forms_registration_data.json');
    
    // Display summary
    console.log('\n📊 Registration Summary:');
    console.log(`Total Registrations: ${processedResponses.length}`);
    
    if (processedResponses.length > 0) {
      // Activity type distribution
      const activities = {};
      processedResponses.forEach(reg => {
        if (reg.activityType) {
          activities[reg.activityType] = (activities[reg.activityType] || 0) + 1;
        }
      });
      
      console.log('\n🎯 Activity Distribution:');
      Object.entries(activities).forEach(([activity, count]) => {
        console.log(`  ${activity}: ${count} registrations`);
      });
      
      console.log('\n📋 Sample Registration:');
      const sample = processedResponses[0];
      console.log(`  Name: ${sample.name || 'Not provided'}`);
      console.log(`  Email: ${sample.email || 'Not provided'}`);
      console.log(`  Activity: ${sample.activityType || 'Not provided'}`);
      console.log(`  Phone: ${sample.phoneNumber || 'Not provided'}`);
      console.log(`  Age: ${sample.age || 'Not provided'}`);
      console.log(`  Submitted: ${sample.createTimeReadable}`);
    }
    
    console.log('\n✅ Data extraction complete!');
    console.log('💡 The Qt application will now load this data automatically.');
    
  } catch (error) {
    console.error('❌ Error:', error.message);
    if (error.status === 401) {
      console.log('\n🔧 Authentication failed. Please check your credentials.');
    }
    process.exit(1);
  }
}

main();