#-------------------------------------------------
#
# Project created by QtCreator 2018-03-01T13:55:23
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport concurrent

TARGET   =  widgetTest
TEMPLATE =  app

INCLUDEPATH += libapi
#QMAKE_POST_LINK = copy /Y libapi\\Lusbapi.dll $(DESTDIR)

#DEFINES += QCUSTOMPLOT_USE_OPENGL

INCLUDEPATH += ./choisedialog \
               ./QCustomPlot

SOURCES +=  main.cpp\
    selectcalibrationagr1.cpp \
    selectinductor.cpp \
    testkoagr.cpp \
    mainwindow.cpp \
    param.cpp \
    viewplot.cpp \
    kalibragr2.cpp \
    choisedialog/agr1.cpp \
    choisedialog/agr2.cpp \
    choisedialog/choisedialog.cpp \
    choisedialog/ko1.cpp \
    choisedialog/ko2.cpp \
    choisedialog/ko3.cpp \
    choisedialog/ko4.cpp \
    choisedialog/ko5.cpp \
    startmeasurment.cpp  \
    widget.cpp \
    useE154.cpp \
    LoadDll.cpp \
    QCustomPlot/qcustomplot.cpp \
    savefiles.cpp

HEADERS  += selectcalibrationagr1.h \
    selectinductor.h \
    testkoagr.h \
    mainwindow.h \
    param.h \
    viewplot.h \
    kalibragr2.h \
    choisedialog/agr1.h \
    choisedialog/agr2.h \
    choisedialog/choisedialog.h \
    choisedialog/ko1.h \
    choisedialog/ko2.h \
    choisedialog/ko3.h \
    choisedialog/ko4.h \
    choisedialog/ko5.h \
    startmeasurment.h  \
    widget.h \
    useE154.h \
    LoadDll.h \
    libapi/Lusbapi.h \
    libapi/LusbapiTypes.h \
    QCustomPlot/qcustomplot.h \
    savefiles.h

FORMS    += selectcalibrationagr1.ui \
    selectinductor.ui \
    testkoagr.ui \
    mainwindow.ui \
    param.ui \
    viewplot.ui \
    kalibragr2.ui \
    choisedialog/agr1.ui \
    choisedialog/agr2.ui \
    choisedialog/choisedialog.ui \
    choisedialog/ko1.ui \
    choisedialog/ko2.ui \
    choisedialog/ko3.ui \
    choisedialog/ko4.ui \
    choisedialog/ko5.ui \
    startmeasurment.ui \
    widget.ui

RESOURCES += \
    rcfile.qrc

DISTFILES += \
    libapi/Lusbapi.dll \
    rcfiles/pause.png \
    rcfiles/play.png
