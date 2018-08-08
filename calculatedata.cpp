#include "calculatedata.h"
#include <QtMath>

CalcData::CalcData(QObject *parent) : QObject(parent)
{
    jump = 0.04f;
    mix_t = 4.0f;
}

CalcData::CalcData(QMap<double, double> map, QObject *parent) : CalcData(parent)
{
    mdata = map;
}

double CalcData::calc()
{
    QMap<double, double>::const_iterator it = mdata.begin();
    QMap<double, double>::const_iterator state;
    double sum = 0;
    int num = 0;

    while(it != mdata.end()) {
        if((it.key() - mdata.begin().key()) > mix_t) {
            state = it;
            //qDebug().noquote() << QString("key = %1, value = %2").arg(it.key()).arg(it.value());
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
        //qDebug() << QString("%1").arg(avg - state.value());
        ++state;
    }
    qDebug().noquote() << QString("sum = %1, ikey = %2, avg = %3")
                          .arg(sum).arg(state.key()).arg(sum/num);
    return state.key();
}

CalcKo1::CalcKo1(QMap<double, double> map) : CalcData(map)
{
/*скачек величиной 4-10% от среднего уровня сигнала для определения времени свертывания*/
    //jump = 0.04f;
    SaveFiles file;
    file.openKo1(param);
    qDebug() << "параметры CalcKo1";
    for(auto it = param.begin(); it < param.end(); it++) {
        qDebug() << *it;
    }
}

double CalcKo1::calc()
{
    double k = CalcData::calc() - 1;
    qDebug() << "CalcArg1::calc() " << k;
    return k;
}

CalcKo2::CalcKo2(QMap<double, double>) : tk(1.0f)
{
    SaveFiles file;
    file.openKo1(param);
    qDebug() << "параметры CalcKo2";
    for(auto it = param.begin(); it < param.end(); it++) {
        qDebug() << *it;
    }
}

double CalcKo2::calc()
{
    return CalcData::calc()/tk;
}

CalcKo3::CalcKo3(QMap<double, double>)
{
    SaveFiles file;
    file.openKo3(param);
    qDebug() << "параметры CalcKo3";
    for(auto it = param.begin(); it < param.end(); it++) {
        qDebug() << *it;
    }
}

double CalcKo3::calc()
{
    return 0;
}

CalcKo4::CalcKo4(QMap<double, double>) : tk(1.0f)
{
    SaveFiles file;
    file.openKo4(param);
    qDebug() << "параметры CalcKo4";
    for(auto it = param.begin(); it < param.end(); it++) {
        qDebug() << *it;
    }
}

double CalcKo4::calc()
{
    return CalcData::calc()/tk;
}

CalcKo5::CalcKo5(QMap<double, double>)
{
    SaveFiles file;
    file.openKo5(param);
    qDebug() << "параметры CalcKo5";
    for(auto it = param.begin(); it < param.end(); it++) {
        qDebug() << *it;
    }
}

double CalcKo5::calc()
{
    return 0;
}

CalcAgr1::CalcAgr1(QMap<double, double>)
{
    SaveFiles file;
    file.openAgr1(param);
    qDebug() << "параметры CalcAgr1";
    for(auto it = param.begin(); it < param.end(); it++) {
        qDebug() << *it;
    }
}

double CalcAgr1::calc()
{
    return 0;
}

CalcAgr2::CalcAgr2(QMap<double, double>)
{
    SaveFiles file;
    file.openAgr2(param);
    qDebug() << "параметры CalcAgr2";
    for(auto it = param.begin(); it < param.end(); it++) {
        qDebug() << *it;
    }
}

double CalcAgr2::calc()
{
    return 0;
}
