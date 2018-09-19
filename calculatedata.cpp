#include "calculatedata.h"
#include <QtMath>

CalcData::CalcData()
{
    dx = 0.04f;
    mix_t = 4.0f;
    plot = NULL;
}

CalcData::CalcData(QMap<double, double> map, QCustomPlot *p)
    : mdata(map), plot(p)
{
}

double CalcData::calcKo(QMap<double, double> map)
{
    if(map.isEmpty()) { qDebug() << "error from CalcData::caalcKo(): the map is empty!"; return 0; }
    QMap<double, double>::const_iterator it = map.begin();
    QMap<double, double>::const_iterator state = map.end();
    double sum = 0;
    int num = 0;

    while(it != map.end()) {
        if((it.key() - map.begin().key()) >= mix_t) {
            state = it;
            //qDebug().noquote() << QString("key = %1, value = %2").arg(it.key()).arg(it.value());
            break;
        }
        ++it;
    }

    while(it != map.end()) {
        num ++;
        sum += it.value();
        ++it;
    }
    double avg = sum/num;
    double over = avg*dx;

    while(state != map.end()) {
        if( (avg-state.value()) >= over ) {
            qDebug() << "state != map.end()";
            break;
        }
        //qDebug() << QString("%1").arg(avg - state.value());
        ++state;
    }
    if(state == map.end()) { qDebug() << "CalcData::CalcKo() is not found over voltage"; return 0; }
    if(plot != NULL) {
        static QCPGraph *g = plot->addGraph();
        g->setName("AVG");
        double endpoint =  (map.end()-1).key();
        qDebug() << QString("endpoint %1").arg(endpoint);
        QVector<double> key = {0, endpoint};
        QVector<double> value = {avg, avg};
        g->setData(key, value);
    }
    qDebug().noquote() << QString("sum = %1, ikey = %2, avg = %3")
                          .arg(sum).arg(state.key()).arg(sum/num);
    return map.lastKey() - state.key(); //state.key() - map.begin().key();
}

