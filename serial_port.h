#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include <QByteArray>
#include "serial.h"

class Serial_Port
{
public:
    explicit Serial_Port();
    int Serial_Port_Open(QString port_name, int speed);
    int Serial_Port_Write(QByteArray *data);
    int Serial_Port_Read(QByteArray *data_read);
    int Serial_Port_Close();
private:
    serial_t *m_serial;

};

#endif // SERIAL_PORT_H
