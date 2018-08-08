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
    double jump;  //скачек величиной 4-10% от среднего уровня сигнала базовое значение для определения времени свертывания
    double mix_t; //время в течение которго происходит перемешивание реагента с плазмой и успокоение жидкости
signals:

public slots:
};

class CalcKo1 : public CalcData
{
public:
    explicit CalcKo1(QMap<double, double>);
    double calc() override;
};

class CalcKo2 : public CalcData
{
public:
    explicit CalcKo2(QMap<double, double>);
    double calc() override;
};

class CalcKo3 : public CalcData
{
public:
    explicit CalcKo3(QMap<double, double>);
    double calc() override;
};

class CalcKo4 : public CalcData
{
public:
    explicit CalcKo4(QMap<double, double>);
    double calc() override;
};

class CalcKo5 : public CalcData
{
public:
    explicit CalcKo5(QMap<double, double>);
    double calc() override;
};

class CalcAgr1 : public CalcData
{
public:
    explicit CalcAgr1(QMap<double, double>);
    double calc() override;
};

class CalcAgr2 : public CalcData
{
public:
    explicit CalcAgr2(QMap<double, double>);
    double calc() override;
};

#endif // CALCULATEDATA_H
