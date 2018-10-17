#include "client.h"

#include <QFile>
#include <QIODevice>
#include <QDataStream>

Client::Client(QObject *parent) : QObject(parent)
{

}

void Client::start()
{
    client = new QTcpSocket;
    connect(client, &QTcpSocket::connected, this, &Client::connect_ok);
    connect(client, &QTcpSocket::readyRead, this, &Client::recv_data);
    client->connectToHost(ip, port);
    //qDebug() << "client try to connect " << ip << port;
}

void Client::set_info(QString ip, int port)
{
    this->ip = ip;
    this->port = port;
    qDebug()<<"client get change info signal..."<<this->ip<<this->port;
    off_line();
    start();
    qDebug()<<"client already start...";
}

void Client::set_dir(QString dir)
{
    this->dir_name = dir;
    qDebug()<<"set client dir to -->"+dir_name;
}

void Client::off_line()
{
    if(!client==NULL)
    {
        client->close();
    }
}

void Client::connect_ok()
{
    //qDebug() << "client.cpp  connect ok...";
    emit connect_success();
}

void Client::recv_data()
{
    disconnect(client, &QTcpSocket::readyRead, this, &Client::recv_data);

    QByteArray data = client->readLine();
    QString content_type = QString::fromUtf8(data).remove("\r\n");

    //qDebug()<< "client.cpp  " << content_type;

    data = client->readLine();
    int content_length = QString::fromUtf8(data).remove("\r\n").toInt();

    //qDebug()<< "client.cpp  " << content_length;

    data = client->read(content_length);
    QString content = QString::fromUtf8(data);
    parse_data(content, content_type);

    if(content_type=="message")
    {
        //qDebug()<<"client.cpp  "+message;
        emit get_data(message, "message");
    }

    else if(content_type=="file")
    {
        //qDebug()<< "client.cpp  "+filename << "  " << file_size << "  " <<times;

        emit get_data(filename, "file");

        QFile file(dir_name+"/"+filename);
        if(!file.open(QIODevice::WriteOnly))
        {
            //qDebug() << "client.cpp  "<<"can not open file";
        }
        else
        {
            char *aaa = NULL;
            long long already_read = 0;
            long long l1 = 0;
            QDataStream in_file(&file);
            while(already_read<file_size)
            {
                while(!client->waitForReadyRead());
                QByteArray a1 = client->readAll();
                l1 = a1.size();
                aaa = a1.data();

                already_read += in_file.writeRawData(aaa, l1);
                double jindu = (double) already_read/file_size;
                //qDebug()<<jindu;

                int jin = (int) (jindu*100);
                //qDebug()<<jin;
                //qDebug() << "client recv "<<already_read;
                emit recv_file_length_change(jin);
            }
            //qDebug()<< "client recv done";
        }
        file.flush();
        file.close();
        //文件接收已经完美搞定
    }

    connect(client, &QTcpSocket::readyRead, this, &Client::recv_data);
}

void Client::parse_data(QString data, QString content_type)
{
    if(content_type=="message")
    {
        message = data;
    }
    else if(content_type=="file")
    {
        QStringList data_list = data.split("\r\n");
        file_size = data_list.at(0).toLongLong();
        times = data_list.at(1).toInt();
        filename = data_list.at(2);
    }
}
