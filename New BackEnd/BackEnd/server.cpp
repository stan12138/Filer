#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{

    server = new QTcpServer;
    connect(server, &QTcpServer::newConnection, this, &Server::accept);

}

Server::~Server()
{
    server->close();
    delete server;
    for(int i=0; i<messengers.size(); i++)
    {
        messengers.at(i)->close();
        delete messengers.at(i);
    }
}



void Server::send(QMap<QString, QString> &the_header, const QByteArray &data, QString aim_ip, int aim_port)
{
    if(aim_ip!="" && aim_port!=0)
    {
        for(int i=0; i<messengers.length(); i++)
        {
            if(messengers.at(i)->IP==aim_ip && messengers.at(i)->port==aim_port)
            {
                messengers.at(i)->send(the_header, data);
                return ;
            }
        }
    }
    else
    {
        for(int i=0; i<messengers.length(); i++)
        {
            messengers.at(i)->send(the_header, data);
        }
    }
}

int Server::generate_server()
{
    while(!server->listen(my_address, init_port))
    {
        qDebug() << init_port;
        init_port++;
    }

    return init_port;
    // emit server_success(init_port);
}


void Server::accept()
{
    QTcpSocket *client = server->nextPendingConnection();
    QString ip = client->peerAddress().toString();
    int po = (int) client->peerPort();
    Messenger *messenger = new Messenger(client, ip, po);
    messengers.append(messenger);
    connect(messenger, &Messenger::recv_message, this, &Server::receive_callback);
    connect(messenger, &Messenger::connect_close, this, &Server::client_close_callback);
    connect(messenger, &Messenger::stream, this, &Server::stream_callback);
    new_connect_callback(messenger);
}

void Server::stream_callback(QString filename, double size_mb, double process, QString the_ip, int the_port)
{
    qDebug() << filename << "   " << process ;
}

void Server::new_connect_callback(Messenger *messenger)
{
    qDebug() << "get new connect " << messenger->IP << ":" << messenger->port;
}

void Server::receive_callback(Messenger *messenger)
{
    QMap<QString, QString> header;
    QMapIterator<QString, QString> i(messenger->header);
    while (i.hasNext()) {
        i.next();
        qDebug() << i.key() << ": " << i.value();
        if(i.key()!="CL") header.insert(i.key(), i.value());
    }

    messenger->send(header);
}

void Server::client_close_callback(Messenger *messenger)
{
    messengers.removeOne(messenger);
    qDebug() << "connect close ->  " << messenger->IP << ":" << messenger->port;
}
