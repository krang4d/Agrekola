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
#include <progresstimerbar.h>
#include "calculatedata.h"
#include "impulewaiter.h"
#include "startmeasurment.h"
#include "options.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    Widget(StartMeasurment *, QWidget *parent = 0);
    ~Widget();
    void setUserMessage(QString, bool withtime = 1, bool tofile = 1);
    inline void setMode(Mode_ID m)  { id = m; }
    inline void setMode(int i) {
        switch (i) {
        case 0:
            setMode(Test_ID);
            break;
        case 1:
            setMode(Agr1_ID);
            break;
        case 2:
            setMode(Agr2_ID);
            break;
        case 3:
            setMode(Ko1_ID);
            break;
        case 4:
            setMode(Ko2_ID);
            break;
        case 5:
            setMode(Ko3_ID);
            break;
        case 6:
            setMode(Ko4_ID);
            break;
        case 7:;
            setMode(Ko5_ID);
            break;
        case 8:
            setMode(Level_ID);
            break;
        default:
            break;
        }
    }
    void setStartWindow(StartMeasurment*);
    inline Mode_ID getMode()     { return id; }
    inline bool isSensorReady()  { return termoSensor; } //проверка тепловой готовности

    void stopIncub();
    bool isIncub();

    void stopData(int);
    bool isData(int = 0);

protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void setupRealtimeData();
    void setupTimers();
    void setupWidget();

protected slots:
    void incubeTimeout_0();
    void incubeTimeout();

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

    void stopData1();
    void stopData2();
    void stopData3();
    void stopData4();

    void ret_value1(double);
    void ret_value2(double);
    void ret_value3(double);
    void ret_value4(double);

//    void btp_done();
//    void otp_done();
    void done();

public slots:
    void startMeasurment();
    void startMeasurment(StartMeasurment *);
    void startIncub(int num);
    void startData(int);
    void getLevelBTP();
    void getLevelOTP();

private slots:
    void realtimeDataSlot(QVariantList);
    double writeMapData(int n = 0);

    void on_checkBox_1_stateChanged(int arg1);
    void on_checkBox_2_stateChanged(int arg1);
    void on_checkBox_3_stateChanged(int arg1);
    void on_checkBox_4_stateChanged(int arg1);
    void on_checkBox_PP_stateChanged(int arg1);
    void on_checkBox_L_stateChanged(int arg1);
    void on_pushButton_clicked();

    void updataTermo(bool);
    void updateTime();

    void on_comboBox_currentIndexChanged(int index);

public:
    QPointer<StartMeasurment> startWin;
    QPointer<QCustomPlot> customPlot1, customPlot2, customPlot3, customPlot4;
    QPointer<ProgressTimerBar> pBar1, pBar2, pBar3, pBar4;

private:
    Ui::Widget *ui;
    QTimer plotTimer, currentTimer;
    QDateTime dt;

    volatile bool data1, data2, data3, data4;
    bool pulse1, pulse2, pulse3, pulse4;
    bool ready1, ready2, ready3, ready4;
    bool termoSensor;
    bool incub;

    QMap<double, double> map_y1, map_y2, map_y3, map_y4 ;
    QVector<double> btp, otp;
    SaveFiles saveFiles;
    int mode;
    Mode_ID id;
    double Start_DX; //порог запуска
    double Stop_DX;  //порог остановки
    double MIN, MAX;
    friend class Options;
};

class Agregometr  : public QObject
{
    Q_OBJECT
public:
    Agregometr(Widget *);

public slots:
    void start();

private:
    Widget *widget;
};

#endif // WIDGET_H
