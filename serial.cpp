#include "serial.h"


Serial::Serial(const wchar_t *portName)
{
    this->connected = false;

    this->hSerial = ::CreateFile(portName,
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

    if(this->hSerial==INVALID_HANDLE_VALUE)
    {
        qDebug() << "Error while initializing Serial reader! error code: " << GetLastError();
    }
    else
    {
        DCB dcbSerialParams = {0};

        if (!GetCommState(this->hSerial, &dcbSerialParams))
        {
            qDebug() << "failed to get current serial parameters!";
        }
        else
        {
            dcbSerialParams.BaudRate=CBR_9600;
            dcbSerialParams.ByteSize=8;
            dcbSerialParams.StopBits=ONESTOPBIT;
            dcbSerialParams.Parity=NOPARITY;
            //Setting the DTR to Control_Enable ensures that the Arduino is properly
            //reset upon establishing a connection
            dcbSerialParams.fDtrControl = DTR_CONTROL_ENABLE;

             if(!SetCommState(hSerial, &dcbSerialParams))
             {
                qDebug() << "ALERT: Could not set Serial Port parameters";
             }
             else
             {
                 this->connected = true;
                 PurgeComm(this->hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
                 Sleep(ARDUINO_WAIT_TIME);
             }
        }
    }
}

Serial::~Serial()
{
    if(this->connected)
    {
        this->connected = false;

        CloseHandle(this->hSerial);
    }
}

int Serial::ReadData(char *buffer, unsigned int nbChar)
{
    DWORD bytesRead;

    unsigned int toRead;

    ClearCommError(this->hSerial, &this->errors, &this->status);

    if(this->status.cbInQue>0)
    {
        if(this->status.cbInQue > nbChar)
            toRead = nbChar;
        else
            toRead = this->status.cbInQue;

        if(ReadFile(this->hSerial, buffer, toRead, &bytesRead, NULL))
            return bytesRead;
    }

    //If nothing has been read, or that an error was detected return 0
    return 0;
}

bool Serial::WriteData(const char *buffer, unsigned int nbChar)
{
    DWORD bytesSend;

    if(!WriteFile(this->hSerial, (void *)buffer, nbChar, &bytesSend, 0))
    {
        ClearCommError(this->hSerial, &this->errors, &this->status);

        return false;
    }
    else
    {
        return true;
    }
}

bool Serial::IsConnected()
{
    return this->connected;
}
