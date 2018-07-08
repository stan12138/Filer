#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QString>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);


signals:
    void connect_success();
    void get_data(QString content, QString content_type);
    void recv_file_length_change(int length);

public slots:
    void start();
    void set_info(QString ip, int port);
    void off_line();

private :
    QString ip;
    int port;

    QString message;
    QString filename;
    int times;
    long long file_size;

    QTcpSocket *client = NULL;

    void connect_ok();
    void recv_data();

    void parse_data(QString data, QString content_type);

};

#endif // CLIENT_H
