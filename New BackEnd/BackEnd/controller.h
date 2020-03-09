#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QString>
#include <QList>
#include <QThread>

#include "ipclient.h"
#include "myclient.h"
#include "myserver.h"
#include "datatype.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();
    void send_message(QString message, QString aim_ip, int aim_port);
    void send_file(QString filename, QString aim_ip, int aim_port);

    void add_connect(QString aim_ip, int aim_port);
    void set_ID(QString my_id);
    void set_server_info(QString aim_ip, int port);

    QList<Device> connect_devices;

public slots:
    void ipclient_connect_fail();
    void ipclient_connect_success();
    void ipclient_update_devices(QList<Device> devices);

    void server_connect_partner_success(QString the_ip, int the_port);
    void server_connect_partner_fail(QString the_ip, int the_port);
    void server_partner_close(QString the_ip, int the_port);


    void client_connect_partner_success(QString the_ip, int the_port);
    void client_connect_partner_fail(QString the_ip, int the_port);
    void client_partner_close(QString the_ip, int the_port);


    void recv_message(QString message, QString the_ip, int the_port);
    void recv_file_process(QString filename, QString the_ip, int the_port, double process, double size_mb);
    void send_file_process(QString filename, QString the_ip, int the_port, double process, double size_mb);

signals:

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
    IPClient *ipclient = nullptr;
    MyServer *server = nullptr;
    MyClient *client = nullptr;


    QString my_id = "";
    int my_port = 0;
};

#endif // CONTROLLER_H
