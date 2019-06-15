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
#include "iscenario.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget, public ITools, public IScenario
{
    Q_OBJECT

public:
    explicit Widget(StartMeasurement *sm, QWidget *parent = nullptr);
    ~Widget() override;

    inline bool isSensorReady() {
        return termoSensor;
    } //проверка тепловой готовности

    void stopData(Channel_ID);
    //bool isData(Channel_ID);

    inline bool isCalib() {
        auto x = startWin->getModeID();
        return x == CalibKo2_ID || x == CalibKo3_ID || x == CalibKo4_ID || x == CalibKo5_ID || x == CalibAgr2_ID;
    }
    inline bool isKo() {
        auto x = startWin->getModeID();
        return x == CalibAgr2_ID ? false : true;
    }

    // ITools interface
    double getMIN() const override;
    void setMIN(double value) override;
    double getMAX() const override;
    void setMAX(double value) override;
    double getMIX() const override;
    void setMIX(double value) override;

    double getSTART_DX1() const override;
    void setSTART_DX1(double value) override;
    double getSTART_DX2() const override;
    void setSTART_DX2(double value) override;
    double getSTART_DX3() const override;
    void setSTART_DX3(double value) override;
    double getSTART_DX4() const override;
    void setSTART_DX4(double value) override;
    double getSTOP_DX1() const override;
    void setSTOP_DX1(double value) override;
    double getSTOP_DX2() const override;
    void setSTOP_DX2(double value) override;
    double getSTOP_DX3() const override;
    void setSTOP_DX3(double value) override;
    double getSTOP_DX4() const override;
    void setSTOP_DX4(double value) override;

    // IScenario interface
    void getBTP() override;
    void getOTP() override;
    void onMixChls(bool) override;
    void onMixPP(bool) override;
    void onLazer(bool) override;
    void incubation1(State*) override;
    void incubation2(State*) override;
    void selectInductor(State*) override;
    void finish() override;
    void agr() override;
    void ko(State*) override;
    void calc() override;
    void write() override;

private:
    void setupWidget();

public slots:
    void setUserMessage(QString, bool withtime = true, bool tofile = true);
    void startIncub(int num, double time_s, std::function<void(void)> timeout_fun = nullptr);
    void getData(Channel_ID, double time_s);
    double calcData(CalcData *p, Channel_ID);
    void writeMapData(Channel_ID);
    void incubeTimeout_1();
    void incubeTimeout_2();
    void waitImpulse(ImpuleWaiter *iw);
    void onMotor(Channel_ID, bool arg);
    void test();

private slots:
    void on_pushButton_clicked();
    void realtimeDataSlot(QVariantList);
    void fix_point(QVariantList);
    void updataTermo(bool);
    void updateTime();
    void doScenario();

signals:
    //сигналы управления потоком E154
    void onmixch1(bool);                ///вкл/выкл перемешивания канал 1
    void onmixch2(bool);                ///вкл/выкл перемешивания канал 2
    void onmixch3(bool);                ///вкл/выкл перемешивания канал 3
    void onmixch4(bool);                ///вкл/выкл перемешивания канал 4
    void onmixpp(bool);                 ///вкл/выкл перемешивания канал рр
    void onlaser(bool);                 ///вкл/выкл лазеров
    void status(const QString&);
    void stop();                        ///сигнал для остановки потока измерений
    void save_data(QStringList);        ///сигнал для записи массива данных

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
    void value_come(QVariantList);
    void incube_timeout();
    void end(QMap<double, double>,QMap<double, double>,QMap<double, double>,QMap<double, double>);

private:
    Ui::Widget *ui;
    QThread save_thread;
    QVariantList fixed_point;

    QTime time;
    StartMeasurement *startWin;
    QCustomPlot *customPlot1, *customPlot2, *customPlot3, *customPlot4;
    ProgressTimerBar *pBar1, *pBar2, *pBar3, *pBar4;
    //Mode_ID current_mode_id;
    State *state;
    Options *tool;

    volatile bool data1, data2, data3, data4;
    bool pulse1, pulse2, pulse3, pulse4;
    bool termoSensor, incub;

    QMap<double, double> map_y1, map_y2, map_y3, map_y4;
    SaveFiles saveFiles;

    //опциональные параметры
    double START_DX1, START_DX2, START_DX3, START_DX4; //порог запуска доля от единицы
    double STOP_DX1, STOP_DX2, STOP_DX3, STOP_DX4;  //порог остановки доля от единицы
    double MIN, MAX; //минимум и максимум на графике вольт
    double MIX_TIME_MS; //время перемешвания мс

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
};
#endif // WIDGET_H
