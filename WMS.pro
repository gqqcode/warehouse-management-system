#-------------------------------------------------
#
# Project created by QtCreator 2015-11-06T16:24:51
#
#-------------------------------------------------

QT       += core gui
QT       +=sql
QT       +=xlsx
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WMS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    customsmanage.cpp \
    stockmanagement.cpp \
    goodsmanagement.cpp \
    warehouseanagement.cpp \
    mylineedit.cpp \
    importexcelthread.cpp \
    stockselect.cpp \
    warehouseselect.cpp \
    otherstockselect.cpp \
    otherwarehouseselect.cpp \
    storgeselect.cpp \
    exportexcelthread.cpp \
    login.cpp \
    alterpasswd.cpp

HEADERS  += mainwindow.h \
    customsmanage.h \
    stockmanagement.h \
    goodsmanagement.h \
    warehouseanagement.h \
    mylineedit.h \
    importexcelthread.h \
    stockselect.h \
    warehouseselect.h \
    otherstockselect.h \
    otherwarehouseselect.h \
    storgeselect.h \
    exportexcelthread.h \
    login.h \
    alterpasswd.h

RESOURCES += \
    mainImage.qrc



