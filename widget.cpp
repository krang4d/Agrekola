﻿#include "widget.h"
#include "ui_widget.h"

#include <QScrollBar>
#include <QMessageBox>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QtConcurrent>
#include <functional>

#define DX 0.1f
#define MIN -6.0f
#define MAX 6.0f

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    pBar1(new ProgressTimerBar), pBar2(new ProgressTimerBar),
    pBar3(new ProgressTimerBar), pBar4(new ProgressTimerBar),
    data1(false), data2(false), data3(false), data4(false),
    pulse1(false), pulse2(false), pulse3(false), pulse4(false),
    ready1(false), ready2(false), ready3(false), ready4(false),
    incub(false)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("Программы сбора данных с АЦП(E-154) по 4 каналам");
    customPlot1 = ui->frame_1;
    ui->groupBox_f1->layout()->addWidget(pBar1);
    customPlot2 = ui->frame_2;
    ui->groupBox_f2->layout()->addWidget(pBar2);
    customPlot3 = ui->frame_3;
    ui->groupBox_f3->layout()->addWidget(pBar3);
    customPlot4 = ui->frame_4;
    ui->groupBox_f4->layout()->addWidget(pBar4);
    ui->groupBox_Mix->setVisible(false);
    setupRealtimeData();
    setupTimers();
    installEventFilter(this);
}

Widget::~Widget()
{
    emit stop();
    delete ui;
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::Close) {
        qDebug() << "Close Event is emited in the Widget!";
        parentWidget()->show();
        emit stop();
        return true;
    }
    if(event->type() == QEvent::KeyPress) {
        qDebug() << "Event kayPress";
        QKeyEvent *kayEvent = static_cast<QKeyEvent *>(event);
        if(kayEvent->key() == Qt::Key_Enter) {
            bool b = ui->groupBox_Mix->isVisible();
            if(b) {
                ui->groupBox_Mix->setVisible(false);
                qDebug() << "setVisible(false)";
            }
            else {
                ui->groupBox_Mix->setVisible(true);
                qDebug() << "setVisible(true)";
            }
        }
        return true;
    }
    return QWidget::eventFilter(watched, event);
}

