#include "calculatedata.h"
#include <QtMath>

CalcData::CalcData()
{
    dx = 0.04f;
    mix_t = 4.0f;
}

CalcData::CalcData(QMap<double, double> map)
    : mdata(map)
{

}

double CalcData::calcKo(QMap<double, double> map)
{
/* старый алгоритм
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
    return map.lastKey() - state.key(); //state.key() - map.begin().key();
*/
    qDebug() << "CalcData::calcKo map.firstkey()" << map.firstKey();
    qDebug() << "CalcData::calcKo map.lastkey()" <<  map.lastKey();
    return map.lastKey() - map.firstKey();
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
    double max = it.value(), min = it.value(), last_value = it.value();
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
//    if(plot != NULL) {
//        static QCPGraph *g  = plot->addGraph();
//        g->setName("DX");
//        g->setData(map_dx.keys().toVector(), map_dx.values().toVector());
//    }
    double avg = sum/num;
    double over = avg*dx;

    double a = (max_dx+1).value() - max_dx.value();
    double b = (max_dx+1).key() - max_dx.key();
    double tgalfa = a/b;
//    if(plot != NULL) {
//        static QCPGraph *g = plot->addGraph();
//        QVector<double> key = { max_dx.key(), max_dx.key() + 1, max_dx.key() + 1 };
//        QVector<double> value = { max_dx.value(), max_dx.value() + tgalfa, max_dx.value() };
//        g->setData(key, value);
//    }
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

CalcData *CalcData::createCalc(Test *t, Calibration *c, Mode_ID  id)
{
    QString str;
    CalcData *p;
    switch (id) {
//    case Test_ID:
//        str = tr("Тест (Test 0)");
//        p = new CalcLevel();
//        break;
    case Level_ID:
        str = tr("Измерение уровня сигнала");
        p = new CalcLevel();
        break;
    case TestKo1_ID:
    case CalibKo1_ID:
        str = tr("Время свертывания");
        if( TestKo1 *test = qobject_cast<TestKo1 *>(t))
            if(CalibrationKo1 *calib = qobject_cast<CalibrationKo1 *>(c))
                p = new CalcKo1(test, calib);
        break;
    case TestKo2_ID:
    case CalibKo2_ID:
        str = tr("АЧТВ");
        if( TestKo2 *test = qobject_cast<TestKo2 *>(t))
            if(CalibrationKo2 *calib = qobject_cast<CalibrationKo2 *>(c))
                p = new CalcKo2(test, calib);
        break;
//    case TestKo2_1_ID:
//        str = tr("АЧТВ без калибровки");
//        p = new CalcKo2(WithoutCalibration());
//        break;
    case TestKo3_ID:
    case CalibKo3_ID:
        str = tr("Фибриноген");
        if( TestKo3 *test = qobject_cast<TestKo3 *>(t))
            if(CalibrationKo3 *calib = qobject_cast<CalibrationKo3 *>(c))
                p = new CalcKo3(test, calib);
        break;
    case TestKo4_ID:
    case CalibKo4_ID:
        str = tr("Тромбин");
        str = tr("Фибриноген");
        if( TestKo4 *test = qobject_cast<TestKo4 *>(t))
            if(CalibrationKo4 *calib = qobject_cast<CalibrationKo4 *>(c))
                p = new CalcKo4(test, calib);
        break;
    case TestKo5_ID:
    case CalibKo5_ID:
        str = tr("Протромбиновый комплекс");
        str = tr("Фибриноген");
        if( TestKo5 *test = qobject_cast<TestKo5 *>(t))
            if(CalibrationKo5 *calib = qobject_cast<CalibrationKo5 *>(c))
                p = new CalcKo5(test, calib);
        break;
    case TestAgr1_ID:
    case CalibAgr1_ID:
        str = tr("Определение параметров агрегации");
        str = tr("Фибриноген");
        if( TestAgr1 *test = qobject_cast<TestAgr1 *>(t))
            if(CalibrationAgr1 *calib = qobject_cast<CalibrationAgr1 *>(c))
                p = new CalcAgr1(test, calib);
        break;
    case TestAgr2_ID:
    case CalibAgr2_ID:
        str = tr("Определение активности фактора Виллебранда");
        str = tr("Фибриноген");
        if( TestAgr2 *test = qobject_cast<TestAgr2 *>(t))
            if(CalibrationAgr2 *calib = qobject_cast<CalibrationAgr2 *>(c))
                p = new CalcAgr2(test, calib);
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

CalcKo1::CalcKo1(TestKo1 *t, CalibrationKo1 *c) : CalcData(), t_ko1(t), c_ko1(c)
{
    ///иницмализация параметров
}

double CalcKo1::calc(QMap<double, double> map)
{
    //qDebug() << "CalcKo1::calc() " << k;
    return CalcData::calcKo(map);
}

QString CalcKo1::getParameters()
{
    return QString("Тест на \"%1\" не имеет параметров калибровки.").arg(info());
}

void CalcKo1::graph()
{
//    static QCPGraph *g = plot->addGraph();
//    g->setName("AVG");
//    double endpoint =  (map.end()-1).key();
//    qDebug() << QString("endpoint %1").arg(endpoint);
//    QVector<double> key = {0, endpoint};
//    QVector<double> value = {avg, avg};
//    g->setData(key, value);
//    qDebug().noquote() << QString("sum = %1, ikey = %2, avg = %3")
//                          .arg(sum).arg(state.key()).arg(sum/num);
}

QString CalcKo1::info()
{
    return QString("Время свертывания (c)");
}

CalcKo2::CalcKo2(TestKo2 *t, CalibrationKo2 *c) : CalcData(), t_ko2(t), c_ko2(c)
{
    t0 = (c_ko2->getA4tv_kp1() + c_ko2->getA4tv_kp2() + c_ko2->getA4tv_kp3() + c_ko2->getA4tv_kp4())/4;
    //QMessageBox::information(nullptr, "CalcKo2", QString("АЧТВ = %1").arg(t0));
    qDebug() << QString("АЧТВ = %1").arg(t0);
}

//CalcKo2::CalcKo2(WithoutCalibration)
//{
//    t_ko2 = new TestKo2(WithoutCalibration(), this);
//    t0 = t_ko2->getA4tv_kp();
//    //QMessageBox::information(nullptr, "CalcKo2", QString("АЧТВ = %1").arg(t0));
//    qDebug() << QString("АЧТВ = %1").arg(t0);
//}

double CalcKo2::calc(QMap<double, double> map)
{
    if(!t0) QMessageBox::information(0, "CalcKo2", "Деление на ноль");
    return CalcData::calcKo(map)/t0; // ОТН АЧТВ(1)
}

QString CalcKo2::info()
{
    return QString("АЧТВ (c)");
}

QString CalcKo2::getParameters()
{
    return QString("АЧТВ контрольной плазмы: t0 = %1 (c)").arg(t0);
}

//void CalcKo2::getCalibrationDeta(double &c1, double &c2, double &c3, double &c4)
//{
//}

CalcKo3::CalcKo3(TestKo3 *t, CalibrationKo3 *c) : CalcData(), t_ko3(t), c_ko3(c)
{
    t1 = c_ko3->getTime_200_plazma();
    t2 = c_ko3->getTime_k_plazma();
    t3 = c_ko3->getTime_50_plazma();
    t4 = c_ko3->getTime_25_plazma();
    c2 = c_ko3->getFibrinogen_k_plazma();
    c1 = c2*200.0f/100.0f;              //(3)
    c_ko3->setFibrinogen_200_plazma(c1);
    c3 = c2*50.0f/100.0f;               //(4)
    c_ko3->setFibrinogen_50_plazma(c3);
    c4 = c2*25.0f/100.0f;               //(5)
    c_ko3->setFibrinogen_25_plazma(c4);
    qDebug() << "Фибриноген по Клауссу =" << c2;
    qDebug() << QString("Параметры калибровки Фириногена") << c2 << t1 << t2 << t3 << t4;
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
    return QString("Концентраци Фибриногена (г/л)");
}

QString CalcKo3::getParameters()
{
    return QString("Cодержание фибриногена по Клауссу (100%) = %1\n"
                   "Время свертывания для каждого разведения:\n"
                   "t1 (200%) = %2\nt2 (100%) = %3\nt3 (50%) = %4\nt4 (25%) = %5")
            .arg(c2).arg(t1).arg(t2).arg(t3).arg(t4);
}

CalcKo4::CalcKo4(TestKo4 *t, CalibrationKo4 *c) : CalcData(), t_ko4(t), c_ko4(c)
{
    t0 = (c_ko4->getTv1() + c_ko4->getTv2() + c_ko4->getTv3() + c_ko4->getTv4())/4;
    qDebug() << "Тромбин контрольной плазмы =" << t0;
}

double CalcKo4::calc(QMap<double, double> map)
{

    return CalcData::calcKo(map)/t0;    //ОТН Тромбин(2)
}

QString CalcKo4::info()
{
    return QString("Тромбин (c)");
}

QString CalcKo4::getParameters()
{
    return QString("Тромбмн контрольной плазмы t0 = %1").arg(t0);
}

CalcKo5::CalcKo5(TestKo5 *t, CalibrationKo5 *c) : CalcData(), t_ko5(t), c_ko5(c)
{
    a100 = c_ko5->getProtrombine_k_Kvik();
    t100 = c_ko5->getTime_k_Kvik();
    t50 = c_ko5->getTime_50_Kvik();
    a50 = a100*50.0f/100.0f;           //(12)
    t25 = c_ko5->getTime_25_Kvik();
    a25 = a100*25.0f/100.0f;           //(13)
    t12 = c_ko5->getTime_12_Kvik();
    a12 = a100*12.5f/100.0f;           //(14)
    qDebug() << "ТВ контрольной плазмы =" << t100;
}

double CalcKo5::calc(QMap<double, double> map)
{
    // <-- проверка значений калибровки
    double tx = CalcData::calcKo(map);
    tgalfa1 = (t50-t100)/std::log10(a100/a50);                  //(16)
    tgalfa2 = (t25-t50)/std::log10(a50/a25);                    //(17)
    tgalfa3 = (t25-t100)/std::log10(a100/a25);                  //(18)
    tgalfa4 = (t12-t50)/std::log10(a50/a12);                    //(19)
    tgalfa = (tgalfa1 + tgalfa2 + tgalfa3 + tgalfa4) / k;     //(15)


    lgax = (t100 - tx + std::log10(a100) * tgalfa) / tgalfa;   //(20)
    ax = qPow(10, lgax);
    pox = ( tx/t100 ) * po1;
    pix = ( t100/tx ) * pi1;
    return ax;
}

QString CalcKo5::info()
{
    return QString("Протромбиновый комплекс");
}

QString CalcKo5::getParameters()
{
    return QString("ТВ контрольной плазмы для каждого разведения:\nt1 (100%) = %1\nt2 (50%) = %2\nt3 (25%) = %3\nt4 (12.5%) = %4").arg(t100).arg(t50).arg(t25).arg(t12);
}

CalcAgr1::CalcAgr1(TestAgr1 *t, CalibrationAgr1 *c) : CalcData(), t_agr1(t), c_agr1(c)
{
//    SaveFiles file;
//    QStringList bt, ot;
//    file.openAgr1(param);

//    qDebug() << "параметры CalcAgr1";

//    for(auto it = param.begin(); it != param.end(); it++) {
//        qDebug() << *it;
//    }

//    file.openBTP0(bt);
//    for(auto it = bt.begin(); it != bt.end(); it++) {
//        QString s = *it;
//        btp += s.toDouble();
//    }
//    btp /= bt.count();

//    file.openBTP100(ot);
//    for(auto it = ot.begin(); it != ot.end(); it++) {
//        QString s = *it;
//        otp += s.toDouble();
//    }
//    otp /= ot.count();

    btp = ( c_agr1->getBTP1() + c_agr1->getBTP2() + c_agr1->getBTP3() + c_agr1->getBTP4() ) / 4;
    otp = ( c_agr1->getOTP1() + c_agr1->getOTP2() + c_agr1->getOTP3() + c_agr1->getOTP4() ) / 4;
}

//CalcAgr1::CalcAgr1(QCustomPlot *p) : CalcAgr1()
//{
//    plot = p;
//}

double CalcAgr1::calc(QMap<double, double> map)
{
    double k = (btp - otp) / 100;
    return CalcData::calcAgr(map)*k;
}

QString CalcAgr1::info()
{
    return QString("Степень агрегации");
}

QString CalcAgr1::getParameters()
{
    return QString("Степень агрегации");
}

CalcAgr2::CalcAgr2(TestAgr2 *t, CalibrationAgr2 *c) : CalcData(), t_agr2(t), c_agr2(c)
{
//    SaveFiles file;
//    file.openAgr2(param);
//    qDebug() << "параметры CalcAgr2";
//    for(auto it = param.begin(); it < param.end(); it++) {
//        qDebug() << *it;
//    }
    c1 = c_agr2->getC1();
    ck1 = c_agr2->getCk1();
    c2 = c_agr2->getC2();
    ck2 = c_agr2->getCk2();
    c3 = c_agr2->getC3();
    ck3 = c_agr2->getCk3();
    c4 = c_agr2->getC4();
    ck4 = c_agr2->getCk4();

    btp = ( c_agr2->getBTP1() + c_agr2->getBTP2() + c_agr2->getBTP3() + c_agr2->getBTP4() ) / 4;
    otp = ( c_agr2->getOTP1() + c_agr2->getOTP2() + c_agr2->getOTP3() + c_agr2->getOTP4() ) / 4;
}

double CalcAgr2::calc(QMap<double, double> map)
{
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

QString CalcAgr2::getParameters()
{
    return QString("");
}

CalcLevel::CalcLevel() : CalcData()
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

QString CalcLevel::getParameters()
{
    return QString("CalcLevel не имеет параметров калибровки");
}
