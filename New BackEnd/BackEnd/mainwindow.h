#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "client.h"
#include "myclient.h"
#include "server.h"
#include "myserver.h"
#include "ipclient.h"
#include "datatype.h"
#include "controller.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void push();

public slots:
    void connect_ipserver_success();
    void connect_ipserver_fail();
    void online_devices(QList<Device> devices);

    void new_partner_signal(QString the_ip, int the_port);
    void connect_partner_fail_signal(QString the_ip, int the_port);
    void partner_close_signal(QString the_ip, int the_port);
    void recv_message_signal(QString message, QString the_ip, int the_por);
    void recv_file_signal(QString filename, QString the_ip, int the_port, double process, double size_mb);
    void send_file_signal(QString filename, QString the_ip, int the_port, double process, double size_mb);

private:
    Ui::MainWindow *ui;

    Controller *controller = nullptr;

    QList<Device> online_devices_list;

};
#endif // MAINWINDOW_H