double CalcData::calcAgr(QMap<double, double> map)
{
    if(map.isEmpty()) { qDebug() << "error from CalcData::caalcAgr(): the map is empty!"; return 0; }
    mix_t = 0;
    QMap<double, double>::const_iterator it = map.begin();
    QMap<double, double>::const_iterator state = map.end();
    double sum = 0;
    int num = 0;

    while(it != map.end()) {
        if((it.key() - map.begin().key()) > mix_t) {
            state = it;
            //qDebug().noquote() << QString("key = %1, value = %2").arg(it.key()).arg(it.value());
            break;
        }
        ++it;
    }

    QMap<double, double>::const_iterator max_dx;
    QMap<double, double> map_dx;
    double max = it.value(), min = it.value(), last_value = it.value(), dx = 0;
    while(it != map.end()) {
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
    double over = avg*dx;

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

    while(state != map.end()) {
        if( avg-state.value() >= over ) {
            qDebug() << "state != map.end()";
            break;
        }
        //qDebug() << QString("%1").arg(avg - state.value());
        ++state;
    }
    qDebug().noquote() << QString("sum = %1, ikey = %2, avg = %3")
                          .arg(sum).arg(state.key()).arg(sum/num);
    return tgalfa;
}

CalcData *CalcData::createCalc(Mode_ID  id)
{
    QString str;
    CalcData *p;
    switch (id) {
    case Test_ID:
        str = tr("Тест (Test 0)");
        p = new CalcLevel();
        break;
    case Agr1_ID:
        str = tr("Определение параметров агрегации, измерение (Agr1 1)");
        p = new CalcAgr1();
        break;
    case Agr2_ID:
        str = tr("Определение активности фактора Виллебранда, измерение (Agr2 2)");
        p = new CalcAgr2();
        break;
    case Ko1_ID:
        str = tr("Время свертывания, измерение (Ko1 3)");
        p = new CalcKo1();
        break;
    case Ko2_ID:
        str = tr("АЧТВ, измерение (Ko2 4)");
        p = new CalcKo2();
        break;
    case Ko3_ID:
        str = tr("Фибриноген, измерение (Ko3 5)");
        p = new CalcKo3();
        break;
    case Ko4_ID:
        str = tr("Тромбин, измерние (Ko4 6)");
        p = new CalcKo4();
        break;
    case Ko5_ID:
        str = tr("Протромбиновый комплекс, измерение (Ko5 7)");
        p = new CalcKo5();
        break;
    default: p = NULL;
        break;
    }
    return p;
}

void CalcData::setMix_t(double sec)
{
    mix_t = sec;
}

double CalcData::getMix_t()
{
    return mix_t;
}

void CalcData::setDx(double dx)
{
    this->dx = dx;
}

double CalcData::getDx()
{
    return dx;
}

CalcKo1::CalcKo1()
{
    SaveFiles file;
    file.openKo1(param);
    qDebug() << "параметры CalcKo1";
    for(auto it = param.begin(); it < param.end(); it++) {
        qDebug() << *it;
    }
}

CalcKo1::CalcKo1(QCustomPlot *p)
{
    CalcKo1();
    plot = p;
}

double CalcKo1::calc(QMap<double, double> map)
{
    double k = CalcData::calcKo(map);
    qDebug() << "CalcKo1::calc() " << k;
    return k;
}

QString CalcKo1::info()
{
    return QString("Время свертывания");
}

CalcKo2::CalcKo2()
{
    SaveFiles file;
    file.openKo2(param);
    qDebug() << "параметры CalcKo2 " << param.count();
    QString d1, d2, d3, d4;
    auto it = param.end();
    d1 = *(it-4);
    d2 = *(it-3);
    d3 = *(it-2);
    d4 = *(it-1);

    qDebug() << d1 << d2 << d3 << d4;
//    auto it = param.end() - 4;
//    for(; it < param.end(); it++) {
//        qDebug() << *it;
//    }
    t0 = (d1.toDouble() + d2.toDouble() + d3.toDouble() + d4.toDouble())/4;
    qDebug() << "АЧТВ контрольной плазмы =" << t0;
}

double CalcKo2::calc(QMap<double, double> map)
{
    return CalcData::calcKo(map)/t0; // ОТН АЧТВ(1)
}

QString CalcKo2::info()
{
    return QString("АЧТВ");
}

//void CalcKo2::getCalibrationDeta(double &c1, double &c2, double &c3, double &c4)
//{
//}

CalcKo3::CalcKo3()
{
    SaveFiles file;
    file.openKo3(param);
    qDebug() << "параметры CalcKo3" << param.count();
    QString d0, d1, d2, d3, d4;
    auto it = param.end();
    d0 = *(it-5);
    d1 = *(it-4);
    d2 = *(it-3);
    d3 = *(it-2);
    d4 = *(it-1);
    c2 = d0.toDouble();
    t1 = d1.toDouble();
    t2 = d2.toDouble();
    t3 = d3.toDouble();
    t4 = d4.toDouble();
    qDebug() << c2 << t1 << t2 << t3 << t4;

    c1 = c2*200.0f/100.0f;              //(3)
    c3 = c2*50.0f/100.0f;               //(4)
    c4 = c2*25.0f/100.0f;               //(5)

//    for(auto it = param.begin(); it < param.end(); it++) {
//        qDebug() << *it;
//    }
//    QString p = param.last();
//    c2 = p.toDouble();
//    qDebug() << "по Клауссу =" << c2;
}

double CalcKo3::calc(QMap<double, double> map)
{
    // <-- проверка значений калибровки
    if( t2/t1 <1 || t3/t2 <1 || t4/t3 <1) {
        qDebug() << "Нет соответствия критерию возрастания";
        //QMessageBox::warning(nullptr, "Фибриноген", "Нет соответствия критерию возрастания");
    }
    tgalfa1 = std::log10(t2/t1)/std::log10(c1/c2);          //(7)
    tgalfa2 = std::log10(t3/t2)/std::log10(c2/c3);          //(8)
    tgalfa3 = std::log10(t3/t1)/std::log10(c1/c3);          //(9)
    tgalfa4 = std::log10(t4/t2)/std::log10(c2/c4);          //(10)
    tgalfa = ( tgalfa1 + tgalfa2 + tgalfa3 + tgalfa4 ) / k; //(6)

    lgcx = ( std::log10(t2/CalcData::calcKo(map)) + std::log10(c2) * tgalfa ) / tgalfa; // (11)

    return qPow(10, lgcx);
}

QString CalcKo3::info()
{
    return QString("Фибриноген");
}

CalcKo4::CalcKo4()
{
    SaveFiles file;
    file.openKo4(param);
    qDebug() << "параметры CalcKo4" << param.count();

    QString d1, d2, d3, d4;
    auto it = param.end();
    d1 = *(it-4);
    d2 = *(it-3);
    d3 = *(it-2);
    d4 = *(it-1);
    qDebug() << d1 << d2 << d3 << d4;
//    auto it = param.end() - 4;
//    for(; it < param.end(); it++) {
//        qDebug() << *it;
//    }
    t0 = (d1.toDouble() + d2.toDouble() + d3.toDouble() + d4.toDouble())/4;
    qDebug() << "Тромбин контрольной плазмы =" << t0;
}

double CalcKo4::calc(QMap<double, double> map)
{
    return CalcData::calcKo(map)/t0;    //ОТН Тромбин(2)
}

QString CalcKo4::info()
{
    return QString("Тромбин");
}

CalcKo5::CalcKo5()
{
    SaveFiles file;
    file.openKo5(param);
    qDebug() << "параметры CalcKo5";
    for(auto it = param.begin(); it < param.end(); it++) {
        qDebug() << *it;
    }
    QString p = param.last();
    a1 = p.toDouble();
    qDebug() << "ТВ контрольной плазмы =" << a1;
}

double CalcKo5::calc(QMap<double, double> map)
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

    lgax = ( t1 - CalcData::calcKo(map) + std::log10(a1) * tgalfa ) / tgalfa;   //(20)

    return qPow(10, lgax);
}

