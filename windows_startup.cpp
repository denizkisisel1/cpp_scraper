#include <iostream>
#include <windows.h>

int main() {
    HKEY hKey;
    const char* keyPath = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    const char* appName = "MyStartupApp";
    const char* appPath = "C:\\path\\to\\your\\program.exe"; // Replace with your program's actual path

    // Open the registry key for writing
    if (RegOpenKeyExA(HKEY_CURRENT_USER, keyPath, 0, KEY_WRITE, &hKey) == ERROR_SUCCESS) {
        // Set the registry entry value
        if (RegSetValueExA(hKey, appName, 0, REG_SZ, (BYTE*)appPath, strlen(appPath)) == ERROR_SUCCESS) {
            std::cout << "Registry entry added successfully." << std::endl;
        } else {
            std::cerr << "Failed to set registry entry." << std::endl;
        }

        // Close the registry key
        RegCloseKey(hKey);
    } else {
        std::cerr << "Failed to open registry key." << std::endl;
    }

    return 0;
}
