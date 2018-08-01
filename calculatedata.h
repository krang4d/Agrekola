#ifndef CALCULATEDATA_H
#define CALCULATEDATA_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QMap>
#include <numeric>

class CalculateData : public QObject
{
    Q_OBJECT

public:
    explicit CalculateData(QObject *parent = 0);
    CalculateData(QMap<double, double>, QObject *parent = 0);
    virtual double calc();

protected:
    QMap<double, double> mdata;
    double jump;  //скачек величиной 4-10% от среднего уровня сигнала базовое значение
    double mix_t; //время в течение которго происходит перемешивание реагента с плазмой и успокоение жидкости

signals:

public slots:
};

class CalculateKo1 : public CalculateData
{
public:
    explicit CalculateKo1(QMap<double, double>);
    double calc() override;
};

#endif // CALCULATEDATA_H
