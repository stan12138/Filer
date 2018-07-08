#ifndef DEVICES_H
#define DEVICES_H

#include <QWidget>

namespace Ui {
class Devices;
}

class Devices : public QWidget
{
    Q_OBJECT

public:
    explicit Devices(QWidget *parent = 0);
    ~Devices();

    Ui::Devices *ui;
};

#endif // DEVICES_H