void Widget::setUserMessage(QString str, bool withtime, bool tofile)
{
    if(withtime) {
        QString msg = QString(tr("%1,    Время %2"))
                .arg(str)
                .arg(dt.toString("hh:mm:ss.zzz"));
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

void Widget::setMode(int b) {

    mode = b;
}

int Widget::getMode()
{
    return mode;
}

void Widget::setupRealtimeData() {
    std::function<bool(void)> foo = [this](){ if(startWin.isNull()) return true; else return startWin->isSingle();};
    if(foo()) {
        QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
        timeTicker->setTimeFormat("%m:%s");

        customPlot1->addGraph();
        customPlot1->graph(0)->setPen(QPen(QColor(10, 110, 40)));
        customPlot1->xAxis->setTicker(timeTicker);
        customPlot1->axisRect()->setupFullAxesBox();
        customPlot1->xAxis->setLabel("t, сек");
        customPlot1->yAxis->setLabel("V1, Вольт");
        customPlot1->yAxis->setRange(MIN, MAX);

        // make left and bottom axes transfer their ranges to right and top axes:
        connect(customPlot1->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot1->xAxis2, SLOT(setRange(QCPRange)));
        connect(customPlot1->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot1->yAxis2, SLOT(setRange(QCPRange)));

        customPlot2->addGraph();
        customPlot2->graph(0)->setPen(QPen(QColor(255, 110, 40)));
        customPlot2->xAxis->setTicker(timeTicker);
        customPlot2->axisRect()->setupFullAxesBox();
        customPlot2->xAxis->setLabel("t, сек");
        customPlot2->yAxis->setLabel("V2, Вотльт");
        customPlot2->yAxis->setRange(MIN, MAX);

        connect(customPlot2->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot2->xAxis2, SLOT(setRange(QCPRange)));
        connect(customPlot2->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot2->yAxis2, SLOT(setRange(QCPRange)));

        customPlot3->addGraph();
        customPlot3->graph(0)->setPen(QPen(QColor(255, 110, 200)));
        customPlot3->xAxis->setTicker(timeTicker);
        customPlot3->axisRect()->setupFullAxesBox();
        customPlot3->xAxis->setLabel("t, сек");
        customPlot3->yAxis->setLabel("V3, Вотльт");
        customPlot3->yAxis->setRange(MIN, MAX);

        connect(customPlot3->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot3->xAxis2, SLOT(setRange(QCPRange)));
        connect(customPlot3->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot3->yAxis2, SLOT(setRange(QCPRange)));

        customPlot4->addGraph();
        customPlot4->graph(0)->setPen(QPen(QColor(255, 200, 40)));
        customPlot4->xAxis->setTicker(timeTicker);
        customPlot4->axisRect()->setupFullAxesBox();
        customPlot4->xAxis->setLabel("t, сек");
        customPlot4->yAxis->setLabel("V4, Вотльт");
        customPlot4->yAxis->setRange(MIN, MAX);

        connect(customPlot4->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot4->xAxis2, SLOT(setRange(QCPRange)));
        connect(customPlot4->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot4->yAxis2, SLOT(setRange(QCPRange)));

//        // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
//        disconnect(&plotTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlotDuo()));
//        plotTimer.stop();
//        connect(&plotTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlotSingle()));
//        plotTimer.start(0); // Interval 0 means to refresh as fast as possible
    }
    else {
        QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
        timeTicker->setTimeFormat("%m:%s");

        customPlot1->addGraph();
        customPlot1->graph(0)->setPen(QPen(QColor(10, 110, 40)));
        customPlot1->graph(1)->setPen(QPen(QColor(255, 110, 40)));
        customPlot1->xAxis->setTicker(timeTicker);
        customPlot1->axisRect()->setupFullAxesBox();
        customPlot1->xAxis->setLabel("Время, с");
        customPlot1->yAxis->setLabel("Напряжение, В");
        customPlot1->yAxis->setRange(MIN, MAX);

        // make left and bottom axes transfer their ranges to right and top axes:
        connect(customPlot1->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot1->xAxis2, SLOT(setRange(QCPRange)));
        connect(customPlot1->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot1->yAxis2, SLOT(setRange(QCPRange)));

        customPlot2->addGraph();
        customPlot2->graph(0)->setPen(QPen(QColor(255, 110, 200)));
        customPlot2->graph(1)->setPen(QPen(QColor(255, 200, 40)));
        customPlot2->xAxis->setTicker(timeTicker);
        customPlot2->axisRect()->setupFullAxesBox();
        customPlot2->xAxis->setLabel("Время, с");
        customPlot2->yAxis->setLabel("Напряжение, В");
        customPlot2->yAxis->setRange(MIN, MAX);

        connect(customPlot2->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot2->xAxis2, SLOT(setRange(QCPRange)));
        connect(customPlot2->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot2->yAxis2, SLOT(setRange(QCPRange)));

//        // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
//        disconnect(&plotTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlotSingle()));
//        plotTimer.stop();
//        connect(&plotTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlotDuo()));
//        plotTimer.start(0); // Interval 0 means to refresh as fast as possible
    }
}

void Widget::realtimeDataSlot(QVariantList a) {
    //qDebug() << "ThreadID: " << QThread::currentThreadId() << "a0 = " << a[0];
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    static double lastPointV1 = a[0].toDouble();
    static double lastPointV2 = a[1].toDouble();
    static double lastPointV3 = a[2].toDouble();
    static double lastPointV4 = a[3].toDouble();
    double dx1 = std::abs(a[0].toDouble() - lastPointV1);
    double dx2 = std::abs(a[1].toDouble() - lastPointV2);
    double dx3 = std::abs(a[2].toDouble() - lastPointV3);
    double dx4 = std::abs(a[3].toDouble() - lastPointV4);
    lastPointV1 = a[0].toDouble();
    if((dx1 > DX || pulse1) && ready1) {
        pulse1 = false;
        ready1 = false;
        emit hasPulse1();
        setUserMessage("Канал 1 - импульс");
        qDebug() << QString("The pulse is come! dx1=%1").arg(dx1);
        startData(1);
    }
    lastPointV2 = a[1].toDouble();
    if((dx2 > DX || pulse2) && ready2) {
        pulse2 = false;
        ready2 = false;
        emit hasPulse2();
        setUserMessage("Канал 2 - импульс");
        qDebug() << QString("The pulse is come! dx2=%1").arg(dx2);
        startData(2);
    }
    lastPointV3 = a[2].toDouble();
    if((dx3 > DX || pulse3) && ready3) {
        pulse3 = false;
        ready3 = false;
        emit hasPulse3();
        setUserMessage("Канал 3 - импульс");
        qDebug() << QString("The pulse is come! dx3=%1").arg(dx3);
        startData(3);
    }
    lastPointV4 = a[3].toDouble();
    if((dx4 > DX || pulse4) && ready4) {
        pulse4 = false;
        ready4 = false;
        emit hasPulse4();
        setUserMessage("Канал 4 - импульс");
        qDebug() << QString("The pulse is come! dx4=%1").arg(dx4);
        startData(4);
    }

    if (key-lastPointKey > 0.01) {// at most add point every 10 ms
        std::function<bool(void)> foo = [this](){ if(startWin.isNull()) return true; else return startWin->isSingle();};
        if(foo()) {
          customPlot1->graph(0)->addData(key, a[0].toDouble());
          customPlot2->graph(0)->addData(key, a[1].toDouble());
          customPlot3->graph(0)->addData(key, a[2].toDouble());
          customPlot4->graph(0)->addData(key, a[3].toDouble());

          // make key axis range scroll with the data (at a constant range size of 8):
          customPlot1->xAxis->setRange(key, 8, Qt::AlignRight);
          customPlot1->replot();

          customPlot2->xAxis->setRange(key, 8, Qt::AlignRight);
          customPlot2->replot();

          customPlot3->xAxis->setRange(key, 8, Qt::AlignRight);
          customPlot3->replot();

          customPlot4->xAxis->setRange(key, 8, Qt::AlignRight);
          customPlot4->replot();
        }
        else {
          customPlot1->graph(0)->addData(key, a[0].toDouble());
          customPlot1->graph(1)->addData(key, a[1].toDouble());
          customPlot2->graph(0)->addData(key, a[2].toDouble());
          customPlot2->graph(1)->addData(key, a[3].toDouble());

          // make key axis range scroll with the data (at a constant range size of 8):
          customPlot1->xAxis->setRange(key, 8, Qt::AlignRight);
          customPlot1->replot();

          customPlot2->xAxis->setRange(key, 8, Qt::AlignRight);
          customPlot2->replot();

          customPlot3->xAxis->setRange(key, 8, Qt::AlignRight);
          customPlot3->replot();

          customPlot4->xAxis->setRange(key, 8, Qt::AlignRight);
          customPlot4->replot();
        }
        if(isData(1)) {
            if(startWin->isChannel_1() ) {
                map_y1.insert(key, a[0].toDouble());
                //ui->label_led1->setStyleSheet("color: green;");
            }
        }
        //else ui->label_led1->setStyleSheet("color: yellow;");
        if(isData(2)) {
            if(startWin->isChannel_2()) {
                map_y2.insert(key, a[1].toDouble());
                //ui->label_led2->setStyleSheet("color: green;");
            }
        }
        //else ui->label_led2->setStyleSheet("color: yellow;");
        if(isData(3)) {
            if(startWin->isChannel_3()) {
                map_y3.insert(key, a[2].toDouble());
                //ui->label_led3->setStyleSheet("color: green;");
            }
        }
        //else ui->label_led3->setStyleSheet("color: yellow;");
        if(isData(4)) {
            if(startWin->isChannel_4()) {
                map_y4.insert(key, a[3].toDouble());
                //ui->label_led4->setStyleSheet("color: green;");
            }
        }
        //else ui->label_led4->setStyleSheet("color: yellow;");
        lastPointKey = key;
    }
    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) {// average fps over 2 seconds
        ui->label_fps->setText(QString("%1 FPS, Total Data points: %2")
                        .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
                        .arg(customPlot1->graph(0)->data()->size()+customPlot2->graph(0)->data()->size()\
                             + customPlot3->graph(0)->data()->size() + customPlot4->graph(0)->data()->size()));
        lastFpsKey = key;
        frameCount = 0;
    }
}

void Widget::on_checkBox_1_stateChanged(int arg1)
{
    if(arg1) setUserMessage("Канал 1: включение перемешивания");
    else setUserMessage("Канал 1: выключение перемешивания");
    emit onmixch1(arg1);
}

void Widget::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1) setUserMessage("Канал 2: включение перемешивания");
    else setUserMessage("Канал 2: выключение перемешивания");
    emit onmixch2(arg1);
}

