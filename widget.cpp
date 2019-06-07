﻿#include "widget.h"
#include "ui_widget.h"

#include <QScrollBar>
#include <QMessageBox>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QtConcurrent>
#include <functional>
#include "useE154.h"

Widget::Widget(StartMeasurement *sm, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    data1(false), data2(false), data3(false), data4(false)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    installEventFilter(this);
    setWindowTitle("Программа сбора данных с АЦП(E-154) по 4 каналам");
    fixed_point.push_back(0);
    fixed_point.push_back(0);
    fixed_point.push_back(0);
    fixed_point.push_back(0);
    connect(this, SIGNAL(value_come(QVariantList)), this, SLOT(realtimeDataSlot(QVariantList)));

    START_DX1 = sm->getTest()->getStart_dx(0);
    START_DX2 = sm->getTest()->getStart_dx(1);
    START_DX3 = sm->getTest()->getStart_dx(2);
    START_DX4 = sm->getTest()->getStart_dx(3);

    STOP_DX1 = sm->getTest()->getStop_dx(0);
    STOP_DX2 = sm->getTest()->getStop_dx(1);
    STOP_DX3 = sm->getTest()->getStop_dx(2);
    STOP_DX4 = sm->getTest()->getStop_dx(3);

    MIN = sm->getTest()->getMin();
    MAX = sm->getTest()->getMax();
    MIX_TIME_MS = 4.0;

    pBar1 = new ProgressTimerBar(this);
    pBar2 = new ProgressTimerBar(this);
    pBar3 = new ProgressTimerBar(this);
    pBar4 = new ProgressTimerBar(this);
    startWin = sm;
    state = StateBuilder::getState(sm->getModeID(), this);
    tool = new Options(this);

    //настройка таймера для часов
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::updateTime);
    timer->start(500);

    //считываем состояние температурной готовности
    ILE154 *pModule = OnlyOneE154::Instance().getModule();
    WORD ttl_in;
    pModule->TTL_IN(&ttl_in);
    termoSensor = ttl_in & (1<<0);
    //if(termoSensor) setUserMessage("Дождитесь нагрева термостата");

    setUserMessage(QString("Начало работы программы    Дата %1")
                   .arg(QDateTime::currentDateTime().toString("dd.MM.yyyy")));

    setupWidget();
}

void Widget::setupWidget()
{
    emit onmixch1(false);
    emit onmixch2(false);
    emit onmixch3(false);
    emit onmixch4(false);
    emit onlaser(false);

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);

    timeTicker->setTimeFormat("%m:%s");

    customPlot1 = ui->frame_1;
    ui->groupBox_f1->layout()->addWidget(pBar1);
    customPlot1->addGraph();
    customPlot1->graph(0)->setPen(QPen(QColor(10, 110, 40)));
    customPlot1->xAxis->setTicker(timeTicker);
    customPlot1->axisRect()->setupFullAxesBox();
    customPlot1->xAxis->setLabel("Время, с");
    customPlot1->yAxis2->setLabel("Вольт");
    customPlot1->yAxis->setRange(MIN, MAX);

    if (startWin->isChannel(Channel1_ID)) {
        ui->groupBox_f1->setTitle(QString("Канал 1, Пр.№%1").arg(startWin->getNum(1)));
        ui->groupBox_f1->show();
    } else ui->groupBox_f1->hide();

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(customPlot1->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot1->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot1->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot1->yAxis2, SLOT(setRange(QCPRange)));

    customPlot2 = ui->frame_2;
    ui->groupBox_f2->layout()->addWidget(pBar2);
    customPlot2->addGraph();
    customPlot2->graph(0)->setPen(QPen(QColor(255, 110, 40)));
    customPlot2->xAxis->setTicker(timeTicker);
    customPlot2->axisRect()->setupFullAxesBox();
    customPlot2->xAxis->setLabel("Время, с");
    customPlot2->yAxis2->setLabel("Вольт");
    customPlot2->yAxis->setRange(MIN, MAX);

    if (startWin->isChannel(Channel2_ID)) {
        ui->groupBox_f2->setTitle(QString("Канал 2, Пр.№%1").arg(startWin->getNum(2)));
        ui->groupBox_f2->show();
    } else ui->groupBox_f2->hide();

    connect(customPlot2->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot2->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot2->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot2->yAxis2, SLOT(setRange(QCPRange)));

    customPlot3 = ui->frame_3;
    ui->groupBox_f3->layout()->addWidget(pBar3);
    customPlot3->addGraph();
    customPlot3->graph(0)->setPen(QPen(QColor(255, 110, 200)));
    customPlot3->xAxis->setTicker(timeTicker);
    customPlot3->axisRect()->setupFullAxesBox();
    customPlot3->xAxis->setLabel("Время, с");
    customPlot3->yAxis2->setLabel("Вольт");
    customPlot3->yAxis->setRange(MIN, MAX);

    if (startWin->isChannel(Channel3_ID)) {
        ui->groupBox_f3->setTitle(QString("Канал 3, Пр.№%1").arg(startWin->getNum(3)));
        ui->groupBox_f3->show();
    } else ui->groupBox_f3->hide();

    connect(customPlot3->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot3->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot3->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot3->yAxis2, SLOT(setRange(QCPRange)));

    customPlot4 = ui->frame_4;
    ui->groupBox_f4->layout()->addWidget(pBar4);
    customPlot4->addGraph();
    customPlot4->graph(0)->setPen(QPen(QColor(255, 200, 40)));
    customPlot4->xAxis->setTicker(timeTicker);
    customPlot4->axisRect()->setupFullAxesBox();
    customPlot4->xAxis->setLabel("Время, с");
    customPlot4->yAxis2->setLabel("Вольт");
    customPlot4->yAxis->setRange(MIN, MAX);

    if (startWin->isChannel(Channel4_ID)) {
        ui->groupBox_f4->setTitle(QString("Канал 4, Пр.№%1").arg(startWin->getNum(4)));
        ui->groupBox_f4->show();
    } else ui->groupBox_f4->hide();

    connect(customPlot4->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot4->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot4->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot4->yAxis2, SLOT(setRange(QCPRange)));
}

