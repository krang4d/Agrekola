#-------------------------------------------------
#
# Project created by QtCreator 2018-03-01T13:55:23
#
#-------------------------------------------------

QT += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport concurrent

TARGET   =  widgetTest
TEMPLATE =  app
VERSION = 1.0.0.3

INCLUDEPATH += libapi
#QMAKE_POST_LINK = copy /Y libapi\\Lusbapi.dll $(DESTDIR)

#DEFINES += QCUSTOMPLOT_USE_OPENGL

INCLUDEPATH += ./choisedialog \
               ./QCustomPlot

SOURCES +=  main.cpp\
    selectinductor.cpp \
    testkoagr.cpp \
    param.cpp \
    viewplot.cpp \
    choisedialog/agr1.cpp \
    choisedialog/agr2.cpp \
    choisedialog/choisedialog.cpp \
    choisedialog/ko1.cpp \
    choisedialog/ko2.cpp \
    choisedialog/ko3.cpp \
    choisedialog/ko4.cpp \
    choisedialog/ko5.cpp \
    widget.cpp \
    useE154.cpp \
    LoadDll.cpp \
    QCustomPlot/qcustomplot.cpp \
    savefiles.cpp \
    calculatedata.cpp \
    progresstimerbar.cpp \
    impulewaiter.cpp \
    incubation.cpp \
    options.cpp \
    calibparam.cpp \
    ../XML/KoAgrXML/koagrxml.cpp \
    startmeasurement.cpp \
    state.cpp \
    choisedialog/printer.cpp \
    choisedialog/enddialog.cpp

HEADERS  += \
    selectinductor.h \
    testkoagr.h \
    param.h \
    viewplot.h \
    choisedialog/agr1.h \
    choisedialog/agr2.h \
    choisedialog/choisedialog.h \
    choisedialog/ko1.h \
    choisedialog/ko2.h \
    choisedialog/ko3.h \
    choisedialog/ko4.h \
    choisedialog/ko5.h \
    widget.h \
    useE154.h \
    LoadDll.h \
    libapi/Lusbapi.h \
    libapi/LusbapiTypes.h \
    QCustomPlot/qcustomplot.h \
    savefiles.h \
    calculatedata.h \
    progresstimerbar.h \
    impulewaiter.h \
    incubation.h \
    options.h \
    calibparam.h \
    globalvalue.h \
    ../XML/KoAgrXML/koagrxml.h \
    startmeasurement.h \
    state.h \
    choisedialog/agr_impl.h \
    choisedialog/ko_impl.h \
    choisedialog/printer.h \
    choisedialog/enddialog.h \
    itools.h \
    iscenario.h \
    choisedialog/istartwin.h

FORMS    += \
    selectinductor.ui \
    testkoagr.ui \
    param.ui \
    viewplot.ui \
    choisedialog/agr1.ui \
    choisedialog/agr2.ui \
    choisedialog/choisedialog.ui \
    choisedialog/ko1.ui \
    choisedialog/ko2.ui \
    choisedialog/ko3.ui \
    choisedialog/ko4.ui \
    choisedialog/ko5.ui \
    widget.ui \
    progresstimerbar.ui \
    impulewaiter.ui \
    options.ui \
    calibparam.ui

RESOURCES += \
    rcfile.qrc

DISTFILES += \
    libapi/Lusbapi.dll \
    rcfiles/pause.png \
    rcfiles/play.png \
    agrekola.qmodel
