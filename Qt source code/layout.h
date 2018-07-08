#ifndef LAYOUT_H
#define LAYOUT_H

#include <QtWidgets>
#include <QList>
#include <QLayout>
#include <QRect>


class Layout : public QLayout
{
    public :
        explicit Layout(QWidget *parent, int spacing = 0);
        Layout(int spaceing=0);
        ~Layout();

        void addItem(QLayoutItem *item);
        void addWidget(QWidget* widget, int p);


        QLayoutItem *itemAt(int index) const;
        QLayoutItem *takeAt(int index);
        QSize sizeHint() const;
        int count() const;
        void setGeometry(const QRect &rect);
    private :
        struct SI
        {
            SI(QLayoutItem* i, int p)
            {
                item = i;
                order = p;
            }
            QLayoutItem * item;
            int order;
        };
        QList<SI *> list;
        int numl=0;
        int numr=0;
        int numm=0;
        int flage=1;
};

#endif // LAYOUT_H