Widget::~Widget()
{
    //emit stop();
    delete state;
    delete startWin;
    delete ui;
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::Close) {
        qDebug() << "Close Event is emited in the Widget!";
        if(!parentWidget()) qDebug() <<"parent Widget do not set in constroctor";
            parentWidget()->show();
        setUserMessage("Конец работы программы");
        emit stop();
        return true; //QWidget::eventFilter(watched, event);
    }
    if(event->type() == QEvent::KeyPress) {
        qDebug() << "Event kayPress";
        QKeyEvent *kayEvent = static_cast<QKeyEvent *>(event);
        if(kayEvent->key() == Qt::Key_Enter) {
            tool->exec();
        }
        return QWidget::eventFilter(watched, event);
    }
    return QWidget::eventFilter(watched, event);
}

void Widget::realtimeDataSlot(QVariantList a) {
    //qDebug() << "ThreadID: " << QThread::currentThreadId() << "a0 = " << a[0];
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of widget, in seconds
    static double lastPointKey = 0;
    static double lastPointV1 = a[0].toDouble();
    static double lastPointV2 = a[1].toDouble();
    static double lastPointV3 = a[2].toDouble();
    static double lastPointV4 = a[3].toDouble();
    double dx1 = std::abs(fixed_point[0].toDouble() - a[0].toDouble()); //std::abs(a[0].toDouble() - lastPointV1);
    double dx2 = std::abs(fixed_point[1].toDouble() - a[1].toDouble()); //std::abs(a[1].toDouble() - lastPointV2);
    double dx3 = std::abs(fixed_point[2].toDouble() - a[2].toDouble()); //std::abs(a[2].toDouble() - lastPointV3);
    double dx4 = std::abs(fixed_point[3].toDouble() - a[3].toDouble()); //std::abs(a[3].toDouble() - lastPointV4);

    //определение порога и запуск канала 1
    //std::abs(map_y1.last() - stop_dy1) >= std::abs(stop_dy1*STOP_DX1
    if( dx1 >= std::abs(fixed_point[0].toDouble() * START_DX1) || pulse1 ) {
        pulse1 = false;
        emit hasPulse1();
    }
    lastPointV1 = a[0].toDouble();

    //определение порога и запуск канала 2
    if( dx2 >= std::abs(fixed_point[1].toDouble() * START_DX2) || pulse2 ) {
        pulse2 = false;
        emit hasPulse2();
    }
    lastPointV2 = a[1].toDouble();

    //определение порога и запуск канала 3
    if( dx3 >= std::abs(fixed_point[2].toDouble() * START_DX3) || pulse3 ) {
        pulse3 = false;
        emit hasPulse3();
    }
    lastPointV3 = a[2].toDouble();

    //определение порога и запуск канала 4
    if( dx4 >= std::abs(fixed_point[3].toDouble() * START_DX4) || pulse4 ) {
        pulse4 = false;
        emit hasPulse4();
    }
    lastPointV4 = a[3].toDouble();

    //добавление точек на графики
    customPlot1->graph(0)->addData(key, a[0].toDouble());
    customPlot2->graph(0)->addData(key, a[1].toDouble());
    customPlot3->graph(0)->addData(key, a[2].toDouble());
    customPlot4->graph(0)->addData(key, a[3].toDouble());

    // make key axis range scroll with the data (at a constant range size of 8):
    customPlot1->xAxis->setRange(key, 10, Qt::AlignRight);
    customPlot1->replot();

    customPlot2->xAxis->setRange(key, 10, Qt::AlignRight);
    customPlot2->replot();

    customPlot3->xAxis->setRange(key, 10, Qt::AlignRight);
    customPlot3->replot();

    customPlot4->xAxis->setRange(key, 10, Qt::AlignRight);
    customPlot4->replot();

    static double stop_dy1 = 0; //установившееся значение (после перемешивания) в канале 1
    if( data1 ) {
        map_y1.insert(key, a[0].toDouble());
        if( key <= (map_y1.firstKey() + MIX_TIME_MS) ) {
                stop_dy1 = map_y1.last();
                //qDebug() << "STOP_DX1 = " << stop_dy1;
        }
        else {
            if(std::abs(map_y1.last() - stop_dy1) >= std::abs(stop_dy1*STOP_DX1))
            {
                //qDebug() << "Signal to stop data1 " << std::abs(map_y1.last() - stop_dy1) << ">=" << std::abs(stop_dy1*STOP_DX);
                setUserMessage("Канал 1: Образование сгустка");
                //data1 = false; //stopData(Channel1_ID);
                pBar1->stopProgress();
                qDebug() << "pBAr1 time = " << pBar1->getTime_ms();
                //emit done1();
            }
        }
    }
    else {
        stop_dy1 = 0;
    }

    static double stop_dy2 = 0; //установившееся значение (после перемешивания) в канале 2
    if( data2 ) {
        map_y2.insert(key, a[1].toDouble());
        if( key <= (map_y2.firstKey() + MIX_TIME_MS) ) {
                stop_dy2 = map_y2.last();
                //qDebug() << "STOP_DX2 = " << stop_dy2;
        }
        else {
            if(std::abs(map_y2.last() - stop_dy2) >= std::abs(stop_dy2*STOP_DX2))
            {
                //qDebug() << "Signal to stop data2 " << std::abs(map_y2.last() - stop_dy2) << ">=" << std::abs(stop_dy2*STOP_DX);
                setUserMessage("Канал 2: Образование сгустка");
                //data2 = false; //stopData(Channel2_ID);
                pBar2->stopProgress();
                qDebug() << "pBAr2 time = " << pBar2->getTime_ms();
                //emit done2();
            }
        }
    }
    else {
        stop_dy2 = 0;
    }

    static double stop_dy3 = 0; //установившееся значение (после перемешивания) в канале 3
    if( data3 ) {
        map_y3.insert(key, a[2].toDouble());
        if( key <= (map_y3.firstKey() + MIX_TIME_MS) ) {
                stop_dy3 = map_y3.last();
                //qDebug() << "STOP_DX3 = " << stop_dy3;
        }
        else {
            if(std::abs(map_y3.last() - stop_dy3) >= std::abs(stop_dy3*STOP_DX3))
            {
                //qDebug() << "Signal to stop data3 " << std::abs(map_y3.last() - stop_dy3) << ">=" << std::abs(stop_dy3*STOP_DX);
                setUserMessage("Канал 3: Образование сгустка");
                //data3 = false; //stopData(Channel3_ID);
                pBar3->stopProgress();
                qDebug() << "pBAr3 time = " << pBar3->getTime_ms();
                //emit done3();
            }
        }
    }
    else {
        stop_dy3 = 0;
    }

    static double stop_dy4 = 0; //установившееся значение (после перемешивания) в канале 4
    if( data4 ) {
        map_y4.insert(key, a[3].toDouble());
        if( key <= (map_y4.firstKey() + MIX_TIME_MS) ) {
                stop_dy4 = map_y4.last();
                //qDebug() << "STOP_DX4 = " << stop_dy4;
        }
        else {
            if(std::abs(map_y4.last() - stop_dy4) >= std::abs(stop_dy4*STOP_DX4))
            {
                //qDebug() << "Signal to stop data4 " << std::abs(map_y4.last() - stop_dy4) << ">=" << std::abs(stop_dy4*STOP_DX);
                setUserMessage("Канал 4: Образование сгустка");
                //data4 =false; //stopData(Channel4_ID);
                pBar4->stopProgress();
                qDebug() << "pBAr4 time = " << pBar4->getTime_ms();
                //emit done4();
            }
        }
    }
    else {
        stop_dy4 = 0;
    }
    // calculate frames per second:
    lastPointKey = key;
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) {// average fps over 2 seconds
        ui->label_fps->setText(QString("%1 FPS, Total Data points: %2")
                        .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
                        .arg(customPlot1->graph(0)->data()->size()
                             +customPlot2->graph(0)->data()->size()
                             +customPlot3->graph(0)->data()->size()
                             +customPlot4->graph(0)->data()->size()));
        lastFpsKey = key;
        frameCount = 0;
    }
}

