#ifndef INFO_H
#define INFO_H

#include <QWidget>

namespace Ui {
class Info;
}

class Info : public QWidget
{
    Q_OBJECT

public:
    explicit Info(QWidget *parent = 0);
    ~Info();
    Ui::Info *ui;
};

#endif // INFO_H
