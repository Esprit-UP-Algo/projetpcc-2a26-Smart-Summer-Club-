/*
 * Summer Club Activity LCD Display
 * Arduino script to display selected calendar activities on I2C LCD 16x2
 * Compatible with standard HD44780 based LCD displays with I2C interface
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD Configuration
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 columns, 2 rows

// Activity data structure
struct Activity {
  String date;
  String time;
  String type;
  String responsible;
  int participants;
  int capacity;
  String status;
};

Activity currentActivity;
bool hasActivity = false;
unsigned long lastScrollTime = 0;
int scrollPosition = 0;
bool isScrolling = false;
String longText = "";
int displayMode = 0; // 0: Date/Time, 1: Activity Type, 2: Responsible, 3: Participants
unsigned long lastModeChange = 0;
const unsigned long MODE_DURATION = 3000; // 3 seconds per mode

void setup() {
  Serial.begin(9600);
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  
  // Show startup message
  lcd.setCursor(0, 0);
  lcd.print("Summer Club");
  lcd.setCursor(0, 1);
  lcd.print("Calendar Ready");
  
  delay(2000);
  lcd.clear();
  
  // Show waiting message
  showWaitingMessage();
  
  Serial.println("Arduino LCD Display Ready");
  Serial.println("Waiting for activity data...");
}

void loop() {
  // Check for serial data
  if (Serial.available() > 0) {
    String receivedData = Serial.readStringUntil('\n');
    receivedData.trim();
    
    if (receivedData.startsWith("ACTIVITY:")) {
      parseActivityData(receivedData);
    } else if (receivedData == "NO_ACTIVITY") {
      showNoActivityMessage();
    } else if (receivedData == "CLEAR") {
      showWaitingMessage();
    }
  }
  
  // Update display if we have activity data
  if (hasActivity) {
    updateActivityDisplay();
  }
  
  delay(100);
}

void parseActivityData(String data) {
  // Expected format: ACTIVITY:date|time|type|responsible|participants|capacity|status
  // Example: ACTIVITY:2025-11-19|10:00|Mini Hackathon Kids|Tech Instructor|12|20|Scheduled
  
  data = data.substring(9); // Remove "ACTIVITY:" prefix
  
  int firstPipe = data.indexOf('|');
  int secondPipe = data.indexOf('|', firstPipe + 1);
  int thirdPipe = data.indexOf('|', secondPipe + 1);
  int fourthPipe = data.indexOf('|', thirdPipe + 1);
  int fifthPipe = data.indexOf('|', fourthPipe + 1);
  int sixthPipe = data.indexOf('|', fifthPipe + 1);
  
  if (firstPipe > 0 && secondPipe > 0 && thirdPipe > 0) {
    currentActivity.date = data.substring(0, firstPipe);
    currentActivity.time = data.substring(firstPipe + 1, secondPipe);
    currentActivity.type = data.substring(secondPipe + 1, thirdPipe);
    
    if (fourthPipe > 0) {
      currentActivity.responsible = data.substring(thirdPipe + 1, fourthPipe);
      
      if (fifthPipe > 0) {
        currentActivity.participants = data.substring(fourthPipe + 1, fifthPipe).toInt();
        
        if (sixthPipe > 0) {
          currentActivity.capacity = data.substring(fifthPipe + 1, sixthPipe).toInt();
          currentActivity.status = data.substring(sixthPipe + 1);
        } else {
          currentActivity.capacity = data.substring(fifthPipe + 1).toInt();
          currentActivity.status = "Unknown";
        }
      } else {
        currentActivity.participants = 0;
        currentActivity.capacity = 0;
        currentActivity.status = "Unknown";
      }
    } else {
      currentActivity.responsible = "Unknown";
      currentActivity.participants = 0;
      currentActivity.capacity = 0;
      currentActivity.status = "Unknown";
    }
    
    hasActivity = true;
    displayMode = 0;
    lastModeChange = millis();
    scrollPosition = 0;
    isScrolling = false;
    
    Serial.println("Activity data received:");
    Serial.println("Date: " + currentActivity.date);
    Serial.println("Time: " + currentActivity.time);
    Serial.println("Type: " + currentActivity.type);
    Serial.println("Responsible: " + currentActivity.responsible);
    Serial.println("Participants: " + String(currentActivity.participants) + "/" + String(currentActivity.capacity));
    Serial.println("Status: " + currentActivity.status);
    
    updateActivityDisplay();
  } else {
    Serial.println("Invalid activity data format received");
    showErrorMessage("Invalid Data");
  }
}

void updateActivityDisplay() {
  unsigned long currentTime = millis();
  
  // Change display mode every 3 seconds
  if (currentTime - lastModeChange >= MODE_DURATION) {
    displayMode = (displayMode + 1) % 4;
    lastModeChange = currentTime;
    scrollPosition = 0;
    isScrolling = false;
    lcd.clear();
  }
  
  switch (displayMode) {
    case 0:
      displayDateAndTime();
      break;
    case 1:
      displayActivityType();
      break;
    case 2:
      displayResponsible();
      break;
    case 3:
      displayParticipants();
      break;
  }
}

void displayDateAndTime() {
  lcd.setCursor(0, 0);
  lcd.print("Date: ");
  
  // Format date to fit display (show MM/DD)
  String shortDate = formatDate(currentActivity.date);
  lcd.print(shortDate);
  
  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  lcd.print(currentActivity.time);
  
  // Add status indicator
  lcd.setCursor(14, 1);
  if (currentActivity.status == "Scheduled") {
    lcd.print("OK");
  } else if (currentActivity.status == "Completed") {
    lcd.print("✓");
  } else {
    lcd.print("?");
  }
}

void displayActivityType() {
  lcd.setCursor(0, 0);
  lcd.print("Activity:");
  
  String activityType = currentActivity.type;
  if (activityType.length() <= 16) {
    lcd.setCursor(0, 1);
    lcd.print(activityType);
  } else {
    // Scroll long activity names
    displayScrollingText(activityType, 1);
  }
}

void displayResponsible() {
  lcd.setCursor(0, 0);
  lcd.print("Instructor:");
  
  String responsible = currentActivity.responsible;
  if (responsible.length() <= 16) {
    lcd.setCursor(0, 1);
    lcd.print(responsible);
  } else {
    displayScrollingText(responsible, 1);
  }
}

void displayParticipants() {
  lcd.setCursor(0, 0);
  lcd.print("Participants:");
  
  lcd.setCursor(0, 1);
  lcd.print(String(currentActivity.participants));
  lcd.print("/");
  lcd.print(String(currentActivity.capacity));
  
  // Show capacity percentage
  int percentage = 0;
  if (currentActivity.capacity > 0) {
    percentage = (currentActivity.participants * 100) / currentActivity.capacity;
  }
  
  lcd.print(" (");
  lcd.print(String(percentage));
  lcd.print("%)");
}

void displayScrollingText(String text, int row) {
  unsigned long currentTime = millis();
  
  if (currentTime - lastScrollTime >= 300) { // Scroll every 300ms
    lastScrollTime = currentTime;
    
    lcd.setCursor(0, row);
    lcd.print("                "); // Clear line
    lcd.setCursor(0, row);
    
    if (text.length() > 16) {
      String displayText = text.substring(scrollPosition);
      if (displayText.length() > 16) {
        displayText = displayText.substring(0, 16);
      }
      lcd.print(displayText);
      
      scrollPosition++;
      if (scrollPosition > text.length() - 16) {
        scrollPosition = 0;
        delay(1000); // Pause at the end
      }
    } else {
      lcd.print(text);
    }
  }
}

String formatDate(String fullDate) {
  // Convert YYYY-MM-DD to MM/DD
  if (fullDate.length() >= 10) {
    String month = fullDate.substring(5, 7);
    String day = fullDate.substring(8, 10);
    return month + "/" + day;
  }
  return fullDate;
}

void showWaitingMessage() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Summer Club");
  lcd.setCursor(0, 1);
  lcd.print("Select Date...");
  hasActivity = false;
}

void showNoActivityMessage() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Selected Date:");
  lcd.setCursor(0, 1);
  lcd.print("No Activities");
  hasActivity = false;
}

void showErrorMessage(String error) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Error:");
  lcd.setCursor(0, 1);
  if (error.length() > 16) {
    lcd.print(error.substring(0, 16));
  } else {
    lcd.print(error);
  }
  hasActivity = false;
}

// Function to handle multiple activities (show count)
void showMultipleActivities(int count) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Selected Date:");
  lcd.setCursor(0, 1);
  lcd.print(String(count));
  lcd.print(" Activities");
  hasActivity = false;
}