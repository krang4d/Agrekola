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

enum Mode_ID {Test_ID = 0, Agr1_ID, Agr2_ID, Ko1_ID, Ko2_ID, Ko3_ID, Ko4_ID, Ko5_ID, Level_ID };

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
    QString info() override;
    double calc(QMap<double, double>) override;
    QString getParameters() override;
};

class CalcKo1 : public CalcData
{
public:
    explicit CalcKo1();
    explicit CalcKo1(QCustomPlot*);

    //параметры для определения времени свертывания
private:

    // CalcData interface
public:
    QString info() override;
    double calc(QMap<double, double>) override;
    QString getParameters() override;
};

class CalcKo2 : public CalcData
{
public:
    explicit CalcKo2();

    //параметры для определения АЧТВ
private:
    double t0;                      // АЧТВ контрольной плазмы

    // CalcData interface
public:
    double calc(QMap<double, double>) override;
    QString info() override;
   // void getCalibrationDeta(double &c1, double &c2, double &c3, double &c4) override;
    QString getParameters() override;
};

class CalcKo3 : public CalcData
{
public:
    explicit CalcKo3();

    //параметры для определения Фибриногена
private:
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
};

class CalcKo4 : public CalcData
{
public:
    explicit CalcKo4();
    double calc(QMap<double, double>) override;
    QString info() override;

    //параметры для определения Тромбина
private:
    double t0;                      // Тромбин контрольной плазмы

    // CalcData interface
public:
    QString getParameters() override;
};

class CalcKo5 : public CalcData
{
public:
    explicit CalcKo5();

    //параметры для определения Протромбинового комплекса
private:
    //константы (паспортные данные)
    const int k = 4;                //часло калибровочных точек
    //протромбиновое отношение плазмы калибратора
    double a100;                      //протромбин по Квику (100%) контрольнной плазмы
    double po1;                     //протромбиновое отношение
    double pi1;                     //протромбиновый индекс
    //калибровочные параметры
    double t100, t50, t25, t12;          //время свертывания для каждого разведения, t100 - контр. плазма (протромбиновое время)
    //искомые величины
    double a50, a25, a12;              //разведение 50% 25%, 12.5%
    double tgalfa, tgalfa1, tgalfa2;
    double tgalfa3, tgalfa4;        //угол наклона k-ого участка калибровочной кривой
    double lgax;                    //искомая величиан ax = 10^lgax
    double pox;                     //протромбиновое отношене
    double pix;                     //протромбиновый индекс

    // CalcData interface
public:
    double calc(QMap<double, double>) override;
    QString info() override;
    QString getParameters() override;
};

class CalcAgr1 : public CalcData
{
public:
    explicit CalcAgr1();
    CalcAgr1(QCustomPlot *p);

    //параметры для определения Агрегации
private:
    double btp;                     //богатая тромбоцитами плазма
    double otp;                     //обогащенная тромбоцитами плазма

    // CalcData interface
public:
    double calc(QMap<double, double>) override;
    QString info() override;
    QString getParameters() override;
};

class CalcAgr2 : public CalcData
{
public:
    explicit CalcAgr2();

    //параметры для определения ф-ра Виллебранда
private:
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
};

#endif // CALCULATEDATA_H
