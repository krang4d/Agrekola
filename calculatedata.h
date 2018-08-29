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

enum Mode_ID {Test_ID = 0, Agr1_ID, Agr2_ID, Ko1_ID, Ko2_ID, Ko3_ID, Ko4_ID, Ko5_ID };

class CalcData : public QObject
{
    Q_OBJECT
public:
    explicit CalcData();
    CalcData(QMap<double, double>, QCustomPlot *p = NULL);
    virtual ~CalcData() {}

    double calcKo(QMap<double, double>);
    double calcAgr(QMap<double, double>);
    static CalcData* createCalc( Mode_ID );

    virtual double calc(QMap<double, double>) = 0;

protected:
    QMap<double, double> mdata;
    QCustomPlot *plot;
    QStringList param;
    double jump;                    //скачек величиной 4-10% от среднего уровня сигнала базовое значение для определения времени свертывания
    double mix_t;                   //время в течение которго происходит перемешивание реагента с плазмой и успокоение жидкости

signals:

public slots:
};

class CalcKo1 : public CalcData
{
public:
    explicit CalcKo1();
    explicit CalcKo1(QCustomPlot*);
    double
    calc(QMap<double, double>);

private:
    //параметры для определения времени свертывания
};

class CalcKo2 : public CalcData
{
public:
    explicit CalcKo2();
    double calc(QMap<double, double>);

private:
    //параметры для определения АЧТВ
    double t0;                      // АЧТВ контрольной плазмы
};

class CalcKo3 : public CalcData
{
public:
    explicit CalcKo3();
    double calc(QMap<double, double>);

private:
    //параметры для определения Фибриногена
    const int k = 4;                //часло калибровочных точек
    double c2;                      //Содержание фибриногена по Клауссу (100%)
    double c1, c3, c4;              //Концентрация фибриногена других разведений 200%, 50%, 25%
    double t1, t2, t3, t4;          //время свертывания для каждого разведения, t2 - контр. плпзма
    double tgalfa, tgalfa1, tgalfa2;
    double tgalfa3, tgalfa4;        //угол наклона k-ого участка калибровочной кривой
    double lgcx;                    //искомая величиан ax = 10^lgcx
};

class CalcKo4 : public CalcData
{
public:
    explicit CalcKo4();
    double calc(QMap<double, double>);

private:
    //параметры для определения Тромбина
    double t0;                      // Тромбин контрольной плазмы
};

class CalcKo5 : public CalcData
{
public:
    explicit CalcKo5();
    double calc(QMap<double, double>);

private:
    //параметры для определения Протромбинового комплекса
    //константы (паспортные данные)
    const int k = 4;                //часло калибровочных точек
    //протромбиновое отношение плазмы калибратора
    double a1;                      //протромбин по Квику (100%)
    double po1;                     //протромбиновое отношение
    double pi1;                     //протромбиновый индекс
    //калибровочные параметры
    double t1, t2, t3, t4;          //время свертывания для каждого разведения, t1 - контр. плазма (протромбиновое время)
    //искомые величины
    double a2, a3, a4;              //разведение 50% 25%, 12.5%
    double tgalfa, tgalfa1, tgalfa2;
    double tgalfa3, tgalfa4;        //угол наклона k-ого участка калибровочной кривой
    double lgax;                    //искомая величиан ax = 10^lgax
    double pox;                     //протромбиновое отношене
    double pix;                     //протромбиновый индекс
};

class CalcAgr1 : public CalcData
{
public:
    explicit CalcAgr1();
    CalcAgr1(QCustomPlot *p);
    double calc(QMap<double, double>);

private:
    //параметры для определения Агрегации
    double btp;                     //богатая тромбоцитами плазма
    double otp;                     //обогащенная тромбоцитами плазма
};

class CalcAgr2 : public CalcData
{
public:
    explicit CalcAgr2();
    double calc(QMap<double, double>);

private:
    //параметры для определения ф-ра Виллебранда
    const int kt = 3;               //часло калибровочных точек
    double btp;                     //богатая тромбоцитами плазма
    double otp;                     //обогащенная тромбоцитами плазма
    double c1;                      //активность фактора Виллебранда контр. плазмы (100%)
    double c2, c3, c4;              //активность фактора Виллебранда других разведений 50%, 25%
    double ck1, ck2, ck3;           //значение скорости агрегации
    double tgalfa, tgalfa1;
    double tgalfa2, tgalfa3;        //угол наклона k-ого участка калибровочной кривой
    double lgcx;                    //искомая величиан ax = 10^lgcx
};

#endif // CALCULATEDATA_H
