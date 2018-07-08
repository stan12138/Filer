#include "communicate.h"
#include "ui_communicate.h"

Communicate::Communicate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Communicate)
{
    ui->setupUi(this);
}

Communicate::~Communicate()
{
    delete ui;
}
