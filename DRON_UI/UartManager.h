#ifndef UARTMANAGER_H
#define UARTMANAGER_H

#include "Libs/qextserialport/qextserialport.h"

class UartManager
{
public:
    UartManager();
private:
    QextSerialPort com_port_;
};

#endif // UARTMANAGER_H
