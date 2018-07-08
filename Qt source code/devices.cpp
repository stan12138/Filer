#include "devices.h"
#include "ui_devices.h"

Devices::Devices(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Devices)
{
    ui->setupUi(this);
}

Devices::~Devices()
{
    delete ui;
}
