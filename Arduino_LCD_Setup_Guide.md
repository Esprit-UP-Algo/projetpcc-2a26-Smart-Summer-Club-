# Arduino LCD Integration Setup Guide

## Hardware Requirements

### Components Needed:
1. Arduino Uno/Nano/ESP32 (any compatible board)
2. 16x2 LCD Display with I2C backpack (HD44780 compatible)
3. Jumper wires
4. USB cable for Arduino connection

### Wiring Diagram:

**I2C LCD to Arduino:**
```
LCD I2C Module    Arduino Uno    Arduino Nano    ESP32
VCC              5V             5V              3.3V/5V
GND              GND            GND             GND  
SDA              A4 (Pin 18)    A4              Pin 21
SCL              A5 (Pin 19)    A5              Pin 22
```

### I2C Address Configuration:
- Most I2C LCD modules use address `0x27`
- If your display doesn't work, try addresses: `0x20`, `0x3F`, or `0x26`
- Use I2C scanner sketch to find the correct address if needed

## Software Setup

### 1. Arduino Libraries Required:
Install these libraries through Arduino IDE Library Manager:
- `LiquidCrystal I2C` by Frank de Brabander
- `Wire` (built-in, no installation needed)

### 2. Upload Arduino Code:
1. Open `activity_lcd_display.ino` in Arduino IDE
2. Select your board type (Tools > Board)
3. Select correct COM port (Tools > Port)
4. Upload the sketch to Arduino

### 3. Qt Application Setup:
The Qt application automatically includes serial communication. No additional setup required.

## Communication Protocol

### Message Format:
The Qt application sends data to Arduino using this format:
```
ACTIVITY:date|time|type|responsible|participants|capacity|status
```

### Example Messages:
```
ACTIVITY:2025-11-19|10:00|Mini Hackathon Kids|Tech Instructor|12|20|Scheduled
NO_ACTIVITY
CLEAR
```

### Arduino Responses:
- Arduino prints debug information to Serial Monitor at 9600 baud
- LCD displays activity information in rotating views (3 seconds each)

## LCD Display Modes

The Arduino cycles through 4 display modes every 3 seconds:

### Mode 1: Date & Time
```
Date: 11/19      OK
Time: 10:00
```

### Mode 2: Activity Type
```
Activity:
Mini Hackathon Kids
```

### Mode 3: Instructor
```
Instructor:
Tech Instructor
```

### Mode 4: Participants
```
Participants:
12/20 (60%)
```

## Usage Instructions

### 1. Connect Arduino:
1. Wire the LCD to Arduino as shown above
2. Upload the Arduino sketch
3. Connect Arduino to computer via USB

### 2. In Qt Application:
1. Open the Activity Calendar tab
2. Click "🔌 Connect LCD" button
3. Application will automatically detect Arduino port
4. Status should show "LCD: Connected" in green

### 3. View Activities:
1. Click on any date in the calendar
2. If activities exist for that date, they appear on LCD
3. LCD cycles through information displays
4. If no activities, LCD shows "No Activities"

### 4. Disconnect:
- Click "🔌 Disconnect" button to safely disconnect
- Or simply close the application

## Troubleshooting

### Arduino Not Detected:
1. Check USB cable connection
2. Ensure Arduino drivers are installed
3. Try different USB port
4. Check if another program is using the serial port

### LCD Not Displaying:
1. Verify wiring connections
2. Check I2C address in Arduino code (line 8)
3. Test with I2C scanner sketch
4. Ensure LCD has power (backlight should be on)

### Communication Issues:
1. Check Arduino Serial Monitor (9600 baud)
2. Verify Qt application shows "LCD: Connected"
3. Try disconnecting and reconnecting
4. Restart Arduino (press reset button)

### No Activities Showing:
1. Ensure you have activities in the database
2. Check that the selected date has activities
3. Verify activities are loading in the Qt calendar view

## Advanced Configuration

### Changing I2C Address:
If your LCD uses a different I2C address, modify line 8 in the Arduino code:
```cpp
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change 0x27 to your address
```

### Customizing Display Duration:
To change how long each mode displays, modify line 17:
```cpp
const unsigned long MODE_DURATION = 3000; // 3 seconds (change as needed)
```

### Adding More Display Modes:
You can extend the Arduino code to show additional information by:
1. Adding new cases in `updateActivityDisplay()` function
2. Increasing the modulus in `displayMode = (displayMode + 1) % 4;`
3. Creating new display functions

## Hardware Alternatives

### Using Regular LCD (without I2C):
If you have a standard 16x2 LCD without I2C:
1. Use `LiquidCrystal.h` library instead
2. Connect LCD using 6 pins: RS, Enable, D4, D5, D6, D7
3. Modify Arduino code to use standard LiquidCrystal initialization

### Using Other Display Types:
- OLED displays (SSD1306) - modify for different library
- Larger LCD displays (20x4) - adjust text positioning
- LED matrix displays - completely different approach needed

## Support and Extension

### Adding New Features:
The system is designed to be easily extensible:
- Add new LCD display modes
- Support multiple activities per day
- Add sound notifications
- Include status LEDs
- Add buttons for navigation

### Integration with Other Systems:
The serial protocol can be adapted for:
- Different microcontrollers (ESP32, Raspberry Pi)
- Wireless communication (WiFi, Bluetooth)
- IoT platforms (MQTT, HTTP APIs)
- Mobile applications

## Safety Notes

- Always disconnect Arduino power when wiring
- Double-check connections before powering on
- Use appropriate voltage levels (5V for Arduino Uno, 3.3V for ESP32)
- Ensure good connections to avoid intermittent issues