#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QStackedWidget>
#include <QListWidgetItem>
#include <QString>

#include <QDragEnterEvent>
#include <QUrl>
#include <QFile>
#include <QTextStream>
#include <QMimeData>
#include <vector>


#include "options.h"
#include "devices.h"
#include "info.h"
#include "communicate.h"

#include "my_datatype.h"
#include "ip_handler.h"
#include "server.h"
#include "client.h"


namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();


public slots:
    void click_item(QListWidgetItem* it);   //在设备选择列表中点击项目将触发这个槽函数

    void update_devices(std::vector<Device_info> devices);

    void get_client(QString ip);
    void get_report_port(int port);

    void get_data(QString content, QString content_type);
    void client_connect_to_server();
    void set_bar(int length);

signals:
    void set_ip_handler_info(QString ip, QString id, int port, int my_port);
    void make_ip_server_off_line();

    void set_server_info(int port);
    void make_server_off_line();
    void send_data(QString data, QString content_type);

    void set_client_info(QString ip, int port);
    void make_client_off_line();

private:

    //下面几个标志位和属性均为鼠标拖动服务
    bool press;
    bool move_press;
    QRect area;
    QPoint old_pos;
    QPoint window_pos;
    QPoint change_old_pos;
    QRect screen;

    Ui::Window *ui;

    QStackedWidget *stack;   //界面的切换由这个堆提供服务

    Options *option_page = new Options(this);   //四个不同的界面，分别是设置，关于，设备选择，通信
    Info *info_page = new Info(this);
    Devices *devices_page = new Devices(this);
    Communicate *talk_page = new Communicate(this);



    std::vector<Device_info> all_devices;   //所有上线设备

    IP_Handler *ip_server;
    Server *server;
    Client *client;

    bool client_alreay_connect_with_server = false;

    QString ip_server_ip;    //配置信息
    QString my_id;
    int ip_server_port;

    int my_server_port=63834;


    bool server_get_connect_success = false;
    bool client_get_connect_success = false;

    QString message_history;
    QString filename = "";   //要传输的文件的名字
    QString send_file_message_flage = "";


    void show_config_page();     //显示 设置     界面
    void show_about_page();      //显示 关于     界面
    void show_devices_page();    //显示 设备列表 界面
    void show_commu_page();      //显示 通讯     界面

    void change_conf();   //修改配置
    void read_conf();    //读取配置

    void mousePressEvent(QMouseEvent *e);     //以下三个均为鼠标拖动窗口服务
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void set_area(QRect a);   //用于实现自定义窗口拖动

    void dragEnterEvent(QDragEnterEvent *e);   //拖拽文件的服务函数
    void dropEvent(QDropEvent *e);


    Device_info find_partner(QString data, QString data_type);
    void connet_server();
    void make_client(Device_info a);

    void check_status_for_about_page();

    void send_message_or_file();
    void choose_file();
};

#endif // WINDOW_H