void Widget::on_checkBox_3_stateChanged(int arg1)
{
    if(arg1) setUserMessage("Канал 3: включение перемешивания");
    else setUserMessage("Канал 3: выключение перемешивания");
    emit onmixch3(arg1);
}

void Widget::on_checkBox_4_stateChanged(int arg1)
{
    if(arg1) setUserMessage("Канал 4: включение перемешивания");
    else setUserMessage("Канал 4: выключение перемешивания");
    emit onmixch4(arg1);
}

void Widget::on_checkBox_PP_stateChanged(int arg1)
{
    if(arg1) setUserMessage("Канал РР: включение перемешивания");
    else setUserMessage("Канал РР: выключение перемешивания");
    emit onmixpp(arg1);
}

void Widget::on_checkBox_L_stateChanged(int arg1)
{
    if(arg1) setUserMessage("Включение лазеров");
    else setUserMessage("Выключение лазеров");
    emit onlaser(arg1);
}

void Widget::on_pushButton_clicked()
{
    startWin = new StartMeasurment(getMode());
    startWin->show();
    connect(startWin, SIGNAL(startMeasurment()), this, SLOT(startMeasurment()));

}

void Widget::updataTermo(bool td)
{
    if(!td) {
        ui->label_TD->setText(QString("Температура >37°C"));
        ui->label_TD->setStyleSheet("color: green");
    }
    else {
        ui->label_TD->setText(QString("Температура <37°C"));
        ui->label_TD->setStyleSheet("color: red");
    }
}

