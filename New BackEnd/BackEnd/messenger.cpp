#include "messenger.h"
#include <QStringList>
#include <QFile>
#include <QDataStream>

Messenger::Messenger(QTcpSocket *client, QString the_ip, int the_port, QObject *parent) : QObject(parent)
{
    socket = client;
    my_ip = client->localAddress().toString();
    connect(socket, &QTcpSocket::connected, this, &Messenger::connect_done);
    connect(socket, &QTcpSocket::readyRead, this, &Messenger::read);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &Messenger::socket_error);
    IP = the_ip;
    port = the_port;

}

void Messenger::send(QMap<QString, QString> &the_header, const QByteArray &data)
{
    if(data.length()>0) the_header.insert("CL", QString::number(data.length()));
    else the_header.insert("CL", "0");

    QString head = "";
    QMapIterator<QString, QString> i(the_header);
    while (i.hasNext()) {
        i.next();
        head += i.key() + ":" + i.value() + ";";
    }
    head = head.left(head.length()-1);
    QByteArray head_byte = head.toUtf8();
    int length = head_byte.length();
    QByteArray head_1 = Int2Byte(length);

    head_1 = head_1 + head_byte;
    if(data.length()>0) head_1 = head_1 + data;

    write_data(head_1);
}

void Messenger::close()
{
    socket->close();
    socket->abort();
    delete socket;
}

void Messenger::process_header(QByteArray &data)
{
    read_data(2, data);
    int header_length = Byte2Int(data);
    data.clear();
    read_data(header_length, data);
    QString header_string = QString::fromUtf8(data);
    parse_header(header_string);
    data.clear();
}

// 理由同下
//void Messenger::process_header(QByteArray &data)
//{
//    if(data.length()<2) read_data(2, data);
//    int header_length = Byte2Int(data);
//    data = data.right(data.length()-2);
//    if(data.length()<header_length)
//    {
//        header_length -= data.length();
//        read_data(header_length, data);
//    }
//    QString header_string = QString::fromUtf8(data.left(header_length));
//    parse_header(header_string);
//    data = data.right(data.length()-header_length);
//}

// 以下为当不信任read_data可以读取准确字节数的处理方法，我决定抛弃，换成一个信任read_data是准确的版本
//void Messenger::read()
//{
//    QByteArray data = remain_data;
//    process_header(data);

//    content.clear();
//    if(header["CL"]=="0")
//    {
//        remain_data=data;
//        emit recv_message(this);
//        return ;
//    }

//    if(header.contains("TP") && header["TP"]=="file" && header["L"].toInt()>1024*1024*10)
//    {
//        stream_flag = true;
//        stream_work(data);
//    }
//    else
//    {
//        stream_flag = false;
//        int content_length = header["CL"].toInt();
//        if(data.length()>=content_length)
//        {
//            content = data.left(content_length);
//            remain_data = data.right(data.length()-content_length);
//        }
//        else
//        {
//            content.append(data);
//            read_data(content_length-content.length(), content);
//            if(content.length() > content_length )
//            {
//                content = content.left(content_length);
//                remain_data = content.right(content.length()-content_length);
//            }
//        }
//        if((!header.contains("TP") ) || header["TP"] != "Check") emit recv_message(this);

//    }

//}

void Messenger::read()
{
    QByteArray data;
    process_header(data);

    content.clear();

    if(header.contains("TP") && header["TP"]=="file" && header["L"].toInt()>stream_threshold)
    {
        stream_flag = true;
        stream_work();
        stream_flag = false;
    }
    else
    {
        read_data(header["CL"].toInt(), content);
        if((!header.contains("TP")) || header["TP"]!="Check") emit recv_message(this);
    }
}


void Messenger::stream_work()
{
    disconnect(socket, &QTcpSocket::readyRead, this, &Messenger::read);

    QFile *opened_file = new QFile(dir_name+"/"+header["N"]);
    QDataStream *in_file;

    if(opened_file->open(QIODevice::WriteOnly))
    {
        in_file = new QDataStream(opened_file);

        int content_length = header["CL"].toInt();

        double read_length = 0;

        double size_mb = header["L"].toDouble()/(1024.0*1024.0);

        while(header["index"]!="-1")
        {
            read_data(content_length, content);
            read_length += (double) in_file->writeRawData(content, content.size());  //这里忽略了writeRawData可能失败，或不完整的问题
            opened_file->flush();

            emit stream(header["N"], size_mb, read_length/header["L"].toDouble(), IP, port);

            QByteArray data;

            process_header(data);

            content_length = header["CL"].toInt();
            content.clear();
        }

        read_data(content_length, content);
        read_length += (double) in_file->writeRawData(content, content.size());

        opened_file->flush();
        opened_file->close();
        delete in_file;
        delete opened_file;

        emit stream(header["N"], size_mb, read_length/header["L"].toDouble(), IP, port);
    }

    connect(socket, &QTcpSocket::readyRead, this, &Messenger::read);
}


void Messenger::read_data(int length, QByteArray &data)
{
    // 我觉得应该相信这个函数可以读出恰好需要的字节数的内容
    if(!stream_flag) disconnect(socket, &QTcpSocket::readyRead, this, &Messenger::read);

    while(data.length()<length)
    {
        data.append(socket->read(length-data.length()));
        if(data.length()<length) while(!socket->waitForReadyRead());
    }

    if(!stream_flag) connect(socket, &QTcpSocket::readyRead, this, &Messenger::read);
}

void Messenger::write_data(QByteArray &data)
{
    while(data.length()>0)
    {
        int len = socket->write(data);
        socket->flush();
        data = data.right(data.length()-len);
    }

}


int Messenger::Byte2Int(const QByteArray &data)
{
    uint16_t res = (((uint16_t) data[1])<<8) + ((uint16_t) data[0]);
    return ((int) res);
}

QByteArray Messenger::Int2Byte(const int &length)
{
    uint16_t s = (uint16_t) length;
    QByteArray data;
    data.resize(2);
    data[0] = (s & 255);
    data[1] = (s >> 8);
    return data;
}

void Messenger::parse_header(QString &header_string)
{
    header.clear();
    QStringList data = header_string.split(";");
    for(int i=0; i<data.length(); i++)
    {
        QStringList part = data.at(i).split(":");
        header.insert(part.at(0), part.at(1));
    }

}

void Messenger::connect_done()
{
    emit connect_success(this);
}

void Messenger::socket_error(QAbstractSocket::SocketError error)
{
    switch (error) {
    case QAbstractSocket::ConnectionRefusedError :
        emit connect_fail(this);
        break;
    case QAbstractSocket::RemoteHostClosedError :
        emit connect_close(this);
        break;
    case QAbstractSocket::SocketAccessError :
        emit connect_close(this);
        break;
    case QAbstractSocket::SocketTimeoutError :
        emit connect_fail(this);
        break;

    default:
        qDebug() << error;
    }
}

void Messenger::show_header1(const QMap<QString, QString> &head)
{
    QMapIterator<QString, QString> i(head);
    while (i.hasNext()) {
        i.next();
        qDebug() << "my" << i.key() << ": " << i.value();
    }
}
