#pragma once


#include <iostream>
#include <windows.h>

class Serial
{
public:
    HANDLE arduinoSerial;

    Serial(const std::wstring& portName);
    ~Serial();

    std::string ReadString();
    void WriteString(const std::string& data);
};
