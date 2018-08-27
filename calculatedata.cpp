#include "calculatedata.h"
#include <QtMath>

CalcData::CalcData()
{
    jump = 0.04f;
    mix_t = 4.0f;
    plot = NULL;
}

CalcData::CalcData(QMap<double, double> map, QCustomPlot *p)
    : mdata(map), plot(p)
{
    jump = 0.04f;
    mix_t = 4.0f;
    plot = NULL;
}

double CalcData::calcKo(QMap<double, double> map)
{
    mdata = map;
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
    if(plot != NULL) {
        static QCPGraph *g = plot->addGraph();
        g->setName("AVG");
        double endpoint =  (mdata.end()-1).key();
        qDebug() << QString("endpoint %1").arg(endpoint);
        QVector<double> key = {0, endpoint};
        QVector<double> value = {avg, avg};
        g->setData(key, value);
    }
    qDebug().noquote() << QString("sum = %1, ikey = %2, avg = %3")
                          .arg(sum).arg(state.key()).arg(sum/num);
    return state.key();
}

double CalcData::calcAgr()
{
    mix_t = 0;
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

    QMap<double, double>::const_iterator max_dx;
    QMap<double, double> map_dx;
    double max = it.value(), min = it.value(), last_value = it.value(), dx = 0;
    while(it != mdata.end()) {
        if(it.value() > max)
            max = it.value();
        if(it.value() < min)
            min = it.value(); 

        if((it.value() - last_value) > dx) {
            dx = it.value() - last_value;
            max_dx = it - 1;
        }
        map_dx.insert((it-1).key(), it.value() - last_value);
        last_value = it.value();

        num ++;
        sum += it.value();
        ++it;
    }
    if(plot != NULL) {
        static QCPGraph *g  = plot->addGraph();
        g->setName("DX");
        g->setData(map_dx.keys().toVector(), map_dx.values().toVector());
    }
    double avg = sum/num;
    double over = avg*jump;

    double a = (max_dx+1).value() - max_dx.value();
    double b = (max_dx+1).key() - max_dx.key();
    double tgalfa = a/b;
    if(plot != NULL) {
        static QCPGraph *g = plot->addGraph();
        QVector<double> key = {max_dx.key(), max_dx.key() + 1, max_dx.key() + 1};
        QVector<double> value = {max_dx.value(), max_dx.value() + tgalfa, max_dx.value()};
        g->setData(key, value);
    }
    qDebug() << QString("Max DX -->%1, Acceleration -->%2, a%3, b%4 ").arg(max_dx.key()).arg(tgalfa).arg(a).arg(b);
    qDebug() << "Минимум --> " << min << "Максимум -->" << max;

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
    return tgalfa;
}

CalcData *CalcData::createCalc(Mode_ID)
{
    CalcData *p;
    double result;
    switch ( Mode_ID ) {
    case Test_ID:
        str = tr("Тест (Test 0)");
        result = 0;
        break;
    case Agr1_ID:
        str = tr("Определение параметров агрегации, измерение (Agr1 1)");
        p = new CalcAgr1();
        break;
    case 2:
        str = tr("Определение активности фактора Виллебранда, измерение (Agr2 2)");
        break;
    case 3:
        str = tr("Время свертывания, измерение (Ko1 3)");
        break;
    case 4:
        str = tr("АЧТВ, измерение (Ko2 4)");
        break;
    case 5:
        str = tr("Фибриноген, измерение (Ko3 5)");
        break;
    case 6:
        str = tr("Тромбин, измерние (Ko4 6)");
        break;
    case 7:
        str = tr("Протромбиновый комплекс, измерение (Ko5 7)");
        break;
    default:
        break;
    }
}

CalcKo1::CalcKo1()
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

CalcKo1::CalcKo1(QMap<double, double> map, QCustomPlot *p) : CalcKo1(map)
{
    plot = p;
}