void Widget::fix_point(QVariantList p)
{
    fixed_point = p;
    qDebug() << "fix the point 1" << p[0].toDouble();
    qDebug() << "fix the point 2" << p[1].toDouble();
    qDebug() << "fix the point 3" << p[2].toDouble();
    qDebug() << "fix the point 4" << p[3].toDouble();
}

void Widget::onMotor(Channel_ID c, bool arg)
{
    switch(c) {
    case Channel1_ID:
        if(arg) setUserMessage("Канал 1: Включение двигателя магнитной мешалки");
        else setUserMessage("Канал 1: Выключение двигателя магнитной мешалки");
        emit onmixch1(arg);
        break;
    case Channel2_ID:
        if(arg) setUserMessage("Канал 2: Включение двигателя магнитной мешалки");
        else setUserMessage("Канал 2: Выключение двигателя магнитной мешалки");
        emit onmixch2(arg);
        break;
    case Channel3_ID:
        if(arg) setUserMessage("Канал 3: Включение двигателя магнитной мешалки");
        else setUserMessage("Канал 3: Выключение двигателя магнитной мешалки");
        emit onmixch3(arg);
        break;
    case Channel4_ID:
        if(arg) setUserMessage("Канал 4: Включение двигателя магнитной мешалки");
        else setUserMessage("Канал 4: Выключение двигателя магнитной мешалки");
        emit onmixch4(arg);
        break;
    case ChannelPP_ID:
        if(arg) setUserMessage("Канал РР: Включение двигателя магнитной мешалки");
        else setUserMessage("Канал РР: Выключение двигателя магнитной мешалки");
        emit onmixpp(arg);
        break;
//    case ChannelAll_ID:
//        if(arg) setUserMessage("Канал 1,2,3,4,PP: Включение двигателя магнитной мешалки");
//        else setUserMessage("Канал 1,2,3,4,PP: Выключение двигателя магнитной мешалки");
//        emit onmixch1(arg);
//        emit onmixch2(arg);
//        emit onmixch3(arg);
//        emit onmixch4(arg);
//        emit onmixpp(arg);
//        break;
    }
}

