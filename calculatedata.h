#ifndef CALCULATEDATA_H
#define CALCULATEDATA_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QMap>
#include <QtMath>
#include <numeric>
#include <savefiles.h>
#include <qcustomplot.h>
#include "globalvalue.h"

//enum Mode_ID {Test_ID = 0, Agr1_ID, Agr2_ID, Ko1_ID, Ko2_ID, Ko3_ID, Ko4_ID, Ko5_ID, Level_ID };

class CalcData : public QObject
{
public:
    explicit CalcData();
    CalcData(QMap<double, double>, QCustomPlot *p = NULL);
    virtual ~CalcData() {}

    double calcKo(QMap<double, double>);
    double calcAgr(QMap<double, double>);
    static CalcData* createCalc( Mode_ID );

    //virtual void getCalibrationDeta(double &c1, double &c2,double &c3, double &c4);
    virtual double calc(QMap<double, double>) = 0;
    virtual QString info() = 0;
    virtual Mode_ID getModeID() = 0;
    virtual QString getParameters() = 0;

    void setMix_t(double sec);
    double getMix_t();

    void setDx(double dx);
    double getDx();

protected:
    QMap<double, double> mdata;
    QCustomPlot *plot;
    QStringList param;
    double dx;                    //скачек величиной 4-10% от среднего уровня сигнала базовое значение для определения времени свертывания
    double mix_t;                 //время в течение которго происходит перемешивание реагента с плазмой и успокоение жидкости
};

class CalcLevel : public CalcData
{
public:
    explicit CalcLevel();

    // CalcData interface
public:
    QString info() override;
    double calc(QMap<double, double>) override;
    QString getParameters() override;
    Mode_ID getModeID() override
    {
        return Mode_ID::Level_ID;
    }
};

class CalcKo1 : public CalcData
{
public:
    explicit CalcKo1();
    explicit CalcKo1(QCustomPlot*);

    //параметры для определения времени свертывания
private:
    TestKo1 t_ko1;
    CalibrationKo1 c_ko1;
    // CalcData interface
public:
    QString info() override;
    double calc(QMap<double, double>) override;
    QString getParameters() override;
    Mode_ID getModeID() override
    {
        return Mode_ID::TestKo1_ID;
    }
};

class CalcKo2 : public CalcData
{
public:
    explicit CalcKo2();

    //параметры для определения АЧТВ
private:
    TestKo2 t_ko2;
    CalibrationKo2 c_ko2;
    double t0;                      // АЧТВ контрольной плазмы

    // CalcData interface
public:
    double calc(QMap<double, double>) override;
    QString info() override;
   // void getCalibrationDeta(double &c1, double &c2, double &c3, double &c4) override;
    QString getParameters() override;
    Mode_ID getModeID() override
    {
        return Mode_ID::TestKo2_ID;
    }
};

class CalcKo3 : public CalcData
{
public:
    explicit CalcKo3();

    //параметры для определения Фибриногена
private:
    TestKo3 t_ko3;
    CalibrationKo3 c_ko3;
    const int k = 4;                //часло калибровочных точек
    double c2;                      //Содержание фибриногена по Клауссу (100%)
    double c1, c3, c4;              //Концентрация фибриногена других разведений 200%, 50%, 25%
    double t1, t2, t3, t4;          //время свертывания для каждого разведения, t2 - контр. плпзма
    double tgalfa, tgalfa1, tgalfa2;
    double tgalfa3, tgalfa4;        //угол наклона k-ого участка калибровочной кривой
    double lgcx;                    //искомая величиан ax = 10^lgcx

    // CalcData interface
public:
    double calc(QMap<double, double>) override;
    QString info() override;
    QString getParameters() override;
    Mode_ID getModeID() override
    {
        return Mode_ID::TestKo3_ID;
    }
};

class CalcKo4 : public CalcData
{
public:
    explicit CalcKo4();

    //параметры для определения Тромбина
private:
    TestKo4 t_ko4;
    CalibrationKo4 c_ko4;
    double t0;                      // Тромбин контрольной плазмы

    // CalcData interface
public:
    double calc(QMap<double, double>) override;
    QString info() override;
    QString getParameters() override;
    Mode_ID getModeID() override
    {
        return Mode_ID::TestKo4_ID;
    }
};

class CalcKo5 : public CalcData
{
public:
    explicit CalcKo5();
    double getIndex() {
        return pix;
    }

    double getOtn() {
        return pox;
    }

    //параметры для определения Протромбинового комплекса
private:
    TestKo5 t_ko5;
    CalibrationKo5 c_ko5;
    //константы (паспортные данные)
    const int k = 4;                //часло калибровочных точек
    //протромбиновое отношение плазмы калибратора
    double a100;                    //протромбин по Квику (100%) контрольнной плазмы
    double po1;                     //протромбиновое отношение плазмы калибратора
    double pi1;                     //протромбиновый индекс плазмы калибратора
    //калибровочные параметры
    double t100, t50, t25, t12;          //время свертывания для каждого разведения, t100 - контр. плазма (протромбиновое время)
    //искомые величины
    double a50, a25, a12;              //разведение 50% 25%, 12.5%
    double tgalfa, tgalfa1, tgalfa2;
    double tgalfa3, tgalfa4;        //угол наклона k-ого участка калибровочной кривой
    double lgax;                    //искомая величиан ax = 10^lgax
    double ax;
    double pox;                     //протромбиновое отношене ОТН
    double pix;                     //протромбиновый индекс ИНД

    // CalcData interface
public:
    double calc(QMap<double, double>) override;
    QString info() override;
    QString getParameters() override;
    Mode_ID getModeID() override
    {
        return Mode_ID::TestKo5_ID;
    }
};

class CalcAgr1 : public CalcData
{
public:
    explicit CalcAgr1();
    CalcAgr1(QCustomPlot *p);

    //параметры для определения Агрегации
private:
    TestAgr1 t_agr1;
    CalibrationAgr1 c_ko1;
    double btp;                     //богатая тромбоцитами плазма
    double otp;                     //обогащенная тромбоцитами плазма

    // CalcData interface
public:
    double calc(QMap<double, double>) override;
    QString info() override;
    QString getParameters() override;
    Mode_ID getModeID() override
    {
        return Mode_ID::TestAgr1_ID;
    }
};

class CalcAgr2 : public CalcData
{
public:
    explicit CalcAgr2();

    //параметры для определения ф-ра Виллебранда
private:
    TestAgr2 t_agr2;
    CalibrationKo2 c_ko2;
    const int kt = 3;               //часло калибровочных точек
    double btp;                     //богатая тромбоцитами плазма
    double otp;                     //обогащенная тромбоцитами плазма
    double c1;                      //активность фактора Виллебранда контр. плазмы (100%)
    double c2, c3, c4;              //активность фактора Виллебранда других разведений 200% 50%, 25%
    double ck1, ck2, ck3;           //значение скорости агрегации
    double tgalfa, tgalfa1;
    double tgalfa2, tgalfa3;        //угол наклона k-ого участка калибровочной кривой
    double lgcx;                    //искомая величиан ax = 10^lgcx

    // CalcData interface
public:
    double calc(QMap<double, double>) override;
    QString info() override;
    QString getParameters() override;
    Mode_ID getModeID() override
    {
        return Mode_ID::TestAgr2_ID;
    }
};

#endif // CALCULATEDATA_H
