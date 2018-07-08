#ifndef IP_HANDLER_H
#define IP_HANDLER_H

#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <vector>

#include "my_datatype.h"

class IP_Handler : public QObject
{
    Q_OBJECT
public:
    explicit IP_Handler(QObject *parent = nullptr);

signals:
    void connect_success();
    void send_devices(std::vector<Device_info> devices);

public slots:
    void report_status();
    void start();
    void set_info(QString ip, QString id, int port, int my_port);
    void off_line();

private :
    QTcpSocket *ip_server = NULL;
    QString ip;
    QString id;
    int port;

    int my_server_port;

    bool connect_flage = false;
    bool report_flage = false;


    void connect_ok();
    void report();
    void recv_data();

    void parse_ip_info(QString data);


};

#endif // IP_HANDLER_H
