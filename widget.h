#ifndef WIDGET_H
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
    void setTestMode(bool);

private:
    bool eventFilter(QObject *watched, QEvent *event);
    void setupRealtimeData();
    void setupTimers();
    void startProgressBarTimer(QString format, int timer_tic_ms, int time_ms);

    void startIncub();
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
    void impulse(int n);

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
    void updateProgressValue();

private:
    Ui::Widget *ui;
    QPointer<StartMeasurment> startWin;
    QCustomPlot *customPlot1;
    QCustomPlot *customPlot2;
    QCustomPlot *customPlot3;
    QCustomPlot *customPlot4;

    QTimer progressTimer, plotTimer, currentTimer;
    QDateTime dt;

    volatile bool data1, data2, data3, data4;
    bool incub;
    bool pulse1, pulse2, pulse3, pulse4;

    QVector<double> x;
    QMap<double, double> map_y1, map_y2, map_y3, map_y4 ;
    QVector<double> y1, y2, y3, y4;

    SaveFiles saveFiles;
    int num;
};

#endif // WIDGET_H