void Widget::updateTime()
{
    //обновление времени на часах
    dt = QDateTime::currentDateTime();
    ui->label_time->setText("Время: " + dt.toString("hh:mm:ss"));
    ui->label_date->setText("Дата: " + dt.toString("dd.MM.yyyy"));

    //обновление времени инкубации
    static double t;
    double interval = currentTimer.interval()/1000.0;
    if(isIncub()) {
        ui->label_incube->setText(QString("Время инкубации, %1 сек")
                                  .arg(startWin->getTimeIncube() - t));
        t+=interval;
    }
    else {
        ui->label_incube->setText(QString("Время инкубации, --- сек"));
        t=0;
    }
}

void Widget::startMeasurment()
{
    ui->pushButton->setEnabled(false);
    QString msg;
    if(!startWin->isCancel()) {
        if(startWin->isSingle()) {

            if (startWin->isChannel_1()) {
                msg += QString("№1 = %1, ").arg(startWin->getNum_1());
                ui->checkBox_1->setChecked(true); //включение перемешивания 1
                ui->groupBox_f1->setTitle("Канал 1");
                ui->groupBox_f1->show();
            }
            else {
                msg += QString("№1 - выкл., ");
                ui->groupBox_f1->hide();
            }

            if (startWin->isChannel_2()) {
                msg += QString("№2 = %1, ").arg(startWin->getNum_2());
                ui->checkBox_2->setChecked(true); //включение перемешивания 2
                ui->groupBox_f2->setTitle("Канал 2");
                ui->groupBox_f2->show();
            }
            else {
                msg += QString("№2 - выкл., ");
                ui->groupBox_f2->hide();
            }

            if (startWin->isChannel_3()) {
                msg += QString("№3 = %1, ").arg(startWin->getNum_3());
                ui->checkBox_3->setChecked(true); //включение перемешивания 3
                ui->groupBox_f3->setTitle("Канал 3");
                ui->groupBox_f3->show();
            }
            else {
                msg += QString("№3 - выкл., ");
                ui->groupBox_f3->hide();
            }

            if (startWin->isChannel_4()) {
                msg += QString("№4 = %1 ").arg(startWin->getNum_4());
                ui->checkBox_4->setChecked(true); //включение перемешивания 4
                ui->groupBox_f4->setTitle("Канал 4");
                ui->groupBox_f4->show();
            }
            else {
                msg += QString("№4 - выкл. ");
                ui->groupBox_f4->hide();
            }

            msg = QString("Начало сбора данных, одиночные пробы (t = %1c, %2)")
                    .arg(startWin->getTime()).arg(msg);
            setUserMessage(msg, true, true);
            ui->checkBox_L->setChecked(true); //включение лазеров
            setupRealtimeData();
        }
        else {

            if (startWin->isChannel_1()) {
                msg += QString("№1, 2 = %1, ").arg(startWin->getNum_1());
                ui->groupBox_f1->setTitle("Канал 1, 2");
                ui->groupBox_f2->hide();
                ui->checkBox_1->setChecked(true); //включение перемешивания 1
                ui->checkBox_2->setChecked(true); //включение перемешивания 2
            }
            else {
                msg += QString("№1, 2 - выкл., ");
                ui->groupBox_f1->hide();
                ui->groupBox_f2->hide();
            }

            if (startWin->isChannel_3()) {
                msg += QString("№3, 4 = %1, ").arg(startWin->getNum_3());
                ui->groupBox_f3->setTitle("Канал 3, 4");
                ui->groupBox_f4->hide();
                ui->checkBox_3->setChecked(true); //включение перемешивания 3
                ui->checkBox_4->setChecked(true); //включение перемешивания 4

            }
            else {
                msg += QString("№3, 4 - выкл., ");
                ui->groupBox_f3->hide();
                ui->groupBox_f4->hide();
            }
            msg = QString("Начало сбора данных, парные пробы (t = %1c, %2)")
                    .arg(startWin->getTime()).arg(msg);
            setUserMessage(msg, true, true);
            setupRealtimeData();
        }
        if( getMode() == 1 ||getMode() == 2 ) {
            startIncub(2);
//            std::function<void (void)> func = [this](){startIncub(3, 2);};
            //QPointer<ProgressTimerBar> pb = new ProgressTimerBar;
//            pBar1->startProgress("Время инкубации №1", t, func);
//            pBar2->startProgress("Время инкубации №1", t);
//            pBar3->startProgress("Время инкубации №1", t);
//            pBar4->startProgress("Время инкубации №1", t);
            //connect(pBar1.data(), SIGNAL(done()), pb.data(), SLOT(deleteLater()));
        }
        else startIncub(1);
    }
}

