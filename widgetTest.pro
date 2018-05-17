#-------------------------------------------------
#
# Project created by QtCreator 2018-03-01T13:55:23
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   =    widgetTest
TEMPLATE =  app


SOURCES +=  main.cpp\
            widget.cpp \
    useE154.cpp \
    LoadDll.cpp \
    loademodule.cpp

HEADERS  += widget.h \
    useE154.h \
    LoadDll.h \
    loademodule.h

FORMS    += widget.ui
