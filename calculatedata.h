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
    virtual void calc()  = 0;

protected:
    QMap<double, double> mdata;

signals:

public slots:
};

class CalculateArg1 : public CalculateData
{
public:
    CalculateArg1() {}
    void calc() override;
};

#endif // CALCULATEDATA_H