void Widget::startData(int n)
{
    QString str = QString("Измерение по каналу %1").arg(n);
    setUserMessage(str);
    emit status(str);
    std::function<void (int)> func = [this](int n){
        writeMapData(n);
    };
    //QPointer<ProgressTimerBar> pb = new ProgressTimerBar;
    //pb->startProgress(QString("%1 %p%").arg(str), 10, startWin->getTime() * 1000, std::bind(func, n));
    switch (n) {
    case 1:
        //ui->groupBox_f1->layout()->addWidget(pb);
        pBar1->startProgress(QString("%1 %p%").arg(str), startWin->getTime() * 1000, std::bind(func, n));
        data1 = true;
        break;
    case 2:
        //ui->groupBox_f2->layout()->addWidget(pb);
        pBar2->startProgress(QString("%1 %p%").arg(str), startWin->getTime() * 1000, std::bind(func, n));
        data2 = true;
        break;
    case 3:
        //ui->groupBox_f3->layout()->addWidget(pb);
        pBar3->startProgress(QString("%1 %p%").arg(str), startWin->getTime() * 1000, std::bind(func, n));
        data3 = true;
        break;
    case 4:
        //ui->groupBox_f4->layout()->addWidget(pb);
        pBar4->startProgress(QString("%1 %p%").arg(str), startWin->getTime() * 1000, std::bind(func, n));
        data4 = true;
        break;
    default:
        break;
    }
}

void Widget::stopData(int n)
{
    switch (n) {
    case 1:
        data1 = false;
        pulse1 = false;
        ui->checkBox_1->setChecked(false); //включение перемешивания
        break;
    case 2:
        data2 = false;
        pulse2 = false;
        ui->checkBox_2->setChecked(false);
        break;
    case 3:
        data3 = false;
        pulse3 = false;
        ui->checkBox_3->setChecked(false);
        break;
    case 4:
        data4 = false;
        pulse4 = false;
        ui->checkBox_4->setChecked(false);
        break;
    default: qDebug() << "n is out of data from Widget::stopData(n)";
    }
    if (!isData(1) && !isData(2) && !isData(3) && !isData(4)) {
        setUserMessage(QString("Конец сбора данных"));
        ui->checkBox_L->setChecked(false);
        ui->pushButton->setEnabled(true);
    }
}

bool Widget::isData(int n)
{
    switch (n) {
    case 1:
        return data1;
    case 2:
        return data2;
    case 3:
        return data3;
    case 4:
        return data4;
    default: qDebug() << "n is out of data from Widget::isData(n)";
    }
    return 0;
}

