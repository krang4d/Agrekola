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
    void setupQuadraticPlot(QVector<double> data = {0});
    void setupRealtimeData();
    void setupTimers();
    void startProgressBarTimer(QString format, int timer_tic_ms, int time_ms);

    void startData();
    void stopData();
    bool isData();

    void startIncub();
    void stopIncub();
    bool isIncub();

signals:
    void onmixch1(bool);
    void onmixch2(bool);
    void onmixch3(bool);
    void onmixch4(bool);
    void onmixpp(bool);
    void onlaser(bool);
    void status(QString);
    void stop();            //сигнал для остановки потока измерений

public slots:
    void getData();
    void incubeTimeout();

private slots:
    void realtimeDataSlot(QVariantList);
    void writeData();

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
    StartMeasurment *startWin;
    QCustomPlot *customPlot1;
    QCustomPlot *customPlot2;
    QCustomPlot *customPlot3;
    QCustomPlot *customPlot4;

    QTimer progressTimer, plotTimer, currentTimer;
    QDateTime dt;

    volatile bool data;
    bool incub;

    QVector<double> x;
    QVector<double> y1, y2, y3, y4;
    int progress_t; //время измерния

    SaveFiles saveFiles;
};

#endif // WIDGET_H
