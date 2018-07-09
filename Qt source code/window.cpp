#include "window.h"
#include "ui_window.h"
#include "options.h"
#include "devices.h"
#include "communicate.h"
#include "layout.h"
#include "info.h"
#include "ui_options.h"
#include "ui_communicate.h"
#include "ui_devices.h"
#include "ui_info.h"

#include <QStackedWidget>
#include <QSettings>
#include <QDebug>
#include <QThread>
#include <QFileDialog>
#include <QDir>

#include <QRect>

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{

    qRegisterMetaType<std::vector<Device_info> >("std::vector<Device_info>");

    setAcceptDrops(true);  //允许文件拖拽至界面，不仅需要设置dragenterevent和dropevent还要设置允许drop
    talk_page->ui->message_box->setAcceptDrops(false);

    ui->setupUi(this);

    QDir *di = new QDir;
    if(!di->exists("inbox"))
    {
        di->mkdir("inbox");
    }


    stack = new QStackedWidget(this);

    stack->addWidget(option_page);   //页面0, 设置页面
    stack->addWidget(info_page);     //页面1, 关于页面
    stack->addWidget(devices_page);  //页面2, 设备列表页面
    stack->addWidget(talk_page);     //页面3, 通讯页面
    stack->resize(430,440);

    Layout *lay = new Layout;
    lay->addWidget(ui->option, 1);
    lay->addWidget(ui->about, 1);
    lay->addWidget(ui->min, 2);
    lay->addWidget(ui->close, 2);
    lay->addWidget(stack, 3);

    this->setLayout(lay);

    show_devices_page();


    connect(ui->option, &QPushButton::clicked, this, &Window::show_config_page);
    connect(ui->about, &QPushButton::clicked, this, &Window::show_about_page);
    connect(ui->min, &QPushButton::clicked, this, &Window::showMinimized);
    connect(ui->close, &QPushButton::clicked, QApplication::instance(), &QApplication::quit);

    connect(option_page->ui->option_confirm, &QPushButton::clicked, this, &Window::change_conf);
    connect(option_page->ui->cancle, &QPushButton::clicked, this, &Window::check_status_for_about_page);
    connect(info_page->ui->info_ok, &QPushButton::clicked, this, &Window::check_status_for_about_page);

    this->setMouseTracking(true);
    this->press = false;
    this->move_press = false;

    QDesktopWidget *desktop = QApplication::desktop();
    this->screen = desktop->screenGeometry();
    set_area(QRect(0,0,this->geometry().width(),40));

    server = new Server;
    QThread *thread2 = new QThread;
    server->moveToThread(thread2);
    thread2->start();
    connect(this, &Window::set_server_info, server, &Server::set_info);
    connect(this, &Window::make_server_off_line, server, &Server::off_line);
    connect(server, &Server::connect_success, this, &Window::get_client);
    connect(this, &Window::send_data, server, &Server::send_data);
    connect(server, &Server::send_file_length_change, this, &Window::set_bar);
    //connect(server, &Server::report_port, this, &Window::get_report_port);
    emit set_server_info(63834);

    ip_server = new IP_Handler;
    QThread *one_thread = new QThread;
    ip_server->moveToThread(one_thread);
    one_thread->start();
    connect(this, &Window::set_ip_handler_info, ip_server, &IP_Handler::set_info);
    //connect(ui->submmit, &QPushButton::clicked, ip_server, &IP_Handler::report_status);
    connect(this, &Window::make_ip_server_off_line, ip_server, &IP_Handler::off_line);
    connect(ip_server, &IP_Handler::send_devices, this, &Window::update_devices);

    read_conf();
    emit set_ip_handler_info(ip_server_ip, my_id, ip_server_port, my_server_port);

    connect(devices_page->ui->devices_list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(click_item(QListWidgetItem*)));

    connect(talk_page->ui->send, &QPushButton::clicked, this, &Window::send_message_or_file);
    connect(talk_page->ui->choose_file, &QPushButton::clicked, this, &Window::choose_file);

    QFile file(":/style/style.css");
    file.open(QFile::ReadOnly);
    QString stylesheet = tr(file.readAll());
    qApp->setStyleSheet(stylesheet);
    file.close();

}

