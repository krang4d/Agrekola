#include "calculatedata.h"
#include <QtMath>

CalculateData::CalculateData(QObject *parent) : QObject(parent)
{
    jump = 0.04f;
    mix_t = 4.0f;
}

CalculateData::CalculateData(QMap<double, double> map, QObject *parent) : CalculateData(parent)
{
    mdata = map;
}

double CalculateData::calc()
{
    QMap<double, double>::const_iterator it = mdata.begin();
    QMap<double, double>::const_iterator state;
    double sum = 0;
    int num = 0;

    while(it != mdata.end()) {
        if((it.key() - mdata.begin().key()) > mix_t) {
            state = it;
            qDebug().noquote() << QString("key = %1, value = %2").arg(it.key()).arg(it.value());
            break;
        }
        ++it;
    }
    while(it != mdata.end()) {
        num ++;
        sum += it.value();
        ++it;
    }
    double avg = sum/num;
    double over = avg*jump;

    while(state != mdata.end()) {
        if( avg-state.value() >= over ) {
            qDebug() << "state != mdata.end()";
            break;
        }
        qDebug() << QString("%1").arg(avg - state.value());
        ++state;
    }
    qDebug().noquote() << QString("sum = %1, ikey = %2, avg = %3")
                          .arg(sum).arg(state.key()).arg(sum/num);
    return state.key();
}

CalculateKo1::CalculateKo1(QMap<double, double> map) : CalculateData(map)
{
/*скачек величиной 4-10% от среднего уровня сигнала для определения времени свертывания*/
    //jump = 0.04f;
}

double CalculateKo1::calc()
{
    double k = CalculateData::calc() - 1;
    qDebug() << "CalculateArg1::calc() " << k;
    return k;
}
