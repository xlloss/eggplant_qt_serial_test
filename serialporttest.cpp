#include "serialporttest.h"
#include "ui_serialporttest.h"
#include <QTimer>

#define MCU_UART_PORT "/dev/ttyS1"
#define MCU_UART_SPEED 921600

/* #define SEND_UART_PORT "/dev/ttyUSB0" */
/* #define SEND_UART_SPEED 115200 */

SerialPortTest::SerialPortTest(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SerialPortTest)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);

    mlabel_timerdata = ui->timer_data;

    mThread = new WorkThread(this);
    mThread->mlabel_senddata = ui->send_data;

    mThread->start();

    connect(timer, SIGNAL(timeout()), this, SLOT(TimeOut()));
    timer->start(15);
}

SerialPortTest::~SerialPortTest()
{
    mThread->serialport->Serial_Port_Close();
    delete ui;
}

void SerialPortTest::TimeOut()
{
    QString label_str;

    mThread->mtimer_cnt++;
    mThread->mshow_cnt++;
    label_str.sprintf("%d", mThread->mshow_cnt);
    mlabel_timerdata->setText(label_str);
    update();
    /* qDebug("%s %d\n", __func__, mThread->mtimer_cnt); */
}

WorkThread::WorkThread(QObject *parent, bool b) :
    QThread(parent), Stop(b)
{
    int ret;
    uint8_t i;

    mtimer_cnt = 0;
    mshow_cnt = 0;
    serialport = new Serial_Port();
    ret = serialport->Serial_Port_Open(MCU_UART_PORT, MCU_UART_SPEED);
    if (ret)
        qDebug("Serial_Port_Open fail\n");

    i = 0;
    while (i != 255) {
        m_data[i] = i;
        i++;
    }
    data_write.append((char *)m_data, 256);
}

void WorkThread::run()
{
    static uint32_t send_data_cnt = 0;
    QString labelstr;

    while (1) {
        if (mtimer_cnt > 0) {
            serialport->Serial_Port_Write(&data_write);

            mtimer_cnt--;
            send_data_cnt++;

            labelstr.sprintf("%d", send_data_cnt);
            mlabel_senddata->setText(labelstr);
            /* qDebug("%s %d\n", __func__, send_data_cnt); */
        }
        usleep(10);
    }
}
