#include "myclient.h"
#include <QFile>
#include <QIODevice>
#include <QThread>
#include <QtMath>

void MyClient::connect_fail_callback(Messenger *messenger)
{
    messenger->close();
    messengers.removeOne(messenger);
//    qDebug() << "myclient connect fail ->  " << messenger->IP << ":" << messenger->port;
    emit connect_fail(messenger->IP, messenger->port);
}

void MyClient::connect_success_callback(Messenger *messenger)
{
//    qDebug() << "myclient  success " << messenger->IP << ":" << messenger->port;
    emit connect_success(messenger->IP, messenger->port);
}

void MyClient::client_close_callback(Messenger *messenger)
{
//    messenger->close();
    messengers.removeOne(messenger);
//    qDebug() << "myclient  connect close ->  " << messenger->IP << ":" << messenger->port;
    emit partner_close(messenger->IP, messenger->port);
}

void MyClient::receive_callback(Messenger *messenger)
{
    if(messenger->header.contains("TP") && messenger->header["TP"]=="file")
    {
        if(opened_file==nullptr)
        {
            opened_file = new QFile(dirname+"/"+messenger->header["N"]);
            if(opened_file->open(QIODevice::WriteOnly))
            {
                in_file = new QDataStream(opened_file);
                read_length = 0;
//                qDebug() << "receive file: " << dirname+"/"+messenger->header["N"];
                emit recv_file_process(messenger->header["N"], messenger->IP, messenger->port, 0, messenger->header["L"].toDouble()/(1024.0*1024.0));
            }
        }
        read_length += (double) in_file->writeRawData(messenger->content.data(), messenger->content.size());
        opened_file->flush();
//        qDebug() << "receive process: " << read_length/messenger->header["L"].toDouble();
        emit recv_file_process(messenger->header["N"], messenger->IP, messenger->port, read_length/messenger->header["L"].toDouble(), messenger->header["L"].toDouble()/(1024.0*1024.0));
        if(messenger->header["index"]=="-1")
        {
            opened_file->flush();
            opened_file->close();
            delete opened_file;
            delete in_file;
            opened_file = nullptr;
            in_file = nullptr;
        }
    }
    else //show_header(messenger->header);
        emit recv_message(messenger->header["info"], messenger->IP, messenger->port);
}

void MyClient::stream_callback(QString filename, double size_mb, double process, QString the_ip, int the_port)
{
    emit recv_file_process(filename, the_ip, the_port, process, size_mb);
}


void MyClient::send_file(QString filename, QString aim_ip, int aim_port)
{
    bool has_aim = false;
    for(int i=0; i<messengers.length(); i++)
    {
        if(messengers.at(i)->IP==aim_ip && messengers.at(i)->port==aim_port)
        {
            has_aim = true;
            break ;
        }
    }
    if(!has_aim) return;
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly))
    {
        long long length = file.size();
        int times = qCeil(length/send_block_size);
        QStringList lis = filename.split("/");
        QString name = lis.at(lis.size()-1);
        QMap<QString, QString> head;
        head.insert("TP", "file");
        head.insert("N", name);
        head.insert("L", QString::number(length));
        head.insert("index", "0");
        double send_length = 0;
        for(int i=0; i<times; i++)
        {

//            qDebug() << times << ": " << i;
            if(i==(times-1))
            {
               head["index"] = QString::number(-1);
            }
            else
            {
               head["index"] = QString::number(i);
            }
            int read_size = i==(times-1) ? length-(times-1)*send_block_size : send_block_size;
            QByteArray data;
            while(data.length()<read_size)
            {
                data.append(file.read(read_size-data.length()));
            }
            send_length += read_size;
            send(head, data, aim_ip, aim_port);
            QThread::msleep(send_interval);
            emit send_file_process(name, aim_ip, aim_port, send_length/length, length/(1024.0*1024.0));
        }
    }
}

void MyClient::show_header(const QMap<QString, QString> &head)
{
    QMapIterator<QString, QString> i(head);
    while (i.hasNext()) {
        i.next();
        qDebug() << "my" << i.key() << ": " << i.value();
    }
}