void Widget::test()
{
    //Test
    QPointer<QMessageBox> test_dialog = new QMessageBox(this);
    //test_dialog->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    QPushButton ok;
    QPushButton cansel;
    ok.setText("Норма");
    cansel.setText("Брак");
    test_dialog->addButton(&ok, QMessageBox::AcceptRole);
    test_dialog->addButton(&cansel, QMessageBox::RejectRole);
    test_dialog->setIcon(QMessageBox::Information);

    emit onmixch1(false);
    emit onmixch2(false);
    emit onmixch3(false);
    emit onmixch4(false);
    emit onlaser(false);
    setUserMessage("<br>Проверка работопособности</br>");
    //Проверка Перемешивания в канале 1
    emit onmixch1(true);
    setUserMessage(QString("Контроль включения перемешивания в канале 1"));
    test_dialog->setWindowTitle("Канал 1 - проверка");
    test_dialog->setText("Проконтролируте включение перемешивания в канале 1");
    test_dialog->exec();
    if(test_dialog->result() == 0) {
       emit onmixch1(false);
       setUserMessage("Перемешивание в канале 1 - <span style='color:blue'>НОРМА</span>");
    }
    else {
       setUserMessage(QString("Перемешивание в канале 1 - <span style='color:red'>БРАК</span>"));
       //return;
    }
    //Проверка Перемешивания в канале 2
    emit onmixch2(true);
    setUserMessage(QString("Контроль включения перемешивания в канале 2"));
    test_dialog->setWindowTitle("Канал 2 - проверка");
    test_dialog->setText("Проконтролируте включение перемешивания в канале 2");
    test_dialog->exec();
    if(test_dialog->result() == 0) {
      emit onmixch2(false);
      setUserMessage("Перемешивание в канале 2 - <span style='color:blue'>НОРМА</span>");
    }
    else {
        setUserMessage(QString("Перемешивание в канале 2 - <span style='color:red'>БРАК</span>"));
        //return;
    }
    //Проверка Перемешивания в канале 3
    emit onmixch3(true);
    setUserMessage(QString("Контроль включения перемешивания в канале 3"));
    test_dialog->setWindowTitle("Канал 3 - проверка");
    test_dialog->setText("Проконтролируте включение перемешивания в канале 3");
    test_dialog->exec();
    if(test_dialog->result() == 0) {
     emit onmixch3(false);
     setUserMessage("Перемешивание в канале 3 - <span style='color:blue'>НОРМА</span>");
    }
    else {
        setUserMessage(QString("Перемешивание в канале 3 - <span style='color:red'>БРАК</span>"));
        //return;
    }
    //Проверка Перемешивания в канале 4
    emit onmixch4(true);
    setUserMessage(QString("Контроль включения перемешивания в канале 4"));
    test_dialog->setWindowTitle("Канал 4 - проверка");
    test_dialog->setText("Проконтролируте включение перемешивания в канале 4");
    test_dialog->exec();
    if(test_dialog->result() == 0) {
        emit onmixch4(false);
        setUserMessage("Перемешивание в канале 4 - <span style='color:blue'>НОРМА</span>");
    }
    else {
        setUserMessage(QString("Перемешивание в канале 4 - <span style='color:red'>БРАК</span>"));
        //return;
    }
    //Проверка Перемешивания в канале РР
    emit onmixpp(true);
    setUserMessage(QString("Контроль включения перемешивания в канале РР"));
    test_dialog->setWindowTitle("Канал РР - проверка");
    test_dialog->setText("Проконтролируте включение перемешивания в канале РР");
    test_dialog->exec();
    if(test_dialog->result() == 0) {
        emit onmixpp(false);
        setUserMessage("Перемешивание в канале РР - <span style='color:blue'>НОРМА</span>");
    }
    else {
        setUserMessage(QString("Перемешивание в канале РР - <span style='color:red'>БРАК</span>"));
        //return;
    }
    //Проверка включения лезерных излучателей
    emit onlaser(true);
    setUserMessage(QString("Контроль включения лазерных излучателей"));
    test_dialog->setWindowTitle("Лазерные излучетели - проверка");
    test_dialog->setText("Проконтролируте включение лазерных излучателей");
    test_dialog->exec();
    if(test_dialog->result() == 0) {
        emit onlaser(false);
        setUserMessage("Лазерные излучатели - <span style='color:blue'>НОРМА</span>");
    }
    else {
        setUserMessage(QString("Лазерные излучатели - <span style='color:red'>БРАК</span>"));
        //return;
    }
    emit stop();
    deleteLater();
}

void Widget::updataTermo(bool td)
{
    termoSensor = td;
    if(!td) {
        ui->label_TD->setText(QString("Температура >37°C"));
        ui->label_TD->setStyleSheet("color: green");

    }
    else {
        ui->label_TD->setText(QString("Температура <37°C"));
        ui->label_TD->setStyleSheet("color: red");
    }
}

void Widget::getData(Channel_ID c, double time_s)
{
    QString str = QString("Канал %1: Измерение %2 (c)").arg(c).arg(time_s);
    setUserMessage(str);
    emit status(str);
    std::function<void (Channel_ID)> stop = [this](Channel_ID c) {
        stopData(c);
    };

    switch (c) {
    case Channel1_ID:
        map_y1.clear();
        pBar1->startProgress(QString("%1 %p%").arg(str), static_cast<int>(round(time_s*1000)), std::bind(stop, c));
        data1 = true;
        break;
    case Channel2_ID:
        map_y2.clear();
        pBar2->startProgress(QString("%1 %p%").arg(str), static_cast<int>(round(time_s*1000)), std::bind(stop, c));
        data2 = true;
        break;
    case Channel3_ID:
        map_y3.clear();
        pBar3->startProgress(QString("%1 %p%").arg(str), static_cast<int>(round(time_s*1000)), std::bind(stop, c));
        data3 = true;
        break;
    case Channel4_ID:
        map_y4.clear();
        pBar4->startProgress(QString("%1 %p%").arg(str), static_cast<int>(round(time_s*1000)), std::bind(stop, c));
        data4 = true;
        break;
    default:
        break;
    }
}

void Widget::stopData(Channel_ID c)
{
    //if(!isData(ChannelAll_ID)) { qDebug() << "stoped"; return; }
    switch (c) {
    case Channel1_ID:
        if(data1) {
            data1 = false;
            emit done1();
        }
        break;
    case Channel2_ID:
        if(data2) {
            data2 = false;
            emit done2();
        }
        break;
    case Channel3_ID:
        if(data3) {
            data3 = false;
            emit done3();
        }
        break;
    case Channel4_ID:
        if(data4) {
            data4 = false;
            emit done4();
        }
        break;
    default: qDebug() << "n is out of data from Widget::stopData(n)";
    }
}

void Widget::startIncub(int num, double time_s, std::function<void(void)> timeout_fun)
{
    bool b = false;
    int time_ms = static_cast<int>(round(time_s * 1000));
    if(num == 1) {
        setUserMessage(QString("Инкубация %1 c").arg(time_s));
        //int time_ms = startWin->getTimeIncube(1) * 1000;
        if(!timeout_fun) {
            std::function<void(void)> call = [](){
                ;
            };
            timeout_fun = call;
        }

        if (startWin->isChannel(Channel1_ID)) {
            if(!b) {
                b = true;
                pBar1->startProgress(QString("Инкубация %1 c %p%").arg(time_s), time_ms, timeout_fun);
            } else pBar1->startProgress(QString("Инкубация %1 c %p%").arg(time_s), time_ms);
        }
        if (startWin->isChannel(Channel2_ID)) {
            if(!b) {
                b = true;
                pBar2->startProgress(QString("Инкубация %1 c %p%").arg(time_s), time_ms, timeout_fun);
            } else pBar2->startProgress(QString("Инкубация %1 c %p%").arg(time_s), time_ms);
        }
        if (startWin->isChannel(Channel3_ID)) {
            if(!b) {
                b = true;
                pBar3->startProgress(QString("Инкубация %1 c %p%").arg(time_s), time_ms, timeout_fun);
            } else pBar3->startProgress(QString("Инкубация %1 c %p%").arg(time_s), time_ms);
        }
        if (startWin->isChannel(Channel4_ID)) {
            if(!b) {
                b = true;
                pBar4->startProgress(QString("Инкубация %1 c %p%").arg(time_s), time_ms, timeout_fun);
            } else pBar4->startProgress(QString("Инкубация %1 c %p%").arg(time_s), time_ms);
        }
        emit status(QString("Инкубация %1 c").arg(time_s));
    }
    else {
        QPointer<QMessageBox> imessageBox = new QMessageBox(this);
        imessageBox->setText(QString("<div style='color: blue'>Время инкубации истекло, добавьте разведения плазмы в рабочие каналы и нажмите кнопку \"ОК\"" ));
        connect(imessageBox.data(), &QMessageBox::buttonClicked, this, &Widget::incubeTimeout_1);
        int time_ms = static_cast<int>(startWin->getTimeIncube(1)*1000);
        pBar1->startProgress(QString("Инкубация 1 %p%"), time_ms, [imessageBox, this]() {
            pBar1->Wait();
            pBar2->Wait();
            pBar3->Wait();
            pBar4->Wait();
            setUserMessage("Время инкубации 1 истекло");
            imessageBox->exec();
        });
        pBar2->startProgress(QString("Инкубация 1 %p%"), time_ms);
        pBar3->startProgress(QString("Инкубация 1 %p%"), time_ms);
        pBar4->startProgress(QString("Инкубация 1 %p%"), time_ms);
        setUserMessage(QString("Инкубация 1 (%1c)").arg(startWin->getTimeIncube()));
        emit status(QString("Инкубация 1"));
    }
}