double CalcKo1::calc( QMap<double, double>  map)
{
    double k = CalcData::calcKo(map);
    qDebug() << "CalcArg1::calc() " << k;
    return k;
}

CalcKo2::CalcKo2(QMap<double, double> map) : CalcData(map), t0(0)
{
    SaveFiles file;
    file.openKo2(param);
    qDebug() << "параметры CalcKo2";
    for(auto it = param.begin(); it < param.end(); it++) {
        qDebug() << *it;
    }
    QString p = param.at(1);
    t0 = p.toDouble();
    qDebug() << "АЧТВ-тест =" << t0;
}

double CalcKo2::calc()
{
    return CalcData::calcKo()/t0; //(1)
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
    c1 = c2*200.0f/100.0f;              //(3)
    c3 = c2*50.0f/100.0f;               //(4)
    c4 = c2*25.0f/100.0f;               //(5)

    tgalfa1 = std::log10(t2/t1)/std::log10(c1/c2);    //(7)
    tgalfa2 = std::log10(t3/t2)/std::log10(c2/c3);    //(8)
    tgalfa3 = std::log10(t3/t1)/std::log10(c1/c3);    //(9)
    tgalfa4 = std::log10(t4/t2)/std::log10(c2/c4);    //(10)
    tgalfa = ( tgalfa1 + tgalfa2 + tgalfa3 + tgalfa4 ) / k; //(6)

    lgcx = ( std::log10(t2/CalcData::calcKo()) + std::log10(c2) * tgalfa ) / tgalfa; //(11)

    return qPow(10, lgcx);
}

CalcKo4::CalcKo4(QMap<double, double> map) : CalcData(map), t0(0)
{
    SaveFiles file;
    file.openKo4(param);
    qDebug() << "параметры CalcKo4";
    for(auto it = param.begin(); it < param.end(); it++) {
        qDebug() << *it;
    }
    QString p = param.at(4);
    t0 = p.toDouble();
    qDebug() << "Тромбин =" << t0;
}

double CalcKo4::calc()
{
    return CalcData::calcKo()/t0;
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
    a2 = a1*50.0f/100.0f;           //(12)
    a3 = a1*25.0f/100.0f;           //(13)
    a4 = a1*12.5f/100.0f;           //(14)

    tgalfa1 = (t2-t1)/std::log10(a1/a2);   //(16)
    tgalfa2 = (t3-t2)/std::log10(a2/a3);   //(17)
    tgalfa3 = (t3-t1)/std::log10(a1/a3);   //(18)
    tgalfa4 = (t4-t2)/std::log10(a2/a4);   //(19)
    tgalfa = ( tgalfa1 + tgalfa2 + tgalfa3 + tgalfa4 ) / k;         //(15)

    lgax = ( t1 - CalcData::calcKo() + std::log10(a1) * tgalfa ) / tgalfa;   //(20)

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

CalcAgr1::CalcAgr1(QMap<double, double> map, QCustomPlot *p) : CalcAgr1(map)
{
    plot = p;
}

double CalcAgr1::calc()
{
    double k = (btp - otp) / 100;
    return CalcData::calcAgr()*k;
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
    // <-- проверка значений калибровки
    c1 = c2*200.0f/100.0f;          //(21)
    c3 = c2*50.0f/100.0f;           //(22)
    c4 = c2*25.0f/100.0f;           //(23)

    tgalfa1 = std::log10(ck2/ck1)/std::log10(c1/c2);   //(25)
    tgalfa2 = std::log10(ck3/ck2)/std::log10(c2/c3);   //(26)
    tgalfa3 = std::log10(ck3/ck1)/std::log10(c1/c3);   //(27)

    tgalfa = ( tgalfa1 + tgalfa2 + tgalfa3 ) / kt;         //(24)

    lgcx = ( std::log10(ck1/CalcData::calcAgr()) + std::log10(c1) * tgalfa ) / tgalfa;   //(28)

    double k = (btp - otp) / 100;
    return qPow(10, lgcx);
}
