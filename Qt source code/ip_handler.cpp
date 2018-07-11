#include "ip_handler.h"

#include <QDebug>
#include <QThread>
#include <vector>
#include "my_datatype.h"


IP_Handler::IP_Handler(QObject *parent) : QObject(parent)
{
;
}

void IP_Handler::report_status()
{
    //qDebug() << "ip_handler.cpp is running....";
}

void IP_Handler::start()
{
    ip_server = new QTcpSocket;
    connect(ip_server, &QTcpSocket::connected, this, &IP_Handler::connect_ok);
    connect(ip_server, &QTcpSocket::readyRead, this, &IP_Handler::recv_data);
    //qDebug() << "ip_handler.cpp  going to connect...";
    ip_server->connectToHost(ip, port);
    report_flage = false;
}

void IP_Handler::set_info(QString ip, QString id, int port, int my_port)
{
    this->ip = ip;
    this->id = id;
    this->port = port;
    this->my_server_port = my_port;

    off_line();
    start();
}

void IP_Handler::off_line()
{
    if(!ip_server==NULL)
    {
        QString m = "off-line";
        QByteArray d = m.toUtf8();
        ip_server->write(d);
        ip_server->flush();
        ip_server->close();
    }
}

void IP_Handler::connect_ok()
{
    //qDebug() << "ip_handler.cpp  connect success....";
    if(!report_flage)
    {
        //qDebug() << "ip_handler.cpp  report one time....";
        report();
        //QThread::sleep(1);
    }
}

void IP_Handler::report()
{

    if(!(my_server_port==0))
    {
        QString message = id+"\n"+QString::number(my_server_port);
        QByteArray d = message.toUtf8();
        long long length = ip_server->write(d);
        ip_server->flush();
        //qDebug()<< "ip_handler.cpp  send message : " << message << "  return : " << length;
    }
    else
    {
        ;
    }

}

void IP_Handler::recv_data()
{
    QString data = ip_server->readAll();
    //qDebug() << data;
    if(data=="get")
    {
        //qDebug() << "ip_handler.cpp "+data;
        report_flage = true;
    }
    else if(!report_flage) report();
    else parse_ip_info(data);
}

void IP_Handler::parse_ip_info(QString data)
{
    //qDebug() << "ip_handler.cpp "+data;
    std::vector<Device_info> devices;
    if(data=="0");
    else
    {
        QStringList all_list = data.split("\r\n");
        for(int i=0; i<all_list.size(); i++)
        {
            QString one = all_list.at(i);
            if(one.size()>1)
            {
                QStringList one_info = one.split("\n");
                Device_info a = {one_info.at(0), one_info.at(2), one_info.at(1).toInt()};
                devices.push_back(a);
            }
        }

        emit send_devices(devices);
    }

}
