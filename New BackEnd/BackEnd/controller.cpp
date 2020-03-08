#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    ipclient = new IPClient;
    server = new MyServer;
    client = new MyClient;

    while(!server->generate_server(QHostAddress::AnyIPv4, my_port))
    {
        my_port += 1;
    }
    ipclient->begin();

    connect(ipclient, &IPClient::connect_fail, this, &Controller::ipclient_connect_fail);
    connect(ipclient, &IPClient::connect_success, this, &Controller::ipclient_connect_success);
    connect(ipclient, &IPClient::online_devices_update, this, &Controller::ipclient_update_devices);

    connect(server, &MyServer::connect_success, this, &Controller::server_connect_partner_success);
    connect(server, &MyServer::connect_fail, this, &Controller::server_connect_partner_fail);
    connect(server, &MyServer::partner_close, this, &Controller::server_partner_close);
    connect(server, &MyServer::recv_message, this, &Controller::recv_message);
    connect(server, &MyServer::recv_file_process, this, &Controller::recv_file_process);
    connect(server, &MyServer::send_file_process, this, &Controller::send_file_process);

    connect(client, &MyClient::connect_success, this, &Controller::client_connect_partner_success);
    connect(client, &MyClient::connect_fail, this, &Controller::client_connect_partner_fail);
    connect(client, &MyClient::partner_close, this, &Controller::client_partner_close);
    connect(client, &MyClient::recv_message, this, &Controller::recv_message);
    connect(client, &MyClient::recv_file_process, this, &Controller::recv_file_process);
    connect(client, &MyClient::send_file_process, this, &Controller::send_file_process);

}

Controller::~Controller()
{
    ipclient->stop();
    delete ipclient;
    delete server;
    delete client;
}

void Controller::send_message(QString message, QString aim_ip, int aim_port)
{
    QMap<QString, QString> head;
    head.insert("info", message);
    server->send(head, NULL, aim_ip, aim_port);
    client->send(head, NULL, aim_ip, aim_port);
}

void Controller::send_file(QString filename, QString aim_ip, int aim_port)
{
    server->send_file(filename, aim_ip, aim_port);
    client->send_file(filename, aim_ip, aim_port);
}


void Controller::add_connect(QString aim_ip, int aim_port)
{
    client->add_connection(aim_ip, aim_port);
}

void Controller::set_ID(QString my_id)
{
    ipclient->set_info(my_id, my_port);
}


void Controller::set_server_info(QString aim_ip, int port)
{
    ipclient->connect_ipserver(aim_ip, port);
}


void Controller::ipclient_connect_fail()
{
    emit connect_ipserver_fail();
}

void Controller::ipclient_connect_success()
{
    emit connect_ipserver_success();
}

void Controller::ipclient_update_devices(QList<Device> devices)
{
    emit online_devices(devices);
}

void Controller::server_connect_partner_success(QString the_ip, int the_port)
{
//    connect_devices.append()
    emit new_partner_signal(the_ip, the_port);
}

void Controller::server_connect_partner_fail(QString the_ip, int the_port)
{
    emit connect_partner_fail_signal(the_ip, the_port);
}

void Controller::server_partner_close(QString the_ip, int the_port)
{
    emit partner_close_signal(the_ip, the_port);
}


void Controller::client_connect_partner_success(QString the_ip, int the_port)
{
    emit new_partner_signal(the_ip, the_port);
}

void Controller::client_connect_partner_fail(QString the_ip, int the_port)
{
    emit connect_partner_fail_signal(the_ip, the_port);
}

void Controller::client_partner_close(QString the_ip, int the_port)
{
    emit partner_close_signal(the_ip, the_port);
}


void Controller::recv_message(QString message, QString the_ip, int the_port)
{
    emit recv_message_signal(message, the_ip, the_port);
}
void Controller::recv_file_process(QString filename, QString the_ip, int the_port, double process, double size_mb)
{
    emit recv_file_signal(filename, the_ip, the_port, process, size_mb);
}
void Controller::send_file_process(QString filename, QString the_ip, int the_port, double process, double size_mb)
{
    emit send_file_signal(filename, the_ip, the_port, process, size_mb);
}