void Widget::incubeTimeout_1()
{
    std::function<void(Widget*)> func = &Widget::incubeTimeout_2;
    int time_ms = static_cast<int>(startWin->getTimeIncube(2) * 1000);
    //pBar1->setFormat("Инкубация 0");
    pBar1->startProgress(QString("Инкубация 2 %p%"), time_ms, std::bind(func, this));
    pBar2->startProgress(QString("Инкубация 2 %p%"), time_ms);
    pBar3->startProgress(QString("Инкубация 2 %p%"), time_ms);
    pBar4->startProgress(QString("Инкубация 2 %p%"), time_ms);
    setUserMessage(QString("Инкубация 2 (%1c)").arg(startWin->getTimeIncube(2)));
}

void Widget::incubeTimeout_2()
{
    QPointer<ImpuleWaiter> iw = new ImpuleWaiter;
    waitImpulse(iw);
}

void Widget::waitImpulse(ImpuleWaiter *iw)
{
    if(startWin->isChannel(Channel1_ID)) {
        QMetaObject::Connection *p1_widget = new QMetaObject::Connection;
        *p1_widget = connect(this, &Widget::hasPulse1, [=]() {
            disconnect(*p1_widget);
            delete p1_widget;
            iw->has_pulse_1();
            setUserMessage("Канал 1: Введен стартовый реагент в кювету");
            getData(Channel1_ID, startWin->getTimeWrite());
        });
        QMetaObject::Connection *p1_waiter = new QMetaObject::Connection;
        *p1_waiter = connect(iw, &ImpuleWaiter::press_1, [=](){
            disconnect(*p1_widget);
            delete p1_widget;
            disconnect(*p1_waiter);
            delete p1_waiter;
            setUserMessage("Канал 1: Введен стартовый реагент в кювету");
            getData(Channel1_ID, startWin->getTimeWrite());
        });
        setUserMessage("Канал 1: В ожидании добавления стартового реагента");
        iw->addWaiter(1);
        pBar1->Wait();
    }
    if(startWin->isChannel(Channel2_ID)) {
        QMetaObject::Connection *p2_widget = new QMetaObject::Connection;
        *p2_widget = connect(this, &Widget::hasPulse2, [=]() {
            disconnect(*p2_widget);
            delete p2_widget;
            iw->has_pulse_2();
            setUserMessage("Канал 2: Введен стартовый реагент в кювету");
            getData(Channel2_ID, startWin->getTimeWrite());
        });
        QMetaObject::Connection *p2_waiter = new QMetaObject::Connection;
        *p2_waiter = connect(iw, &ImpuleWaiter::press_2, [=](){
            disconnect(*p2_widget);
            delete p2_widget;
            disconnect(*p2_waiter);
            delete p2_waiter;
            setUserMessage("Канал 2: Введен стартовый реагент в кювету");
            getData(Channel2_ID, startWin->getTimeWrite());
        });
        setUserMessage("Канал 2: В ожидании добавления стартового реагента");
        iw->addWaiter(2);
        pBar2->Wait();
    }
    if(startWin->isChannel(Channel3_ID)) {
        QMetaObject::Connection *p3_widget = new QMetaObject::Connection;
        *p3_widget = connect(this, &Widget::hasPulse3, [=]() {
            disconnect(*p3_widget);
            delete p3_widget;
            iw->has_pulse_3();
            setUserMessage("Канал 3: Введен стартовый реагент в кювету");
            getData(Channel3_ID, startWin->getTimeWrite());
        });
        QMetaObject::Connection *p3_waiter = new QMetaObject::Connection;
        *p3_waiter = connect(iw, &ImpuleWaiter::press_3, [=](){
            disconnect(*p3_widget);
            delete p3_widget;
            disconnect(*p3_waiter);
            delete p3_waiter;
            setUserMessage("Канал 3: Введен стартовый реагент в кювету");
            getData(Channel3_ID, startWin->getTimeWrite());
        });
        setUserMessage("Канал 3: В ожидании добавления стартового реагента");
        iw->addWaiter(3);
        pBar3->Wait();
    }
    if(startWin->isChannel(Channel4_ID)) {
        QMetaObject::Connection *p4_widget = new QMetaObject::Connection;
        *p4_widget = connect(this, &Widget::hasPulse4, [=]() {
            disconnect(*p4_widget);
            delete p4_widget;
            iw->has_pulse_4();
            setUserMessage("Канал 4: Введен стартовый реагент в кювету");
            getData(Channel4_ID, startWin->getTimeWrite());
        });
        QMetaObject::Connection *p4_waiter = new QMetaObject::Connection;
        *p4_waiter = connect(iw, &ImpuleWaiter::press_4, [=](){
            disconnect(*p4_widget);
            delete p4_widget;
            disconnect(*p4_waiter);
            delete p4_waiter;
            setUserMessage("Канал 4: Введен стартовый реагент в кювету");
            getData(Channel4_ID, startWin->getTimeWrite());
        });
        setUserMessage("Канал 4: В ожидании добавления стартового реагента");
        iw->addWaiter(4);
        pBar4->Wait();
    }
    //setUserMessage("<div style='color: blue'>В ожидании добавления стартового реагента");
    iw->startWait();
}

