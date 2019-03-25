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
#include "progresstimerbar.h"
#include "calculatedata.h"
#include "impulewaiter.h"
#include "startmeasurement.h"
#include "options.h"
#include "state.h"
#include "globalvalue.h"

namespace Ui {
class Widget;
}
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void setupWidget();
    void setUserMessage(QString, bool withtime = true, bool tofile = true);

    inline bool isSensorReady() {
        return termoSensor;
    } //проверка тепловой готовности

    inline void stopIncub() {
        incub = false;
    }

    inline bool isIncub() {
        return incub;
    }

    void stopData(Channel_ID);
    bool isData(Channel_ID);

    inline bool isWaitPulse() { return waitPulse; }

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

    void btp_value1(double);
    void btp_value2(double);
    void btp_value3(double);
    void btp_value4(double);

    void otp_value1(double);
    void otp_value2(double);
    void otp_value3(double);
    void otp_value4(double);

    void done1();
    void done2();
    void done3();
    void done4();
    void done();
    void incube_timeout();
    void end();

public slots:
    void startIncub(int num, double time_s, std::function<void(void)> timeout_fun, QString message = "Время инкубации истекло");
    void getData(Channel_ID, double time_s);
    double calcData(Channel_ID);
    void writeMapData(Channel_ID);
    void incubeTimeout_1();
    void incubeTimeout_2();
    void waitImpulse(ImpuleWaiter *iw);

    void onMotor(Channel_ID, bool arg);
    void onLazer(bool arg);
    void test();

private slots:
    void on_pushButton_clicked();

    void realtimeDataSlot(QVariantList);
    void updataTermo(bool);
    void updateTime();
    void doScenario();
    void setupRealtimeData(bool single);
    void setupTimers();

public:
    StartMeasurement *startWin;
    QCustomPlot *customPlot1, *customPlot2, *customPlot3, *customPlot4;
    ProgressTimerBar *pBar1, *pBar2, *pBar3, *pBar4;
    Mode_ID current_mode_id;
    State *state;
    bool single;

private:
    Ui::Widget *ui;
    QTimer plotTimer, currentTimer;
    QDateTime dt;

    volatile bool data1, data2, data3, data4;
    bool pulse1, pulse2, pulse3, pulse4;
    bool ready1, ready2, ready3, ready4;
    bool termoSensor, incub, waitPulse;

    QMap<double, double> map_y1, map_y2, map_y3, map_y4 ;
    SaveFiles saveFiles;

    //опциональные параметры
    double START_DX; //порог запуска
    double STOP_DX;  //порог остановки
    double MIN, MAX; //минимум и максимум на графике

    friend class Options;

    // QWidget interface
protected:
    void showEvent(QShowEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;
};
#endif // WIDGET_H
