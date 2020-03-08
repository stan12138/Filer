#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include "server.h"
#include <QFile>
#include <QDataStream>

class MyServer : public Server
{
    Q_OBJECT
public:
    void send_file(QString filename, QString aim_ip = "", int aim_port = 0);
    QString dirname="/Users/hanyi02/Desktop";

    int send_block_size = 1024*512;  //发送块大小 B
    int send_interval = 10;   //发送时延 ms

signals:
    void connect_success(QString IP, int port);
    void connect_fail(QString IP, int port);
    void partner_close(QString IP, int port);

    void recv_message(QString message, QString IP, int port);
    void recv_file_process(QString filename, QString IP, int port, double process, double size_mb);
    void send_file_process(QString filename, QString IP, int port, double process, double size_mb);



public slots:

    void new_connect_callback(Messenger *messenger);
    void client_close_callback(Messenger *messenger);
    void receive_callback(Messenger *messenger);
    void stream_callback(QString filename, double size_mb, double process, QString the_ip, int the_port);

private:
    QFile *opened_file=nullptr;
    QDataStream *in_file=nullptr;
    double read_length = 0;
    void show_header(const QMap<QString, QString> &head);
};

#endif // MYSERVER_H
