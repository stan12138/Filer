#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QDebug>
#include <QByteArray>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Btn, &QPushButton::clicked, this, &MainWindow::push);

    controller = new Controller;
    controller->set_ID("Stan-Qt");
    controller->set_server_info("127.0.0.1", 5000);

//    connect(controller, &Controller::recv_file_signal)
    connect(controller, &Controller::connect_ipserver_success, this, &MainWindow::connect_ipserver_success);
    connect(controller, &Controller::connect_ipserver_fail, this, &MainWindow::connect_ipserver_fail);
    connect(controller, &Controller::online_devices, this, &MainWindow::online_devices);

    connect(controller, &Controller::new_partner_signal, this, &MainWindow::new_partner_signal);

    connect(controller, &Controller::partner_close_signal, this, &MainWindow::partner_close_signal);

    connect(controller, &Controller::recv_message_signal, this, &MainWindow::recv_message_signal);
    connect(controller, &Controller::recv_file_signal, this, &MainWindow::recv_file_signal);

}



MainWindow::~MainWindow()
{
    delete ui;
//    delete controller;
}


void MainWindow::push()
{

}


void MainWindow::connect_ipserver_success()
{
    qDebug() << "connect ip server success";
}
void MainWindow::connect_ipserver_fail()
{
    qDebug() << "connect ip server fail!!!!!";
}
void MainWindow::online_devices(QList<Device> devices)
{
//    qDebug() << "recv devices";
}

void MainWindow::new_partner_signal(QString the_ip, int the_port)
{
    qDebug() << "get partner:  " << the_ip << ":" << the_port;
}
void MainWindow::connect_partner_fail_signal(QString the_ip, int the_port)
{
    qDebug() << "connect partner fail: "<< the_ip << ":" << the_port;
}
void MainWindow::partner_close_signal(QString the_ip, int the_port)
{
    qDebug() << "partner close: "<< the_ip << ":" << the_port;
}
void MainWindow::recv_message_signal(QString message, QString the_ip, int the_port)
{
    qDebug() << the_ip << ":" << the_port << ":---" << message;
}
void MainWindow::recv_file_signal(QString filename, QString the_ip, int the_port, double process, double size_mb)
{
    qDebug() << the_ip << ":" << the_port << "--" << filename << "(" << size_mb << "MB): "<< process;
}
void MainWindow::send_file_signal(QString filename, QString the_ip, int the_port, double process, double size_mb)
{
    qDebug() << the_ip << ":" << the_port << "--" << filename << "(" << size_mb << "MB): "<< process;
}
