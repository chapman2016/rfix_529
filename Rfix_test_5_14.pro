#-------------------------------------------------
#
# Project created by QtCreator 2018-05-14T16:55:57
#
#-------------------------------------------------

QT       += core gui
QT         += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Rfix_test_5_14
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    basicinfo.cpp \
    rdcase.cpp \
    dmgscale.cpp \
    form.cpp \
    infoinput.cpp \
    cal_task.cpp \
    needs.cpp \
    eqp.cpp \
    seecase.cpp \
    matcheqp.cpp \
    final.cpp \
    editconfig.cpp \
    seeeqps.cpp \
    color.cpp \
    base.cpp \
    database.cpp \
    dmgscale2.cpp \
    caselist.cpp \
    login.cpp

HEADERS += \
        mainwindow.h \
    config.h \
    basicinfo.h \
    rdcase.h \
    dmgscale.h \
    form.h \
    infoinput.h \
    cal_task.h \
    needs.h \
    eqp.h \
    seecase.h \
    matcheqp.h \
    final.h \
    editconfig.h \
    seeeqps.h \
    color.h \
    base.h \
    database.h \
    dmgscale2.h \
    caselist.h \
    login.h

FORMS += \
        mainwindow.ui \
    basicinfo.ui \
    dmgscale.ui \
    form.ui \
    infoinput.ui \
    cal_task.ui \
    needs.ui \
    seecase.ui \
    matcheqp.ui \
    final.ui \
    editconfig.ui \
    seeeqps.ui \
    color.ui \
    base.ui \
    dmgscale2.ui \
    caselist.ui \
    login.ui

DISTFILES += \
    img/button.png \
    img/base.jpg

RESOURCES += \
    res.qrc
