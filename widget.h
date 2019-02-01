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
#include "startmeasurement.h"
#include "QCustomPlot/qcustomplot.h"
#include <progresstimerbar.h>
#include "calculatedata.h"
#include "impulewaiter.h"
#include "startmeasurement.h"
#include "options.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    Widget(StartMeasurement *, QWidget *parent = 0);
    ~Widget();

    void setUserMessage(QString, bool withtime = true, bool tofile = true);

    inline void setMode(Mode_ID m)  { id = m; }
    inline Mode_ID getMode()     { return id; }

    void setStartWindow(StartMeasurement*);

    inline bool isSensorReady()
    {
        return termoSensor;
    } //проверка тепловой готовности


    inline void stopIncub()
    {
        incub = false;
    }

    inline bool isIncub()
    {
        return incub;
    }


    void stopData(int);
    bool isData(int = 0);

    inline bool isWaitPulse() { return waitPulse; }

protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void setupRealtimeData();
    void setupTimers();
    void setupWidget();

public slots:
    void incubeTimeout_1();
    void incubeTimeout_2();
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

    void ret_value1(double);
    void ret_value2(double);
    void ret_value3(double);
    void ret_value4(double);
    void done();

public slots:
    //void startMeasurment();
    void startMeasurment(StartMeasurement *);
    void startIncub(int num);
    void getData(int);
    void getLevelBTP();
    void getLevelOTP();

private slots:

    void on_pushButton_clicked();

    void realtimeDataSlot(QVariantList);
    double writeMapData(int n = 0);

    void on_checkBox_1_stateChanged(int arg1);
    void on_checkBox_2_stateChanged(int arg1);
    void on_checkBox_3_stateChanged(int arg1);
    void on_checkBox_4_stateChanged(int arg1);
    void on_checkBox_PP_stateChanged(int arg1);
    void on_checkBox_L_stateChanged(int arg1);


    void updataTermo(bool);
    void updateTime();

    void on_comboBox_currentIndexChanged(int index);

public:
    StartMeasurement *startWin;
    QPointer<QCustomPlot> customPlot1, customPlot2, customPlot3, customPlot4;
    QPointer<ProgressTimerBar> pBar1, pBar2, pBar3, pBar4;

private:
    Ui::Widget *ui;
    QTimer plotTimer, currentTimer;
    QDateTime dt;

    volatile bool data1, data2, data3, data4;
    bool pulse1, pulse2, pulse3, pulse4;
    bool ready1, ready2, ready3, ready4;
    bool termoSensor, incub, waitPulse;

    QMap<double, double> map_y1, map_y2, map_y3, map_y4 ;
    QVector<double> btp, otp;
    SaveFiles saveFiles;
    Mode_ID id;
    double Start_DX; //порог запуска
    double Stop_DX;  //порог остановки
    double MIN, MAX;

    friend class Options;
    friend class DoThis;
};

class DoThis{

//    Widget *obj;
//    DoThis *self;

//public:
//    DoThis(Widget *obj);
//    virtual ~DoThis();

//protected:
//    void output(QString text) {
//        obj->setUserMessage(text);
//    }
};

class Incubation : public DoThis {
//    Incubation(Widget *obj);
//    virtual ~Incubation();
//    void Go();

};

#endif // WIDGET_H
