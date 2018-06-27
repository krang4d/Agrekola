#-------------------------------------------------
#
# Project created by QtCreator 2018-03-01T13:55:23
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   =    widgetTest
TEMPLATE =  app

INCLUDEPATH += ./choisedialog

SOURCES +=  main.cpp\
            widget.cpp \
    useE154.cpp \
    LoadDll.cpp \
    loademodule.cpp \
    selectcalibrationagr1.cpp \
    selectinductor.cpp \
    measurement.cpp \
    testkoagr.cpp \
    mainwindow.cpp \
    param.cpp \
    viewplot.cpp \
    kalibragr2.cpp \
    viewgraph.cpp \
    choisedialog/agr1.cpp \
    choisedialog/agr2.cpp \
    choisedialog/choisedialog.cpp \
    choisedialog/ko1.cpp \
    choisedialog/ko2.cpp \
    choisedialog/ko3.cpp \
    choisedialog/ko4.cpp \
    choisedialog/ko5.cpp \
    startmeasurment.cpp

HEADERS  += widget.h \
    useE154.h \
    LoadDll.h \
    loademodule.h \
    selectcalibrationagr1.h \
    selectinductor.h \
    measurement.h \
    testkoagr.h \
    mainwindow.h \
    param.h \
    viewplot.h \
    kalibragr2.h \
    viewgraph.h \
    choisedialog/agr1.h \
    choisedialog/agr2.h \
    choisedialog/choisedialog.h \
    choisedialog/ko1.h \
    choisedialog/ko2.h \
    choisedialog/ko3.h \
    choisedialog/ko4.h \
    choisedialog/ko5.h \
    startmeasurment.h

FORMS    += widget.ui \
    selectcalibrationagr1.ui \
    selectinductor.ui \
    measurement.ui \
    testkoagr.ui \
    mainwindow.ui \
    param.ui \
    viewplot.ui \
    kalibragr2.ui \
    viewgraph.ui \
    choisedialog/agr1.ui \
    choisedialog/agr2.ui \
    choisedialog/choisedialog.ui \
    choisedialog/ko1.ui \
    choisedialog/ko2.ui \
    choisedialog/ko3.ui \
    choisedialog/ko4.ui \
    choisedialog/ko5.ui \
    startmeasurment.ui

RESOURCES += \
    rcfile.qrc
