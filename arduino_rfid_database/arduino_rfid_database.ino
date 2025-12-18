#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10    // SDA
#define RST_PIN 9    // RST
#define GREEN_LED 6  // Green LED for access granted
#define RED_LED 7    // Red LED for access denied
#define BUZZER 8     // Buzzer for audio feedback
#define SERVO_PIN 5  // Servo motor control pin

MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo doorServo;  // MG90S servo motor for door control

String lastProcessedUID = "";
unsigned long lastCardTime = 0;
const unsigned long CARD_TIMEOUT = 2000; // 2 seconds between same card readings

// Access feedback settings
bool waitingForResponse = false;
unsigned long responseTimeout = 5000; // 5 seconds timeout
unsigned long responseStartTime = 0;

// Door control settings
const int DOOR_OPEN_ANGLE = 90;    // Angle to open door (0-180 degrees)
const int DOOR_CLOSED_ANGLE = 0;   // Angle for closed door
const unsigned long DOOR_OPEN_TIME = 3000; // Keep door open for 3 seconds

// Convert UID bytes to a readable string like "13 2C 01 96"
String getUidString(MFRC522::Uid *uid) {
  String s = "";
  for (byte i = 0; i < uid->size; i++) {
    if (uid->uidByte[i] < 0x10) s += "0";
    s += String(uid->uidByte[i], HEX);
    if (i < uid->size - 1) s += " ";
  }
  s.toUpperCase();
  return s;
}

void setup() {
  Serial.begin(9600);
  while (!Serial) { }

  SPI.begin();
  mfrc522.PCD_Init();

  // Initialize LEDs and buzzer
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  // Initialize servo motor
  doorServo.attach(SERVO_PIN);
  doorServo.write(DOOR_CLOSED_ANGLE); // Start with door closed
  
  // Initial state - all off
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER, LOW);

  // Startup indication
  blinkLED(GREEN_LED, 2);
  blinkLED(RED_LED, 2);
  
  // Test servo movement on startup
  Serial.println("Testing door servo...");
  openDoor();
  delay(1000);
  closeDoor();
  Serial.println("Door servo test complete");
  
  Serial.println("RFID System Ready - Database Integration Active");
  Serial.println("Waiting for RFID cards...");
}

void loop() {
  // Check for serial commands from Qt application
  checkSerialCommands();
  
  // Check for timeout on waiting response
  if (waitingForResponse && (millis() - responseStartTime > responseTimeout)) {
    waitingForResponse = false;
    showAccessDenied();
    Serial.println("Response timeout - access denied");
  }
  
  // Wait for new card
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Read card
  if (!mfrc522.PICC_ReadCardSerial()) {
    Serial.println("Card detected, but UID read failed!");
    return;
  }

  // Build UID string
  String uidStr = getUidString(&mfrc522.uid);
  
  // Prevent duplicate readings of same card
  if (uidStr == lastProcessedUID && (millis() - lastCardTime) < CARD_TIMEOUT) {
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
    return;
  }
  
  lastProcessedUID = uidStr;
  lastCardTime = millis();

  Serial.print("Card detected! UID: ");
  Serial.println(uidStr);

  // Send verification request to Qt application
  Serial.print("VERIFY:");
  Serial.println(uidStr);
  
  // Set waiting state
  waitingForResponse = true;
  responseStartTime = millis();
  
  // Show waiting indication
  showWaiting();

  // Finish communication with this card
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

void checkSerialCommands() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    
    Serial.print("Received command: ");
    Serial.println(command);
    
    if (command.startsWith("ACCESS:GRANTED")) {
      waitingForResponse = false;
      
      // Extract member name if provided
      String memberName = "";
      int colonIndex = command.indexOf(':', 14); // After "ACCESS:GRANTED"
      if (colonIndex != -1) {
        memberName = command.substring(colonIndex + 1);
      }
      
      showAccessGranted();
      Serial.print("Access granted");
      if (memberName.length() > 0) {
        Serial.print(" to ");
        Serial.print(memberName);
      }
      Serial.println();
      
    } else if (command.startsWith("ACCESS:DENIED")) {
      waitingForResponse = false;
      showAccessDenied();
      Serial.println("Access denied");
      
    } else if (command == "DOOR:OPEN") {
      openDoor();
      Serial.println("Manual door open command executed");
      
    } else if (command == "DOOR:CLOSE") {
      closeDoor();
      Serial.println("Manual door close command executed");
      
    } else if (command == "DOOR:TEST") {
      testDoor();
      
    } else if (command == "STATUS") {
      printStatus();
      
    } else {
      Serial.println("Unknown command received");
      Serial.println("Available commands: ACCESS:GRANTED, ACCESS:DENIED, DOOR:OPEN, DOOR:CLOSE, DOOR:TEST, STATUS");
    }
  }
}

void showAccessGranted() {
  // Green LED on
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  
  // Success beep pattern
  beep(100);
  delay(100);
  beep(100);
  
  // Open the door
  Serial.println("Opening door...");
  openDoor();
  
  // Keep door open and LED on for specified time
  delay(DOOR_OPEN_TIME);
  
  // Close door and turn off LED
  Serial.println("Closing door...");
  closeDoor();
  digitalWrite(GREEN_LED, LOW);
}

void showAccessDenied() {
  // Red LED on for 2 seconds
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
  
  // Denial beep pattern
  beep(300);
  delay(100);
  beep(300);
  delay(100);
  beep(300);
  
  delay(2000);
  digitalWrite(RED_LED, LOW);
}

void showWaiting() {
  // Both LEDs blink quickly to show processing
  for (int i = 0; i < 3; i++) {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, HIGH);
    delay(100);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);
    delay(100);
  }
  
  // Short beep to acknowledge card read
  beep(50);
}

void blinkLED(int pin, int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(pin, HIGH);
    delay(200);
    digitalWrite(pin, LOW);
    delay(200);
  }
}

void beep(int duration) {
  digitalWrite(BUZZER, HIGH);
  delay(duration);
  digitalWrite(BUZZER, LOW);
}

// Door control functions
void openDoor() {
  Serial.println("Door: Opening...");
  doorServo.write(DOOR_OPEN_ANGLE);
  delay(500); // Give servo time to move
  Serial.println("Door: OPEN");
}

void closeDoor() {
  Serial.println("Door: Closing...");
  doorServo.write(DOOR_CLOSED_ANGLE);
  delay(500); // Give servo time to move
  Serial.println("Door: CLOSED");
}

// Test door mechanism (can be called via serial command)
void testDoor() {
  Serial.println("=== Door Test Sequence ===");
  openDoor();
  delay(2000);
  closeDoor();
  Serial.println("=== Door Test Complete ===");
}

// Debug function to print system status
void printStatus() {
  Serial.println("=== RFID System Status ===");
  Serial.print("Last UID: ");
  Serial.println(lastProcessedUID);
  Serial.print("Waiting for response: ");
  Serial.println(waitingForResponse ? "Yes" : "No");
  Serial.print("Door servo attached: ");
  Serial.println(doorServo.attached() ? "Yes" : "No");
  Serial.print("Current servo angle: ");
  Serial.println(doorServo.read());
  
  if (waitingForResponse) {
    unsigned long elapsed = millis() - responseStartTime;
    Serial.print("Response timeout in: ");
    Serial.print((responseTimeout - elapsed) / 1000);
    Serial.println(" seconds");
  }
  
  Serial.println("========================");
}