double Widget::calcData(CalcData *p, Channel_ID c)
{
    double retval;
    QString kanal;
    QMap<double, double> map;
    switch(c) {
    case ChannelPP_ID:
        break;
    case Channel1_ID:
        kanal = "Канал 1";
        map = map_y1;
        break;
    case Channel2_ID:
        kanal = "Канал 2";
        map = map_y2;
        break;
    case Channel3_ID:
        kanal = "Канал 3";
        map = map_y3;
        break;
    case Channel4_ID:
        kanal = "Канал 4";
        map = map_y4;
        break;
    }

    if(!map.isEmpty()) {
        if(!isCalib()) {
            retval = p->calc(map, c);
            setUserMessage(QString("<div style='color: green'>%1: %2 %3")
                           .arg(kanal)
                           .arg(p->info())
                           .arg(retval));
        }
        else {
            if (isKo()) retval = p->calcKo(map);
            else retval = p->calcAgr(map);
            setUserMessage(QString("<div style='color: green'>%1: калибровка %2")
                           .arg(kanal)
                           .arg(retval));
        }
        //emit ret_value1(retval);
    }
    else {
        setUserMessage(QString("Канал %1: Массив данных не заполнен!").arg(c));
        return -1;
    }
    //delete p;
    return retval;
}

void Widget::writeMapData(Channel_ID c)
{
//    CalcData *p = CalcData::createCalc( startWin->getModeID() );
//    if(p == NULL) { qDebug() << "CalcData is NULL"; return; }
    setUserMessage(QString("Канал %1: Запись данных").arg(c));
    emit status(QString("Канал %1: Запись данных").arg(c));

    QStringList strList;
    auto func = [&](QMap<double, double> map) {
        if(map.isEmpty()) QMessageBox::information(this, "writeMapData", "Массив не заполнен!");
        strList << QString("t#%5\tti#%6\tp#%7\n").arg(startWin->getTimeWrite())
                                                 .arg(startWin->getTimeIncube())
                                                 .arg(startWin->isSingle());
        int i = 0;
        auto it = map.constBegin();
        while(it != map.constEnd()) {
            strList << QString("%1\t%2\t%3\n").arg(i).arg(it.value()).arg(it.key());
            ++it; ++i;
        }
    };
    strList << QString("N\t");
    switch (c) {
    case Channel1_ID:
        strList << QString("V1#%1\t").arg(startWin->getNum(1));
        func(map_y1);
        break;
    case Channel2_ID:
        strList << QString("V2#%1\t").arg(startWin->getNum(2));
        func(map_y2);
        break;
    case Channel3_ID:
        strList << QString("V3#%1\t").arg(startWin->getNum(3));
        func(map_y3);
        break;
    case Channel4_ID:
        strList << QString("V4#%1\t").arg(startWin->getNum(4));
        func(map_y4);
        break;
    default:
        break;
    }

    SaveData *save_file = new SaveData;
    //save_file->moveToThread(&save_thread);
    //connect(&save_thread, &QThread::finished, save_file, &QObject::deleteLater);
    //connect(this, &Widget::save_data, save_file, &SaveData::writeData);
//    connect(save_file, &SaveData::resultReady, [=](const QString &filename) {
//
//    });
    //save_thread.start();
    //save_file->writeData(strList);
    //emit save_data(strList);
    QFuture<QString> future = QtConcurrent::run(save_file, &SaveData::writeData, strList);
    //QFutureWatcher<int> watcher;
    //watcher.setFuture(future);
    QString filename = future.result();
    setUserMessage(QString("Канал %1: %2").arg(c).arg(filename), true, true);
//    connect(&watcher, &QFutureWatcher, [](){ future.result();});
//    qDebug() << "Widget thread ID" << QThread::currentThreadId();

}

void Widget::updateTime()
{
    //обновление времени на часах
    ui->label_time->setText("Время: " + QDateTime::currentDateTime().toString("hh:mm:ss"));
    ui->label_date->setText("Дата: " + QDateTime::currentDateTime().toString("dd.MM.yyyy"));
}

void Widget::setUserMessage(QString str, bool withtime, bool tofile)
{
    if(withtime) {
        QString msg = QString(tr("%1, Время %2"))
                .arg(str)
                .arg(QDateTime::currentDateTime().toString("hh:mm:ss.zzz"));
        ui->textEdit->append(msg);
        if(tofile) saveFiles.writeUserMsg(msg);
    }
    else {
        ui->textEdit->append(str);
        if(tofile) saveFiles.writeUserMsg(str);
    }
    QScrollBar *b = ui->textEdit->verticalScrollBar();
    b->triggerAction(QScrollBar::SliderToMaximum);
}

void Widget::on_pushButton_clicked()
{
    if( termoSensor ) {
        setUserMessage(QString("<span style='color:red'>Дождитесь нагрева термостата"));
        pBar1->setFormat("В ожидании");
        pBar1->setValue(0);
        pBar2->setFormat("В ожидании");

        pBar2->setValue(0);
        pBar3->setFormat("В ожидании");
        pBar3->setValue(0);
        pBar4->setFormat("В ожидании");
        pBar4->setValue(0);
        return;
    }
    else {
        setUserMessage("<span style='color:blue'>Термостат нагрет до 37ºC");
        pBar1->setFormat("Готов");
        pBar1->setValue(pBar1->getMaximum());
        pBar2->setFormat("Готов");
        pBar2->setValue(pBar2->getMaximum());
        pBar3->setFormat("Готов");
        pBar3->setValue(pBar3->getMaximum());
        pBar4->setFormat("Готов");
        pBar4->setValue(pBar4->getMaximum());
        connect(state, SIGNAL(stateChanged()), this, SLOT(doScenario()));
    }
    ui->pushButton->setEnabled(false);

    map_y1.clear();
    map_y2.clear();
    map_y3.clear();
    map_y4.clear();
    state->reset();

    doScenario();
}

