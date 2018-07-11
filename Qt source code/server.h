#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

signals:
    void connect_success(QString ip);
    void send_file_length_change(int length);
    void send_done();
    void report_port(int port);

public slots:
    void start();
    void set_info(int port);
    void set_delay(int delay);
    void off_line();

    void send_data(QString data, QString content_type);

private:
    int port=63834;
    int send_delay=50;

    QTcpServer *server = NULL;
    QTcpSocket *client = NULL;

    void get_connect();

};

#endif // SERVER_H
