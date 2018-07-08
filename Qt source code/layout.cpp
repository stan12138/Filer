#include "layout.h"

Layout::Layout(QWidget *parent, int spacing)
    : QLayout(parent)
{
    flage = spacing;
}

Layout::Layout(int spacing)
{
    flage = spacing;
}

Layout::~Layout()
{
    QLayoutItem *l;
    while ((l = takeAt(0)))
        delete l;
}

void Layout::addItem(QLayoutItem* item)
{
    list.append(new SI(item, 1));
    numl = numl+1;
}

int Layout::count() const
{
    return list.size();
}

void Layout::addWidget(QWidget* widget, int p)
{
    if(p==1)
    {
        list.append(new SI(new QWidgetItem(widget), p));
        numl = numl + 1;
    }
    else if(p==2)
    {
        list.append(new SI(new QWidgetItem(widget), p));
        numr = numr + 1;
    }
    else if(p==3)
    {
        list.append(new SI(new QWidgetItem(widget), p));
        numm = numm + 1;
    }

}

QLayoutItem *Layout::itemAt(int index) const
{
    if(index >= 0 && index < list.size())
    {	SI *wrapper = list.value(index);
        return wrapper->item;
    }
    else
        return 0;
}

void Layout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);
    int i;
    int lorder=0;
    int rorder=0;
    for(i=0; i<list.size(); ++i)
    {
        SI *wrapper = list.at(i);
        QLayoutItem *item = wrapper->item;
        int order = wrapper->order;

        if(order==1)
        {
            item->setGeometry(QRect(10+lorder*40, 10, 30, 30));
            lorder = lorder + 1;
        }
        else if(order==2)
        {
            item->setGeometry(QRect(rect.width()-(numr-rorder)*40, 10, 30 ,30));
            rorder = rorder + 1;
        }
        else if(order==3)
        {
            item->setGeometry(QRect(10, 50, rect.width()-20, rect.height()-60));
        }

    }

}



QSize Layout::sizeHint() const
{
    QSize a(1,1);
    return a;
}

QLayoutItem *Layout::takeAt(int index)
{
    if (index >= 0 && index < list.size()) {
        SI *wrapper = list.takeAt(index);
        return wrapper->item;
    }
    return 0;
}
