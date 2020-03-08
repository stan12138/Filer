#ifndef MESSENGER_H
#define MESSENGER_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QByteArray>
#include <QMap>

#include <QAbstractSocket>
#include <QHostAddress>

class Messenger : public QObject
{
    Q_OBJECT
public:
    explicit Messenger(QTcpSocket *client, QString the_ip, int the_port, QObject *parent = nullptr);
    void close();
    void send(QMap<QString, QString> &the_header, const QByteArray &data=NULL);

    QString IP;    //远端的IP
    int port;     //远端端口
    int stream_threshold = 1024*1204*10;  //接收的文件大小超过此阈值的时候将会放弃信号触发的方式，流式读取数据(算流式吗？)

    QString my_ip = "";  //本地IP
    QString dir_name = "/Users/hanyi02/Desktop";  //流式传输时文件存储目录

    QMap<QString, QString> header;
    QByteArray content;

signals:
    void recv_message(Messenger *messenger);
    void connect_success(Messenger *messenger);
    void connect_fail(Messenger *messenger);
    void connect_close(Messenger *messenger);

    void stream(QString name, double size_mb, double process, QString the_ip, int the_port);   //流式传输时发送的信号


private:
    QTcpSocket *socket = nullptr;

    bool stream_flag = false;

    QByteArray remain_data;  //现行版本这个量无用

    void read();

    void read_data(int length, QByteArray &data);

    void write_data(QByteArray &data);

    int Byte2Int(const QByteArray &data);

    QByteArray Int2Byte(const int &length);

    void parse_header(QString &header_string);

    void connect_done();

    void socket_error(QAbstractSocket::SocketError error);

    void show_header1(const QMap<QString, QString> &head);

    void stream_work();

    void process_header(QByteArray &data);

};

#endif // MESSENGER_H