void Widget::startIncub(int num)
{
    incub = true;

    setUserMessage(QString("Инкубация %1").arg(num));

    //std::function<void(Widget*)> func = &Widget::incubeTimeout;

    if(num == 1) {
        std::function<void(Widget*)> func = &Widget::incubeTimeout;
        std::function<void(void)> foo = std::bind(func, this);
        int time_ms = startWin->getTimeIncube(1) * 1000;
        pBar1->startProgress(QString("Инкубация %1 %p%").arg(num), time_ms, foo);
        pBar2->startProgress(QString("Инкубация %1 %p%").arg(num), time_ms);
        pBar3->startProgress(QString("Инкубация %1 %p%").arg(num), time_ms);
        pBar4->startProgress(QString("Инкубация %1 %p%").arg(num), time_ms);
    }
    else {
        QMessageBox *imessageBox = new QMessageBox(this);
        connect(imessageBox, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(incubeTimeout_0()));
        //connect(imessageBox.data(), SIGNAL(buttonClicked(QAbstractButton*)), imessageBox.data(), SLOT(deleteLater()));
        imessageBox->setText(QString("Время инкубации истекло, добавьте разведения плазмы в рабочие каналы и нажмите кнопку \"ОК\"" ));

        //imessageBox->show();
        std::function<void(QMessageBox*)> func = &QMessageBox::exec; //&Widget::incubeTimeout_0;
        std::function<void(void)> foo = std::bind(func, imessageBox);

        int time_ms = startWin->getTimeIncube(2) * 1000;
        pBar1->startProgress(QString("Инкубация %1 %p%").arg(num), time_ms, foo);
        pBar2->startProgress(QString("Инкубация %1 %p%").arg(num), time_ms);
        pBar3->startProgress(QString("Инкубация %1 %p%").arg(num), time_ms);
        pBar4->startProgress(QString("Инкубация %1 %p%").arg(num), time_ms);
    }
    emit status(QString("Инкубация %1").arg(num));
}

void Widget::stopIncub()
{
    setUserMessage("Время инкубации истекло, добавьте стартовый реагент!");
    incub = false;
}

bool Widget::isIncub()
{
    return incub;
}

void Widget::incubeTimeout_0()
{
    std::function<void(Widget*)> func = &Widget::incubeTimeout;
    int num = 1;
    int time_ms = startWin->getTimeIncube(1) * 1000;
    //pBar1->setFormat("Инкубация 0");
    pBar1->startProgress(QString("Инкубация %1 %p%").arg(num), time_ms, std::bind(func, this));
    pBar2->startProgress(QString("Инкубация %1 %p%").arg(num), time_ms);
    pBar3->startProgress(QString("Инкубация %1 %p%").arg(num), time_ms);
    pBar4->startProgress(QString("Инкубация %1 %p%").arg(num), time_ms);
}

void Widget::incubeTimeout()
{
    QPointer<ImpuleWaiter> iw = new ImpuleWaiter;

    stopIncub();
    if(startWin->isChannel_1()) {
        setUserMessage("Канала 1 в ожидании добавления стартового реагента");
        ready1 = true;
        iw->addWaiter(1);
    }
    if(startWin->isChannel_2()) {
        setUserMessage("Канала 2 в ожидании добавления стартового реагента");
        ready2 = true;
        iw->addWaiter(2);
    }
    if(startWin->isChannel_3()) {
        setUserMessage("Канала 3 в ожидании добавления стартового реагента");
        ready3 = true;
        iw->addWaiter(3);
    }
    if(startWin->isChannel_4()) {
        setUserMessage("Канала 4 в ожидании добавления стартового реагента");
        ready4 = true;
        iw->addWaiter(4);
    }
    connect(this, &Widget::hasPulse1, iw, &ImpuleWaiter::has_pulse_1);
    connect(this, &Widget::hasPulse2, iw, &ImpuleWaiter::has_pulse_2);
    connect(this, &Widget::hasPulse3, iw, &ImpuleWaiter::has_pulse_3);
    connect(this, &Widget::hasPulse4, iw, &ImpuleWaiter::has_pulse_4);

    connect(iw, &ImpuleWaiter::press_1, [=](){
        disconnect(this, &Widget::hasPulse1, iw, &ImpuleWaiter::has_pulse_1);
        pulse1 = true;});
    connect(iw, &ImpuleWaiter::press_2, [=](){
        disconnect(this, &Widget::hasPulse2, iw, &ImpuleWaiter::has_pulse_2);
        pulse2 = true;});
    connect(iw, &ImpuleWaiter::press_3, [=](){
        disconnect(this, &Widget::hasPulse3, iw, &ImpuleWaiter::has_pulse_3);
        pulse3 = true;});
    connect(iw, &ImpuleWaiter::press_4, [=](){
        disconnect(this, &Widget::hasPulse4, iw, &ImpuleWaiter::has_pulse_4);
        pulse4 = true;});

    iw->startWait();
//    QMessageBox::information(this, "Инкубация",
//                             "Время инкубации истекло, добавьте стартовый реагент\n"
//                             "и нажмите кнопку СТАРТ для соответствующего канала, если\n"
//                             "измерение не запустилось автоматически. Нажмите ОК для продолжения.");
//    emit status(QString("Время инкубации вышло"));
    //запуск измерени
    //startData();
}

