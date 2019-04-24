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
#include "selectinductor.h"
#include "itools.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget, public ITools
{
    Q_OBJECT

public:
    explicit Widget(StartMeasurement *sm, QWidget *parent = 0);
    ~Widget();
    void setupWidget();
    void setUserMessage(QString, bool withtime = true, bool tofile = true);

    inline bool isSensorReady() {
        return termoSensor;
    } //проверка тепловой готовности

    void stopData(Channel_ID);
    bool isData(Channel_ID);

    // ITools interface
    double getSTART_DX() const override;
    void setSTART_DX(double value) override;
    double getSTOP_DX() const override;
    void setSTOP_DX(double value) override;
    double getMIN() const override;
    void setMIN(double value) override;
    double getMAX() const override;
    void setMAX(double value) override;

signals:
    //сигналы управления потоком E154
    void onmixch1(bool);    ///вкл/выкл перемешивания канал 1
    void onmixch2(bool);    ///вкл/выкл перемешивания канал 2
    void onmixch3(bool);    ///вкл/выкл перемешивания канал 3
    void onmixch4(bool);    ///вкл/выкл перемешивания канал 4
    void onmixpp(bool);     ///вкл/выкл перемешивания канал рр
    void onlaser(bool);     ///вкл/выкл лазеров
    void status(QString);
    void stop();            ///сигнал для остановки потока измерений

    //возвращаемые значения при одиночных пробах
    void ret_value1(double, int);
    void ret_value2(double, int);
    void ret_value3(double, int);
    void ret_value4(double, int);

    //возвращаемые значения при парных пробах
    void ret_value1_2(double, int);
    void ret_value3_4(double, int);

    //возвращаемые БТП значения
    void btp_value1(double);
    void btp_value2(double);
    void btp_value3(double);
    void btp_value4(double);

    //возвращаемые ОТП значения
    void otp_value1(double);
    void otp_value2(double);
    void otp_value3(double);
    void otp_value4(double);

    //сигналы для сбора данных в realTime
    void hasPulse1();
    void hasPulse2();
    void hasPulse3();
    void hasPulse4();

    void done1();
    void done2();
    void done3();
    void done4();

    void done();
    void incube_timeout();
    void end();

public slots:
    void startIncub(int num, double time_s, std::function<void(void)> timeout_fun = NULL);
    void getData(Channel_ID, double time_s);
    double calcData(Channel_ID, Mode_ID);
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

private:
    Ui::Widget *ui;
    QTimer plotTimer, currentTimer;
    QDateTime dt;

    StartMeasurement *startWin;
    QCustomPlot *customPlot1, *customPlot2, *customPlot3, *customPlot4;
    ProgressTimerBar *pBar1, *pBar2, *pBar3, *pBar4;
    Mode_ID current_mode_id;
    State *state;
    bool single;

    volatile bool data1, data2, data3, data4;
    bool pulse1, pulse2, pulse3, pulse4;
    bool termoSensor, incub;

    QMap<double, double> map_y1, map_y2, map_y3, map_y4 ;
    SaveFiles saveFiles;

    //опциональные параметры
    double START_DX; //порог запуска
    double STOP_DX;  //порог остановки
    double MIN, MAX; //минимум и максимум на графике
    //friend class Options;

    // QWidget interface
protected:
    void showEvent(QShowEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;
};
#endif // WIDGET_H
