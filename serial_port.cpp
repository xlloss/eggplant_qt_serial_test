#include <QDebug>
#include "serial_port.h"

Serial_Port::Serial_Port()
{

}

/* Open /dev/ttyUSB0 with baudrate 115200, and defaults of 8N1, no flow control */
int Serial_Port::Serial_Port_Open(QString port_name, int speed)
{
    m_serial = serial_new();
    if (!m_serial)
        return  -EINVAL;

    if (serial_open(m_serial, port_name.toUtf8().data(), speed) < 0) {
        qDebug("serial_open(): %s\n", serial_errmsg(m_serial));
        return -EINVAL;
    }

    return  0;
}

int Serial_Port::Serial_Port_Write(QByteArray *data_write)
{
    unsigned char *buf;

    if (!data_write)
        return -EINVAL;

    /* Write to the serial port */
    buf = (unsigned char *)data_write->data();

    qDebug("Write Data Size %d\n", data_write->size());
    if (serial_write(m_serial, buf, data_write->size()) < 0) {
        qDebug("serial_write(): %s\n", serial_errmsg(m_serial));
        return -EINVAL;
    }

    return 0;
}

int Serial_Port::Serial_Port_Read(QByteArray *data_read)
{
    unsigned char buf[64];
    int ret;
    #define TIMEOUT 2000

    if (!data_read)
        return -EINVAL;

    /* Read up to buf size or 2000ms timeout */
    if ((ret = serial_read(m_serial, buf, sizeof(buf), TIMEOUT)) < 0) {
        qDebug("serial_read(): %s\n", serial_errmsg(m_serial));
        return -EINVAL;
    }

    data_read->resize(ret);
    memcpy(data_read->data(), buf, ret);

    /* qDebug("read %d bytes: _%s_\n", ret, buf); */
    return 0;
}

int Serial_Port::Serial_Port_Close()
{
    serial_close(m_serial);
    serial_free(m_serial);
    return 0;
}