void Widget::doScenario()
{

//  static QPointer<ImpuleWaiter> iw;
//  QString s =  state->getMessage();
//  setUserMessage(s);
    if(!state) { qDebug() << "Widget::doScenario() is empty!"; return; }
    state->doState();

    ///QMessageBox::information(this, "", s);
}

double Widget::getMAX() const
{
    return MAX;
}

void Widget::setMAX(double value)
{
    MAX = value;
    startWin->getTest()->setMax(value);
    customPlot1->yAxis->setRange(MIN, MAX);
    customPlot1->replot();
    customPlot2->yAxis->setRange(MIN, MAX);
    customPlot2->replot();
    customPlot3->yAxis->setRange(MIN, MAX);
    customPlot3->replot();
    customPlot4->yAxis->setRange(MIN, MAX);
    customPlot4->replot();
}

double Widget::getMIN() const
{
    return MIN;
}

void Widget::setMIN(double value)
{
    MIN = value;
    startWin->getTest()->setMin(value);
    customPlot1->yAxis->setRange(MIN, MAX);
    customPlot1->replot();
    customPlot2->yAxis->setRange(MIN, MAX);
    customPlot2->replot();
    customPlot3->yAxis->setRange(MIN, MAX);
    customPlot3->replot();
    customPlot4->yAxis->setRange(MIN, MAX);
    customPlot4->replot();
}

double Widget::getMIX() const
{
    return MIX_TIME_MS;
}

void Widget::setMIX(double value)
{
    MIX_TIME_MS = value;
}

double Widget::getSTOP_DX1() const
{
    return STOP_DX1;
}

void Widget::setSTOP_DX1(double value)
{
    STOP_DX1 = value;
    startWin->getTest()->setStop_dx(0, value);
}

double Widget::getSTOP_DX2() const
{
    return STOP_DX2;
}

void Widget::setSTOP_DX2(double value)
{
    STOP_DX2 = value;
    startWin->getTest()->setStop_dx(1, value);
}

double Widget::getSTOP_DX3() const
{
    return STOP_DX3;
}

void Widget::setSTOP_DX3(double value)
{
    STOP_DX3 = value;
    startWin->getTest()->setStop_dx(2, value);
}

double Widget::getSTOP_DX4() const
{
    return STOP_DX4;
}

void Widget::setSTOP_DX4(double value)
{
    STOP_DX4 = value;
    startWin->getTest()->setStop_dx(3, value);
}

double Widget::getSTART_DX1() const
{
    return START_DX1;
}

void Widget::setSTART_DX1(double value)
{
    START_DX1 = value;
    startWin->getTest()->setStart_dx(0, value);
}

double Widget::getSTART_DX2() const
{
    return START_DX2;
}

void Widget::setSTART_DX2(double value)
{
    START_DX2 = value;
    startWin->getTest()->setStart_dx(1, value);
}

double Widget::getSTART_DX3() const
{
    return START_DX3;
}

void Widget::setSTART_DX3(double value)
{
    START_DX3 = value;
    startWin->getTest()->setStart_dx(2, value);
}

double Widget::getSTART_DX4() const
{
    return START_DX4;
}

void Widget::setSTART_DX4(double value)
{
    START_DX4 = value;
    startWin->getTest()->setStart_dx(3, value);
}

void Widget::getBTP()
{
    static int i = 0;
    if (startWin->isChannel(Channel1_ID)) {
        i++;
        getData(Channel1_ID, startWin->getBtp_time());
        connect(this, &Widget::done1, [this]() {
            i--;
            disconnect(this, &Widget::done1, nullptr, nullptr);
            auto p = new CalcLevel();
            emit btp_value1(calcData(p, Channel1_ID));
            delete p;
            if (!i) { state->next(); qDebug() << "Btp done1"; }
        });
    }

    if (startWin->isChannel(Channel2_ID)) {
        i++;
        getData(Channel2_ID, startWin->getBtp_time());
        connect(this, &Widget::done2, [this]() {
            i--;
            disconnect(this, &Widget::done2, nullptr, nullptr);
            auto p = new CalcLevel();
            emit btp_value2(calcData(p, Channel2_ID));
            delete p;
            if (!i) { state->next(); qDebug() << "Btp done2"; }
        });
    }
    if (startWin->isChannel(Channel3_ID)) {
        i++;
        getData(Channel3_ID, startWin->getBtp_time());
        connect(this, &Widget::done3, [this]() {
            i--;
            disconnect(this, &Widget::done3, nullptr, nullptr);
            auto p = new CalcLevel();
            emit btp_value3(calcData(p, Channel3_ID));
            delete p;
            if (!i) { state->next(); qDebug() << "Btp done3"; }
        });
    }
    if (startWin->isChannel(Channel4_ID)) {
        i++;
        getData(Channel4_ID, startWin->getBtp_time());
        connect(this, &Widget::done4, [this]() {
            i--;
            disconnect(this, &Widget::done4, nullptr, nullptr);
            auto p = new CalcLevel();
            emit btp_value4(calcData(p, Channel4_ID));
            delete p;
            if (!i) { state->next(); qDebug() << "Btp done4"; }
        });
    }

}

void Widget::getOTP()
{
    static int i = 0;
    if (startWin->isChannel(Channel1_ID)) {
        i++;
        getData(Channel1_ID, startWin->getOtp_time());
        connect(this, &Widget::done1, [this]() {
            i--;
            disconnect(this, &Widget::done1, nullptr, nullptr);
            auto p = new CalcLevel();
            emit otp_value1(calcData(p, Channel1_ID));
            delete p;
            if (!i) { state->next(); qDebug() << "Otp done1"; }
        });
    }
    if (startWin->isChannel(Channel2_ID)) {
        i++;
        getData(Channel2_ID, startWin->getOtp_time());
        connect(this, &Widget::done2, [this]() {
            i--;
            disconnect(this, &Widget::done2, nullptr, nullptr);
            auto p = new CalcLevel();
            emit otp_value2(calcData(p, Channel2_ID));
            delete p;
            if (!i) { state->next(); qDebug() << "Otp done2"; }
        });
    }
    if (startWin->isChannel(Channel3_ID)) {
        i++;
        getData(Channel3_ID, startWin->getOtp_time());
        connect(this, &Widget::done3, [this]() {
            i--;
            disconnect(this, &Widget::done3, nullptr, nullptr);
            auto p = new CalcLevel();
            emit otp_value3(calcData(p, Channel3_ID));
            delete p;
            if (!i) { state->next(); qDebug() << "Otp done3"; }
        });
    }
    if (startWin->isChannel(Channel4_ID)) {
        i++;
        getData(Channel4_ID, startWin->getOtp_time());
        connect(this, &Widget::done4, [this]() {
            i--;
            disconnect(this, &Widget::done4, nullptr, nullptr);
            auto p = new CalcLevel();
            emit otp_value4(calcData(p, Channel4_ID));
            delete p;
            if (!i) { state->next(); qDebug() << "Otp done4"; }
        });
    }
}