Window::~Window()
{
    delete ui;
    emit make_ip_server_off_line();
    emit make_server_off_line();
    emit make_client_off_line();
}

void Window::client_connect_to_server()
{
    client_get_connect_success = true;
    if(client_get_connect_success && server_get_connect_success)
    {
        filename = "";
        show_commu_page();
    }
}

void Window::set_bar(int length)
{
    talk_page->ui->progress->setValue(length);
    //qDebug() << "进度："<<length;
}


void Window::get_client(QString ip)
{
    Device_info a = find_partner(ip, "ip");
    if(!(a.ID=="") && !client_alreay_connect_with_server)
    {
        make_client(a);
    }
    server_get_connect_success = true;
    if(client_get_connect_success && server_get_connect_success)
    {
        filename = "";
        show_commu_page();
    }
}

void Window::get_report_port(int port)
{
    my_server_port = port;
    emit set_ip_handler_info(ip_server_ip, my_id, ip_server_port, my_server_port);
}


void Window::show_config_page()
{
    stack->setCurrentIndex(0);
    read_conf();
}

void Window::show_about_page()
{
    stack->setCurrentIndex(1);
}

void Window::show_devices_page()
{
    stack->setCurrentIndex(2);
}

void Window::show_commu_page()
{
    stack->setCurrentIndex(3);
}


void Window::change_conf()
{
    ip_server_ip = option_page->ui->IP->text();
    my_id = option_page->ui->ID->text();
    ip_server_port = option_page->ui->Port->text().toInt();

    QSettings *conf_file = new QSettings("./config.ini", QSettings::IniFormat);
    conf_file->setValue("/Info/server-ip", ip_server_ip);
    conf_file->setValue("/Info/ID", my_id);
    conf_file->setValue("/Info/server-port", ip_server_port);
    conf_file->sync();

    delete conf_file;



    if(server_get_connect_success && client_get_connect_success)
    {
        //filename = "";
        show_commu_page();
    }
    else
    {
        emit set_ip_handler_info(ip_server_ip, my_id, ip_server_port, my_server_port);
        show_devices_page();
    }
}

void Window::read_conf()
{
    QSettings *conf_file = new QSettings("./config.ini", QSettings::IniFormat);
    ip_server_ip = conf_file->value("/Info/server-ip").toString();
    my_id = conf_file->value("/Info/ID").toString();
    ip_server_port = conf_file->value("/Info/server-port").toInt();

    delete conf_file;

    option_page->ui->IP->setText(ip_server_ip);
    option_page->ui->ID->setText(my_id);
    option_page->ui->Port->setText(QString::number(ip_server_port));
}



void Window::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(QColor(240,240,240,240)));
    painter.setPen(Qt::transparent);
    QRect rect1 = rect();
    rect1.setWidth(rect1.width()-1);
    rect1.setHeight(rect1.height()-1);
    painter.drawRoundedRect(rect1, 6, 6);
    //painter.fillRect(rect1, QColor(240,240,240,240));
}

void Window::mousePressEvent(QMouseEvent *e)
{
    if(e->buttons() == Qt::LeftButton && this->area.contains(e->pos()))
    {
        this->move_press = true;
        this->old_pos = e->pos();
        this->window_pos = this->pos();
    }
    if(e->buttons() == Qt::LeftButton)
    {
        this->press = true;
        this->change_old_pos = e->pos();
    }
}

void Window::mouseReleaseEvent(QMouseEvent *e)
{
    this->press = false;
    this->move_press = false;
}

void Window::mouseMoveEvent(QMouseEvent *e)
{
    if(this->move_press)
    {
        move(this->pos()+e->pos()-this->old_pos);
    }
}

void Window::set_area(QRect a)
{
    area = a;
}



