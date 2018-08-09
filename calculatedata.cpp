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
    double k = CalcData::calc();
    qDebug() << "CalcArg1::calc() " << k;
    return k;
}

CalcKo2::CalcKo2(QMap<double, double> map) : CalcData(map), tk(1.0f)
{
    SaveFiles file;
    file.openKo2(param);
    qDebug() << "параметры CalcKo2";
    for(auto it = param.begin(); it < param.end(); it++) {
        qDebug() << *it;
    }
}

double CalcKo2::calc()
{
    return CalcData::calc()/tk;
}

CalcKo3::CalcKo3(QMap<double, double> map) : CalcData(map)
{
    SaveFiles file;
    file.openKo3(param);
    qDebug() << "параметры CalcKo3";
    for(auto it = param.begin(); it < param.end(); it++) {
        qDebug() << *it;
    }
    QString p = param.at(3);
    c2 = p.toDouble();
    qDebug() << "по Клауссу =" << c2;

}

double CalcKo3::calc()
{
    // <-- проверка значений калибровки
    c1 = c2*200.0f/100.0f;          //(3)
    c3 = c2*50.0f/100.0f;           //(4)
    c4 = c2*25.0f/100.0f;           //(5)

    tgalfa1 = qLn(t2/t1)/qLn(c1/c2);   //(7)
    tgalfa2 = qLn(t3/t2)/qLn(c2/c3);   //(8)
    tgalfa3 = qLn(t3/t1)/qLn(c1/c3);   //(9)
    tgalfa4 = qLn(t4/t2)/qLn(c2/c4);   //(10)
    tgalfa = ( tgalfa1 + tgalfa2 + tgalfa3 + tgalfa4 ) / k; //(6)

    lgcx = ( qLn(t2/CalcData::calc()) + qLn(c2) * tgalfa ) / tgalfa; //(11)

    return qPow(10, lgcx);
}

CalcKo4::CalcKo4(QMap<double, double> map) : CalcData(map), tk(1.0f)
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

CalcKo5::CalcKo5(QMap<double, double> map) : CalcData(map)
{
    SaveFiles file;
    file.openKo5(param);
    qDebug() << "параметры CalcKo5";
    for(auto it = param.begin(); it < param.end(); it++) {
        qDebug() << *it;
    }
    QString p = param.at(3);
    a1 = p.toDouble();
    qDebug() << "по Квику =" << a1;
}

double CalcKo5::calc()
{
    // <-- проверка значений калибровки
    a2 = a1*50.0f/100.0f;       //(12)
    a3 = a1*25.0f/100.0f;       //(13)
    a4 = a1*12.5f/100.0f;       //(14)

    tgalfa1 = (t2-t1)/qLn(a1/a2);  //(16)
    tgalfa2 = (t3-t2)/qLn(a2/a3);  //(17)
    tgalfa3 = (t3-t1)/qLn(a1/a3);  //(18)
    tgalfa4 = (t4-t2)/qLn(a2/a4);  //(19)
    tgalfa = ( tgalfa1 + tgalfa2 + tgalfa3 + tgalfa4 ) / k; //(15)

    lgax = ( t1 - CalcData::calc() + qLn(a1) * tgalfa ) / tgalfa; //(20)

    return qPow(10, lgax);
}

CalcAgr1::CalcAgr1(QMap<double, double> map) : CalcData(map)
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

CalcAgr2::CalcAgr2(QMap<double, double> map) : CalcData(map)
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
