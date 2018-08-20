﻿#ifndef WIDGET_H
#define WIDGET_H

#include <QString>
#include <QVector>
#include <QWidget>
#include <QTimer>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

#include "savefiles.h"
#include "startmeasurment.h"
#include "QCustomPlot/qcustomplot.h"
#include "impulewaiter.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void setUserMessage(QString, bool withtime = 1, bool tofile = 1);
    void setMode(int);
    int getMode();

private:
    bool eventFilter(QObject *watched, QEvent *event);
    void setupRealtimeData();
    void setupTimers();

    void startIncub(int time_sec, int num);
    void stopIncub();
    bool isIncub();

    void startData(int);
    void stopData(int);
    bool isData(int);

signals:
    void onmixch1(bool);
    void onmixch2(bool);
    void onmixch3(bool);
    void onmixch4(bool);
    void onmixpp(bool);
    void onlaser(bool);
    void status(QString);
    void stop();            //сигнал для остановки потока измерений
    void hasPulse1();
    void hasPulse2();
    void hasPulse3();
    void hasPulse4();

public slots:
    void getData();
    void incubeTimeout();

private slots:
    void realtimeDataSlot(QVariantList);
    void writeData(const int n = 0);
    void writeMapData(const int n = 0);

    void on_checkBox_1_stateChanged(int arg1);
    void on_checkBox_2_stateChanged(int arg1);
    void on_checkBox_3_stateChanged(int arg1);
    void on_checkBox_4_stateChanged(int arg1);
    void on_checkBox_PP_stateChanged(int arg1);
    void on_checkBox_L_stateChanged(int arg1);
    void on_pushButton_clicked();

    void updataTermo(bool);
    void updateTime();

private:
    Ui::Widget *ui;
    QPointer<StartMeasurment> startWin;
    QCustomPlot *customPlot1;
    QCustomPlot *customPlot2;
    QCustomPlot *customPlot3;
    QCustomPlot *customPlot4;

    QTimer plotTimer, currentTimer;
    QDateTime dt;

    volatile bool data1, data2, data3, data4;
    bool incub;
    bool pulse1, pulse2, pulse3, pulse4;
    bool ready1, ready2, ready3, ready4;

    QVector<double> x;
    QMap<double, double> map_y1, map_y2, map_y3, map_y4 ;
    QVector<double> y1, y2, y3, y4;

    SaveFiles saveFiles;
    int mode;
};

//class ProgressBar : QProgressBar
//{
//    Q_OBJECT

//public:
//    explicit ProgressBar(QWidget *parent = 0);
//    void startProgressBarTimer(QString format, int timer_tic_ms, int time_ms);
//    ~ProgressBar();
//private:
//    QTimer progressTimer;

//signals:

//public slots:
//    void updateProgressValue();

//};

#endif // WIDGET_H
