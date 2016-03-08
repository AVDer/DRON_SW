#ifndef UARTMANAGER_H
#define UARTMANAGER_H

#include <QString>

#include "Libs/qextserialport/qextserialport.h"

class UartManager
{
public:
    UartManager();
    ~UartManager();
    void set_port(QString port_name);
    bool is_open() {return com_port_.isOpen();}
    bool is_bytes_available() {return com_port_.bytesAvailable();}
    void write(const  char* data, qint64 length) {com_port_.write(data, length);}
    char get_char() {char c; com_port_.getChar(&c); return c;}
private:
    QextSerialPort com_port_;
    QString current_port;
};

#endif // UARTMANAGER_H
