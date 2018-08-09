#ifndef CALCULATEDATA_H
#define CALCULATEDATA_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QMap>
#include <numeric>
#include <savefiles.h>

class CalcData : public QObject
{
    Q_OBJECT
public:
    explicit CalcData(QObject *parent = 0);
    CalcData(QMap<double, double>, QObject *parent = 0);
    virtual double calc();

protected:
    QStringList param;
    QMap<double, double> mdata;
    double jump;                    //скачек величиной 4-10% от среднего уровня сигнала базовое значение для определения времени свертывания
    double mix_t;                   //время в течение которго происходит перемешивание реагента с плазмой и успокоение жидкости
signals:

public slots:
};

class CalcKo1 : public CalcData
{
public:
    explicit CalcKo1(QMap<double, double>);
    double calc() override;

private:
    //параметры для определения времени свертывания
};

class CalcKo2 : public CalcData
{
public:
    explicit CalcKo2(QMap<double, double>);
    double calc() override;

private:
    //параметры для определения АЧТВ
    double tk;                      // АЧТВ контрольной плазмы
};

class CalcKo3 : public CalcData
{
public:
    explicit CalcKo3(QMap<double, double>);
    double calc() override;

private:
    //параметры для определения Фибриногена


};

class CalcKo4 : public CalcData
{
public:
    explicit CalcKo4(QMap<double, double>);
    double calc() override;

private:
    //параметры для определения Тромбина
    double tk;                      // АЧТВ контрольной плазмы
};

class CalcKo5 : public CalcData
{
public:
    explicit CalcKo5(QMap<double, double>);
    double calc() override;

private:
    //параметры для определения Протромбинового комплекса
    //константы (паспортные данные)
    const int k = 4;                //часло калибровочных точек
    //протромбиновое отношение плазмы калибратора
    double a1;                      //протромбин по Квику
    double po1;                     //протромбиновое отношение
    double pi1;                     //протромбиновый индекс
    //калибровочные параметры
    double t1, t2, t3, t4;          //время свертывания для каждого разведения, t1 - контр. плазма (протромбиновое время)
    //искомые величины
    double a2, a3, a4;              //разведение 100%, 50% 25%, 12.5%
    double tgalfa, tgalfa1, tgalfa2, tgalfa3, tgalfa4;  //угол наклона k-ого участка калибровочной кривой
    double lgax;                    //искомая величиан ax = 10^lgax
    double pox;                     //протромбиновое отношене
    double pix;                     //протромбиновый индекс
};

class CalcAgr1 : public CalcData
{
public:
    explicit CalcAgr1(QMap<double, double>);
    double calc() override;

private:
    //параметры для определения Агрегации
};

class CalcAgr2 : public CalcData
{
public:
    explicit CalcAgr2(QMap<double, double>);
    double calc() override;

private:
    //параметры для определения ф-ра Виллебранда
};

#endif // CALCULATEDATA_H
