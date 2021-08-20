#include "serialporttest.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SerialPortTest w;
    w.show();
    return a.exec();
}
