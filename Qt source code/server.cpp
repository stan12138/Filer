#include "server.h"
#include <QHostAddress>
#include <QFile>
#include <QIODevice>
#include <QDataStream>
#include <QThread>

Server::Server(QObject *parent) : QObject(parent)
{

}

void Server::start()
{
    server = new QTcpServer;
    connect(server, &QTcpServer::newConnection, this, &Server::get_connect);
    while(!server->listen(QHostAddress::AnyIPv4, port))
    {
        port = port + 1;
    }

    emit report_port(port);
}

void Server::set_info(int port)
{
    this->port = port;
    off_line();
    start();
}

void Server::off_line()
{
    if(!client==NULL) client->close();
    if(!server==NULL) server->close();
}

void Server::send_data(QString data, QString content_type)
{
    if(content_type=="message")
    {
        QByteArray new_data = data.toUtf8();
        QString message = "message\r\n"+QString::number(new_data.size())+"\r\n"+QString::fromUtf8(new_data);
        QByteArray me = message.toUtf8();
        client->write(me);
        client->flush();
    }
    else if(content_type=="file")
    {
        //qDebug()<<data;
        QFile file(data);
        if(!file.open(QIODevice::ReadOnly))
        {
            //qDebug() <<"server.cpp  "<< "can not open file";
        }
        else
        {
            long long length = file.size();
            int times = int(length/(1024*512))+1;

            QStringList lis = data.split("/");
            QString name = lis.at(lis.size()-1);

            //qDebug()<<name<<length<<"  " << times;

            QString m1 = QString::number(length)+"\r\n"+QString::number(times)+"\r\n"+name; //此处需要处理文件名,取出最后一段
            QByteArray m2 = m1.toUtf8();

            QString m_head = "file\r\n"+QString::number(m2.size())+"\r\n"+m1;

            //qDebug()<<m_head;

            QByteArray data = m_head.toUtf8();
            client->write(data);
            client->flush();

            QThread::sleep(1);
            //qDebug()<<"send filename already";

            long long read_length = 0;


            QDataStream out_file(&file);
            for(int i=0; i<times; i++)
            {
                //QThread::msleep(5);
                char *aaa = new char[1024*512];
                int s3;
                s3 = out_file.readRawData(aaa, 1024*512);
                read_length += s3;
                QByteArray bbb = QByteArray(aaa, s3);
                long long s2 = bbb.size();
                long long s1 = client->write(QByteArray(bbb));
                bool flage = client->flush();
                //qDebug() << "read"  << s3 << s2;
                //qDebug() << "send " << s1 << flage;
                double jindu =  (double)read_length/length;
                int jin = (int) (jindu*100);
                emit send_file_length_change(jin);
                if(read_length>=length)
                {
                   emit send_done();
                   break;
                }
            }
        }
        file.close();
    }
}

void Server::get_connect()
{
    client = server->nextPendingConnection();
    emit connect_success(client->peerAddress().toString());
    //qDebug() << "client connect already";
}