void Window::dragEnterEvent(QDragEnterEvent *e)
{
    if(e->mimeData()->hasUrls())
    {
        e->acceptProposedAction();
    }
    else e->ignore();
}

void Window::dropEvent(QDropEvent *e)
{
    const QMimeData *d = e->mimeData();
    if(d->hasUrls())
    {
        QList<QUrl> urls = d->urls();
        filename = urls.at(0).toLocalFile();
        if(!filename.isEmpty())
        {
            //qDebug() << filename;
            send_file_message_flage = filename;
            talk_page->ui->message_box->setText(send_file_message_flage);
        }
    }
}

void Window::update_devices(std::vector<Device_info> devices)
{
    QString information = "";

    int length = (int)devices.size();
    for(int i=0; i<length; i++)
    {
        Device_info one = devices[i];
        information += one.ID + "  " + one.IP + "  " + QString::number(one.port) + "\n";
        int l2 = (int) all_devices.size();
        bool has_already = false;
        for(int j=0; j<l2; j++)
        {
            if(all_devices[j].IP==one.IP) has_already=true;
        }
        if(!has_already) all_devices.push_back(one);
    }
    //qDebug() << information;

    devices_page->ui->devices_list->clear();
    length = (int) all_devices.size();
    for(int i=0; i<length; i++)
    {
        Device_info one = all_devices[i];
        devices_page->ui->devices_list->addItem(new QListWidgetItem(one.ID));
    }
}

void Window::click_item(QListWidgetItem *it)
{
    QString id = it->text();
    //qDebug() << id;
    Device_info one = find_partner(id, "id");
    if(!(one.IP=="") && !client_alreay_connect_with_server)
    {
        make_client(one);
    }
}

Device_info Window::find_partner(QString data, QString data_type)
{
    int length = (int) all_devices.size();
    if(data_type=="ip")
    {
        for(int i=0; i<length; i++)
        {
            Device_info one = all_devices[i];
            if(one.IP==data) return one;
        }
    }
    if(data_type=="id")
    {
        for(int i=0; i<length; i++)
        {
            Device_info one = all_devices[i];
            if(one.ID==data) return one;
        }
    }
    return Device_info{"","", 0};
}

void Window::make_client(Device_info a)
{
    client = new Client;
    QThread *thread3 = new QThread;
    client->moveToThread(thread3);
    thread3->start();
    connect(this, &Window::set_client_info, client, &Client::set_info);
    connect(this, &Window::make_client_off_line, client, &Client::off_line);
    connect(client, &Client::get_data, this, &Window::get_data);
    connect(client, &Client::connect_success, this, &Window::client_connect_to_server);
    connect(client, &Client::recv_file_length_change, this, &Window::set_bar);

    emit set_client_info(a.IP, a.port);

    client_alreay_connect_with_server = true;

    //qDebug()<< "already make client " << a.IP << a.port;

}

void Window::get_data(QString content, QString content_type)
{
    //qDebug() << content_type << content;
    message_history += "\r\n recive: " + content_type + "  "+content;
    talk_page->ui->show->setText(message_history);
}

void Window::check_status_for_about_page()
{
    if(server_get_connect_success && client_get_connect_success)
    {
        filename = "";
        show_commu_page();
    }
    else show_devices_page();
}

void Window::send_message_or_file()
{
    QString message = talk_page->ui->message_box->toPlainText();
    if(filename.size()>0 && message==send_file_message_flage)
    {
        emit send_data(filename, "file");
        message_history += "\r\nsend "+filename;
        filename = "";
    }
    else
    {
        emit send_data(message, "message");
        message_history += "\r\n"+message;
        talk_page->ui->message_box->setText("");
    }
    talk_page->ui->show->setText(message_history);
}

void Window::choose_file()
{
    filename = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("Choose one file"),"C:/");
    //qDebug() << filename;
    send_file_message_flage = filename;
    talk_page->ui->message_box->setText(send_file_message_flage);

    //emit send_data(filename, "file");
}
