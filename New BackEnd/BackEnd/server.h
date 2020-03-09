#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QMap>
#include <QString>
#include <QHostAddress>
#include <QTimer>


#include "messenger.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();


    void send(QMap<QString, QString> &the_header, const QByteArray &data=NULL, QString aim_ip="", int aim_port=0);

    QList<Messenger *> messengers;



public slots:

    virtual void new_connect_callback(Messenger *messenger);
    virtual void client_close_callback(Messenger *messenger);
    virtual void receive_callback(Messenger *messenger);
    virtual void stream_callback(QString filename, double size_mb, double process, QString the_ip, int the_port);

    int generate_server();


signals:

private:
    QTcpServer *server;
    QHostAddress my_address=QHostAddress::AnyIPv4;
    int init_port=63330;
    void accept();

};

#endif // SERVER_H
