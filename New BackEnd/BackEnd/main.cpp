#include "mainwindow.h"
#include "datatype.h"
#include <QApplication>
#include <QList>
int main(int argc, char *argv[])
{
    qRegisterMetaType<Device>("Device");
    qRegisterMetaType< QList<Device> >("QList<Device>");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