QString CalcKo5::info()
{
    return QString("Протромбиновый комплекс");
}

CalcAgr1::CalcAgr1()
{
    SaveFiles file;
    file.openAgr1(param);
    qDebug() << "параметры CalcAgr1";
    for(auto it = param.begin(); it < param.end(); it++) {
        qDebug() << *it;
    }
}

CalcAgr1::CalcAgr1(QCustomPlot *p)
{
    plot = p;
}

double CalcAgr1::calc(QMap<double, double> map)
{
    double k = (btp - otp) / 100;
    return CalcData::calcAgr(map)*k;
}

QString CalcAgr1::info()
{
    return QString("Степень агрегации");
}

CalcAgr2::CalcAgr2()
{
    SaveFiles file;
    file.openAgr2(param);
    qDebug() << "параметры CalcAgr2";
    for(auto it = param.begin(); it < param.end(); it++) {
        qDebug() << *it;
    }
}

double CalcAgr2::calc(QMap<double, double> map)
{
    // <-- проверка значений калибровки
    c1 = c2*200.0f/100.0f;          //(21)
    c3 = c2*50.0f/100.0f;           //(22)
    c4 = c2*25.0f/100.0f;           //(23)

    tgalfa1 = std::log10(ck2/ck1)/std::log10(c1/c2);   //(25)
    tgalfa2 = std::log10(ck3/ck2)/std::log10(c2/c3);   //(26)
    tgalfa3 = std::log10(ck3/ck1)/std::log10(c1/c3);   //(27)

    tgalfa = ( tgalfa1 + tgalfa2 + tgalfa3 ) / kt;         //(24)

    lgcx = ( std::log10(ck1/CalcData::calcAgr(map)) + std::log10(c1) * tgalfa ) / tgalfa;   //(28)

    double k = (btp - otp) / 100;
    return qPow(10, lgcx)/k;
}

QString CalcAgr2::info()
{
    return QString("фактор Виллебранда");
}

CalcLevel::CalcLevel()
{

}

QString CalcLevel::info()
{
    return QString("среднее Значение");
}

double CalcLevel::calc(QMap<double, double> map)
{
    if(map.isEmpty()) { qDebug() << "error from CalcData::caalcKo(): the map is empty!"; return 0; }
    QMap<double, double>::const_iterator it = map.begin();
    QMap<double, double>::const_iterator state = map.end();
    double sum = 0;
    int num = 0;

    while(it != map.end()) {
        if((it.key() - map.begin().key()) >= mix_t) {
            state = it;
            //qDebug().noquote() << QString("key = %1, value = %2").arg(it.key()).arg(it.value());
            break;
        }
        ++it;
    }

    while(it != map.end()) {
        num ++;
        sum += it.value();
        ++it;
    }
    return sum/num;
}