void Widget::onMixChls(bool b)
{
    if(startWin->isChannel(Channel1_ID))
        onMotor(Channel1_ID, b);
    if(startWin->isChannel(Channel2_ID))
        onMotor(Channel2_ID, b);
    if(startWin->isChannel(Channel3_ID))
        onMotor(Channel3_ID, b);
    if(startWin->isChannel(Channel4_ID))
        onMotor(Channel4_ID, b);
}

void Widget::onMixPP(bool b)
{
    onMotor(ChannelPP_ID, b);
}

void Widget::onLazer(bool b)
{
    if(b) setUserMessage("Включение питания лазеров каждого из каналов");
    else setUserMessage("Выключение питания лазеров каждого из каналов");
    emit onlaser(b);
}

void Widget::incubation1(State *next)
{
    setUserMessage(QString("<span style = 'color: blue'>%1</span>").arg(next->getMessage()));
    QMetaObject::Connection obj = connect(this, SIGNAL(value_come(QVariantList)), this, SLOT(fix_point(QVariantList)));
    QMessageBox::information(this, "Инкубация", next->getMessage());
    startIncub(1, startWin->getTimeIncube(1), [=]() {
        disconnect(obj);
        //setUserMessage(QString("<span style = 'color: blue'>Время инкубации истекло</span>"));
        next->next();
    });
}

void Widget::incubation2(State *next)
{
    startIncub(2, startWin->getTimeIncube(1), [=]() {
        //setUserMessage(QString("<span style = 'color: blue'>Время инкубации истекло</span>"));
        next->next();
    });
}

void Widget::selectInductor(State *next)
{
    SelectInductor *si = new SelectInductor(this);
    connect(si, &SelectInductor::finished, [=](){
        next->next();
        si->deleteLater();
    });
        si->show();
    //next->next();
}

void Widget::finish()
{
    emit stop();
    if(!startWin->isChannel(Channel1_ID)) map_y1.clear();
    if(!startWin->isChannel(Channel2_ID)) map_y2.clear();
    if(!startWin->isChannel(Channel3_ID)) map_y3.clear();
    if(!startWin->isChannel(Channel4_ID)) map_y4.clear();
    emit end(map_y1, map_y2, map_y3, map_y4);
}

void Widget::agr()
{

}

void Widget::ko(State *state)
{
    static int i = 0;
    if (startWin->isChannel(Channel1_ID)) {
        i++;
        connect(this, &Widget::done1, [=]() {
            i--;
            disconnect(this, &Widget::done1, nullptr, nullptr);
            if (!i) { state->next(); qDebug() << "done1"; }
        });
    }
    if (startWin->isChannel(Channel2_ID)) {
        i++;
        connect(this, &Widget::done2, [=]() {
            i--;
            disconnect(this, &Widget::done2, nullptr, nullptr);
            if (!i) { state->next(); qDebug() << "done2"; }
        });
    }
    if (startWin->isChannel(Channel3_ID)) {
        i++;
        connect(this, &Widget::done3, [=]() {
            i--;
            disconnect(this, &Widget::done3, nullptr, nullptr);
            if (!i) { state->next(); qDebug() << "done3"; }
        });
    }
    if (startWin->isChannel(Channel4_ID)) {
        i++;
        connect(this, &Widget::done4, [=]() {
            i--;
            disconnect(this, &Widget::done4, nullptr, nullptr);
            if (!i) { state->next(); qDebug() << "done4"; }
        });
    }
    waitImpulse(new ImpuleWaiter(this));
}

void Widget::calc()
{
    CalcData* p = CalcData::createCalc(startWin->getTest(), startWin->getCalib(), startWin->getModeID());
    if(!p) { setUserMessage(QString("Ошибка при выделении памяти под класс CalcData")); return; }
    if(startWin->isSingle()) {
        if( startWin->isChannel(Channel1_ID) )
            emit ret_value1(calcData(p, Channel1_ID), state->getLevel());
        if( startWin->isChannel(Channel2_ID) )
            emit ret_value2(calcData(p, Channel2_ID), state->getLevel());
        if( startWin->isChannel(Channel3_ID) )
            emit ret_value3(calcData(p, Channel3_ID), state->getLevel());
        if( startWin->isChannel(Channel4_ID) )
            emit ret_value4(calcData(p, Channel4_ID), state->getLevel());
    } else {
        if( startWin->isChannel(Channel1_ID) )
            if( startWin->isChannel(Channel2_ID) ) {
                double v1 = calcData(p, Channel1_ID);
                double v2 = calcData(p, Channel2_ID);
                emit ret_value1_2( (v1+v2)/2, state->getLevel() );
        }
        if( startWin->isChannel(Channel3_ID) )
            if( startWin->isChannel(Channel4_ID) ) {
                double v3 = calcData(p, Channel3_ID);
                double v4 = calcData(p, Channel4_ID);
                emit ret_value3_4( (v3+v4)/2, state->getLevel() );
            }
    }
    delete p;
}

void Widget::write()
{
    if( startWin->isChannel(Channel1_ID) ) writeMapData(Channel1_ID);
    if( startWin->isChannel(Channel2_ID) ) writeMapData(Channel2_ID);
    if( startWin->isChannel(Channel3_ID) ) writeMapData(Channel3_ID);
    if( startWin->isChannel(Channel4_ID) ) writeMapData(Channel4_ID);
}
