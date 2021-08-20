#ifndef SERIALPORTTEST_H
#define SERIALPORTTEST_H
#include <QThread>
#include <QWidget>
#include "serial_port.h"
#include "QLabel"

QT_BEGIN_NAMESPACE
namespace Ui { class SerialPortTest; }
QT_END_NAMESPACE

class WorkThread : public QThread
{
    Q_OBJECT
public:
    explicit WorkThread(QObject *parent = 0, bool b = false);
    void run();

    uint8_t  m_data[256];
    uint32_t m_data_cnt;
    QByteArray data_write;
    // if Stop = true, the thread will break
    // out of the loop, and will be disposed
    bool Stop;
    Serial_Port *serialport;
    int mtimer_cnt;
    uint32_t mshow_cnt;
    QLabel *mlabel_senddata;
public slots:

};

class SerialPortTest : public QWidget
{
    Q_OBJECT

public:
    SerialPortTest(QWidget *parent = nullptr);
    ~SerialPortTest();
    WorkThread *mThread;

private:
    Ui::SerialPortTest *ui;
    QLabel *mlabel_timerdata;

public slots:
    void TimeOut();
};
#endif // SERIALPORTTEST_H
