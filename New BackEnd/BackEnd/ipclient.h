#ifndef IPCLIENT_H
#define IPCLIENT_H

#include <QObject>
#include <QTimer>

#include "client.h"
#include "datatype.h"

class IPClient : public Client
{
    Q_OBJECT

public:
    ~IPClient();
    void set_info(QString my_ID, int my_port);
    void begin();
    void stop();

    void connect_ipserver(QString aim_ip, int aim_port);
    QList<Device> online_devices;

signals:
    void connect_fail();
    void connect_success();
    void online_devices_update(QList<Device> online_devices);

public slots:
    void connect_fail_callback(Messenger *messenger);
    void connect_success_callback(Messenger *messenger);
    void client_close_callback(Messenger *messenger);
    void receive_callback(Messenger *messenger);

private:
    QTimer *timer = nullptr;
    QString ID="";
    int port=0;

    void report();
    void parser_devices(const QByteArray &data);
};

#endif // IPCLIENT_H
