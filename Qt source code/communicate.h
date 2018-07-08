#ifndef COMMUNICATE_H
#define COMMUNICATE_H

#include <QWidget>

namespace Ui {
class Communicate;
}

class Communicate : public QWidget
{
    Q_OBJECT

public:
    explicit Communicate(QWidget *parent = 0);
    ~Communicate();
    Ui::Communicate *ui;
};

#endif // COMMUNICATE_H
