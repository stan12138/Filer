#ifndef DATATYPE_H
#define DATATYPE_H
#include <QString>
#include <QMetaType>

struct Device
{
    QString IP;
    QString ID;
    int port;
};

Q_DECLARE_METATYPE(Device);
#endif // DATATYPE_H
