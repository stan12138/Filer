#-------------------------------------------------
#
# Project created by QtCreator 2018-07-06T17:42:13
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Filer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        window.cpp \
    layout.cpp \
    options.cpp \
    devices.cpp \
    communicate.cpp \
    info.cpp \
    ip_handler.cpp \
    server.cpp \
    client.cpp

HEADERS += \
        window.h \
    layout.h \
    options.h \
    devices.h \
    communicate.h \
    info.h \
    my_datatype.h \
    ip_handler.h \
    server.h \
    client.h

FORMS += \
        window.ui \
    options.ui \
    devices.ui \
    communicate.ui \
    info.ui

RESOURCES += \
    resource.qrc

RC_ICONS = Filer.ico