void Widget::setupTimers()
{
    //настройка таймера для часов
    connect(&currentTimer, SIGNAL(timeout()), SLOT(updateTime()));
    currentTimer.start(300);
    dt = QDateTime::currentDateTime();
    setUserMessage(QString("Начало работы программы    Дата %1").arg(dt.toString("dd.MM.yyyy")));
}

void Widget::writeMapData(const int n)
{
    stopData(n);
    setUserMessage(QString("Запись данных по каналу %1").arg(n));
    emit status(QString("Запись данных по каналу %1").arg(n));
    //QPointer<QProgressDialog> pb = new QProgressDialog;
    //pb->setLabelText(QString("Запись данных %p%"));
    QPointer<ProgressTimerBar> pBar;
    switch (n) {
    case 1:
        //ui->groupBox_f1->layout()->addWidget(pb);
        pBar = pBar1;
        break;
    case 2:
        //ui->groupBox_f2->layout()->addWidget(pb);
        pBar = pBar2;
        break;
    case 3:
        //ui->groupBox_f3->layout()->addWidget(pb);
        pBar = pBar3;
        break;
    case 4:
        //ui->groupBox_f4->layout()->addWidget(pb);
        pBar = pBar4;
        break;
    default:
        break;
    }
    pBar->setFormat(QString("Запись данных %p%"));
    //pb->show();
    qDebug().noquote() << QString("Запись данных по каналу %1").arg(n);

    QStringList strList;
    auto func = [&](QMap<double, double> map) {
        strList << QString("t#%5\tti#%6\tp#%7\n").arg(startWin->getTime())
                                                 .arg(startWin->getTimeIncube())
                                                 .arg(startWin->isSingle());
        int i = 0;
        auto it = map.constBegin();
        while(it != map.constEnd()) {
            //pb->setMaximum(map.count());
            //pb->setValue(i+1);//i*100/x.length());
            strList << QString("%1\t%2\t%3\n").arg(i).arg(it.value()).arg(it.key());
            ++it; ++i;
        }
        //map.clear();
    };
    strList << QString("N\t");
    if( n == 1 && !map_y1.isEmpty() ) {
        strList << QString("V1#%1\t").arg(startWin->getNum_1());
        func(map_y1);
        pBar->setMaximum(map_y1.count());
        map_y1.clear();
    }
    if( n == 2 && !map_y2.isEmpty() ) {
        strList << QString("V2#%1\t").arg(startWin->getNum_2());
        func(map_y2);
        pBar->setMaximum(map_y2.count());
        map_y2.clear();
    }
    if( n == 3 && !map_y3.isEmpty() ) {
        strList << QString("V3#%1\t").arg(startWin->getNum_3());
        func(map_y3);
        pBar->setMaximum(map_y3.count());
        map_y3.clear();
    }
    if( n == 4 && !map_y4.isEmpty() ) {
        strList << QString("V4#%1\t").arg(startWin->getNum_4());
        func(map_y4);
        pBar->setMaximum(map_y4.count());
        map_y4.clear();
    }
    setUserMessage(saveFiles.writeData(strList, pBar), true, true);
}

void Widget::on_comboBox_currentIndexChanged(int index)
{
    setMode(index);
    //setUserMessage(QString(agrekola->GetInformation()), false);
    QString str;
    switch (index){
    case 0:
        str = tr("Тест (Test 0)");
        //ui->groupBox_Mix->setVisible(b);
        break;
    case 1:
        str = tr("Определение параметров агрегации, измерение (Agr1 1)");
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
    setUserMessage(str, 0);
}
