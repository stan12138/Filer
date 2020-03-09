#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    ipclient = new IPClient;
    server = new MyServer;
    client = new MyClient;

    my_port = server->generate_server();

    ipclient->begin();

    connect(ipclient, &IPClient::connect_fail, this, &Controller::ipclient_connect_fail);
    connect(ipclient, &IPClient::connect_success, this, &Controller::ipclient_connect_success);
    connect(ipclient, &IPClient::online_devices_update, this, &Controller::ipclient_update_devices);



//    connect(this, &Controller::beign_server, server, &MyServer::generate_server);
    connect(server, &MyServer::connect_success, this, &Controller::server_connect_partner_success);
    connect(server, &MyServer::connect_fail, this, &Controller::server_connect_partner_fail);
    connect(server, &MyServer::partner_close, this, &Controller::server_partner_close);
    connect(server, &MyServer::recv_message, this, &Controller::recv_message);
    connect(server, &MyServer::recv_file_process, this, &Controller::recv_file_process);
    connect(server, &MyServer::send_file_process, this, &Controller::send_file_process);
//    connect(server, &MyServer::server_success, this, &Controller::server_success_port);

//    connect(&server_thread, &QThread::finished, server, &QObject::deleteLater);

    connect(client, &MyClient::connect_success, this, &Controller::client_connect_partner_success);
    connect(client, &MyClient::connect_fail, this, &Controller::client_connect_partner_fail);
    connect(client, &MyClient::partner_close, this, &Controller::client_partner_close);
    connect(client, &MyClient::recv_message, this, &Controller::recv_message);
    connect(client, &MyClient::recv_file_process, this, &Controller::recv_file_process);
    connect(client, &MyClient::send_file_process, this, &Controller::send_file_process);

//    connect(&client_thread, &QThread::finished, client, &QObject::deleteLater);

//    ip_thread.start();
//    server_thread.start();
//    client_thread.start();

//    emit beign_server();

}

Controller::~Controller()
{
//    ip_thread.quit();
//    ip_thread.wait();

//    server_thread.quit();
//    server_thread.wait();

//    client_thread.quit();
//    client_thread.wait();

    delete ipclient;
    delete server;
    delete client;
}

//void Controller::server_success_port(int port)
//{
//    qDebug() << "set info";
//    if(port != my_port)
//    {
//        if(my_id != "")
//        {
//            ipclient->set_info(my_id, port);
//        }
//        my_port = port;
//        qDebug() << "recv port" << port;
//        ipclient->begin();
//    }

//}

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
    this->my_id = my_id;
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
    Device a = {the_ip, "unknow", the_port};
    connect_devices.append(a);
    emit new_partner_signal(the_ip, the_port);
}

void Controller::server_connect_partner_fail(QString the_ip, int the_port)
{
    emit connect_partner_fail_signal(the_ip, the_port);
}

void Controller::server_partner_close(QString the_ip, int the_port)
{
    int aim_index = -1;
    for(int i=0; i<connect_devices.size(); i++)
    {
        if(connect_devices.at(i).IP==the_ip && connect_devices.at(i).port==the_port)
        {
            aim_index = i;
            break;
        }
    }
    if(aim_index!=-1) connect_devices.removeAt(aim_index);
    emit partner_close_signal(the_ip, the_port);
}


void Controller::client_connect_partner_success(QString the_ip, int the_port)
{
    Device a = {the_ip, "unknow", the_port};
    connect_devices.append(a);
    emit new_partner_signal(the_ip, the_port);
}

void Controller::client_connect_partner_fail(QString the_ip, int the_port)
{
    emit connect_partner_fail_signal(the_ip, the_port);
}

void Controller::client_partner_close(QString the_ip, int the_port)
{
    int aim_index = -1;
    for(int i=0; i<connect_devices.size(); i++)
    {
        if(connect_devices.at(i).IP==the_ip && connect_devices.at(i).port==the_port)
        {
            aim_index = i;
            break;
        }
    }
    if(aim_index!=-1) connect_devices.removeAt(aim_index);
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
