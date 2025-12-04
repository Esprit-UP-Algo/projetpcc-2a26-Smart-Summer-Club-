/*
 * Arduino Port Diagnostic Tool
 * Helps diagnose serial port connection issues
 * Compile with: g++ arduino_port_diagnostic.cpp -o arduino_diagnostic.exe
 */

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <setupapi.h>
#include <devguid.h>

#pragma comment(lib, "setupapi.lib")

void listAvailablePorts() {
    std::cout << "\n=== Available Serial Ports ===" << std::endl;
    
    // Method 1: Registry enumeration
    HKEY hKey;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DEVICEMAP\\SERIALCOMM", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        DWORD index = 0;
        char valueName[256];
        DWORD valueNameSize = sizeof(valueName);
        char portName[256];
        DWORD portNameSize = sizeof(portName);
        DWORD type;
        
        while (RegEnumValue(hKey, index++, valueName, &valueNameSize, NULL, &type, 
                           (BYTE*)portName, &portNameSize) == ERROR_SUCCESS) {
            std::cout << "Port: " << portName << " (Device: " << valueName << ")" << std::endl;
            valueNameSize = sizeof(valueName);
            portNameSize = sizeof(portName);
        }
        RegCloseKey(hKey);
    }
}

bool testPortAccess(const std::string& portName) {
    std::string fullPortName = "\\\\.\\" + portName;
    
    std::cout << "\nTesting access to " << portName << "..." << std::endl;
    
    HANDLE hSerial = CreateFile(fullPortName.c_str(),
                               GENERIC_READ | GENERIC_WRITE,
                               0,    // No sharing
                               NULL, // Default security
                               OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL,
                               NULL);
    
    if (hSerial == INVALID_HANDLE_VALUE) {
        DWORD error = GetLastError();
        switch (error) {
            case ERROR_ACCESS_DENIED:
                std::cout << "❌ ACCESS DENIED - Port is being used by another program" << std::endl;
                break;
            case ERROR_FILE_NOT_FOUND:
                std::cout << "❌ PORT NOT FOUND - Device may be disconnected" << std::endl;
                break;
            case ERROR_SHARING_VIOLATION:
                std::cout << "❌ SHARING VIOLATION - Port is locked by another process" << std::endl;
                break;
            default:
                std::cout << "❌ ERROR " << error << " - Unknown error" << std::endl;
                break;
        }
        return false;
    } else {
        std::cout << "✅ SUCCESS - Port is available for use" << std::endl;
        CloseHandle(hSerial);
        return true;
    }
}

void findArduinoDevices() {
    std::cout << "\n=== Arduino Device Detection ===" << std::endl;
    
    HDEVINFO deviceInfoSet = SetupDiGetClassDevs(&GUID_DEVCLASS_PORTS,
                                                 NULL,
                                                 NULL,
                                                 DIGCF_PRESENT);
    
    if (deviceInfoSet == INVALID_HANDLE_VALUE) {
        std::cout << "Failed to enumerate devices" << std::endl;
        return;
    }
    
    SP_DEVINFO_DATA deviceInfoData;
    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    
    for (DWORD i = 0; SetupDiEnumDeviceInfo(deviceInfoSet, i, &deviceInfoData); i++) {
        char deviceDescription[256];
        char hardwareId[256];
        
        if (SetupDiGetDeviceRegistryProperty(deviceInfoSet, &deviceInfoData,
                                           SPDRP_DEVICEDESC, NULL,
                                           (BYTE*)deviceDescription,
                                           sizeof(deviceDescription), NULL)) {
            
            if (SetupDiGetDeviceRegistryProperty(deviceInfoSet, &deviceInfoData,
                                               SPDRP_HARDWAREID, NULL,
                                               (BYTE*)hardwareId,
                                               sizeof(hardwareId), NULL)) {
                
                std::string desc(deviceDescription);
                std::string hwId(hardwareId);
                
                // Check if this looks like an Arduino
                if (desc.find("Arduino") != std::string::npos ||
                    desc.find("CH340") != std::string::npos ||
                    desc.find("CP210") != std::string::npos ||
                    hwId.find("VID_2341") != std::string::npos || // Arduino VID
                    hwId.find("VID_1A86") != std::string::npos) { // CH340 VID
                    
                    std::cout << "🎯 ARDUINO FOUND!" << std::endl;
                    std::cout << "  Description: " << deviceDescription << std::endl;
                    std::cout << "  Hardware ID: " << hardwareId << std::endl;
                }
            }
        }
    }
    
    SetupDiDestroyDeviceInfoList(deviceInfoSet);
}

int main() {
    std::cout << "Arduino Port Diagnostic Tool" << std::endl;
    std::cout << "===========================" << std::endl;
    
    findArduinoDevices();
    listAvailablePorts();
    
    std::cout << "\n=== Port Access Tests ===" << std::endl;
    std::cout << "Enter port names to test (e.g., COM5) or 'quit' to exit:" << std::endl;
    
    std::string input;
    while (std::getline(std::cin, input) && input != "quit" && input != "q") {
        if (!input.empty() && input.substr(0, 3) == "COM") {
            testPortAccess(input);
        } else if (!input.empty()) {
            std::cout << "Invalid port name. Use format: COM1, COM5, etc." << std::endl;
        }
        std::cout << "\nEnter another port name or 'quit':" << std::endl;
    }
    
    return 0;
}