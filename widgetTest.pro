#-------------------------------------------------
#
# Project created by QtCreator 2018-03-01T13:55:23
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET   =  widgetTest
TEMPLATE =  app

SOURCES +=  main.cpp\
            widget.cpp \
    useE154.cpp \
    LoadDll.cpp \
#    chartdir/qchartviewer.cpp \
#    chartdir/realtimedemo.cpp
    QCustomPlot/qcustomplot.cpp

HEADERS  += widget.h \
    useE154.h \
    LoadDll.h \
#    chartdir/qchartviewer.h \
#    chartdir/realtimedemo.h
    libapi/Lusbapi.h \
    libapi/LusbapiTypes.h \
    QCustomPlot/qcustomplot.h

FORMS    += widget.ui

#RESOURCES += \
#    chartdir/realtimedemo.qrc

INCLUDEPATH += libapi
QMAKE_POST_LINK = copy /Y libapi\\Lusbapi.dll $(DESTDIR)

#INCLUDEPATH += chartdir/include

#DEFINES += CHARTDIR_HIDE_OBSOLETE _CRT_SECURE_NO_WARNINGS

#win32:contains(QMAKE_HOST.arch, x86_64) {
#  LIBS += -L$$PWD/chartdir/lib64/ -lchartdir60
#  QMAKE_POST_LINK = copy /Y chartdir\\lib64\\chartdir60.dll $(DESTDIR)
#} else {
#  LIBS += -L$$PWD/chartdir/lib32/ -lchartdir60
#  QMAKE_POST_LINK = copy /Y chartdir\\lib32\\chartdir60.dll $(DESTDIR)
#}

#win32:CONFIG(release, debug|release): -L$$PWD/chartdir/lib32/ -lchartdir60
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/chartdir/lib32/ -lchartdir60d

#INCLUDEPATH += $$PWD/chartdir/lib32
#DEPENDPATH += $$PWD/chartdir/lib32

DISTFILES += \
    libapi/Lusbapi.dll \
    rcfiles/pause.png \
    rcfiles/play.png \
    .gitignore
