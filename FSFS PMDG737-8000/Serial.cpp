#include "Serial.h"
#include <vector>
Serial::Serial(const std::wstring& portName)
{
    arduinoSerial = CreateFile(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (arduinoSerial == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Error opening serial port!" << std::endl;
    }
    else
    {
        DCB dcbSerialParams = { 0 };
        dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

        if (!GetCommState(arduinoSerial, &dcbSerialParams))
        {
            std::cerr << "Error getting serial port state!" << std::endl;
        }

        dcbSerialParams.BaudRate = CBR_9600; // Set your desired baud rate here
        dcbSerialParams.ByteSize = 8;        // Set your desired data bits here
        dcbSerialParams.StopBits = ONESTOPBIT; // Set your desired stop bits here
        dcbSerialParams.Parity = NOPARITY;    // Set your desired parity here

        if (!SetCommState(arduinoSerial, &dcbSerialParams))
        {
            std::cerr << "Error setting serial port state!" << std::endl;
        }
    }
}

std::string Serial::ReadString()
{
    const char MESSAGE_TERMINATOR = '\n';
    std::vector<char> buffer;
    char currentChar;

    while (true)
    {
        DWORD bytesRead;
        if (ReadFile(arduinoSerial, &currentChar, sizeof(currentChar), &bytesRead, nullptr))
        {
            if (bytesRead > 0)
            {
                buffer.push_back(currentChar);
                if (currentChar == MESSAGE_TERMINATOR)
                {
                    // Full message received
                    std::string receivedMessage(buffer.begin(), buffer.end());
                    buffer.clear();
                    return receivedMessage;
                }
            }
        }
        else
        {
            // Print error details
            DWORD error = GetLastError();
            std::wcerr << L"Error reading from serial port! Error code: " << error << std::endl;
            return "";
        }
    }
}


void Serial::WriteString(const std::string& data)
{
    DWORD bytesWritten;
    if (!WriteFile(arduinoSerial, data.c_str(), data.length(), &bytesWritten, nullptr))
    {
        std::cerr << "Error writing to serial port!" << std::endl;
    }
}