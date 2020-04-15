#ifndef SERIAL_H
#define SERIAL_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include <QDebug>

class Serial
{
private:
    const uint16_t ARDUINO_WAIT_TIME = 2000;

    HANDLE hSerial;
    bool connected;
    COMSTAT status;
    DWORD errors;

public:
    Serial(const wchar_t *portName);
    ~Serial();

    int ReadData(char *buffer, unsigned int nbChar);

    bool WriteData(const char *buffer, unsigned int nbChar);

    bool IsConnected();

};

#endif // SERIAL_H
