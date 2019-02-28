﻿#include "widget.h"
#include "ui_widget.h"

#include <QScrollBar>
#include <QMessageBox>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QtConcurrent>
#include <functional>
#include "agr1.h"

//#define STOP_DX 0.1f
//#define MIN -6.0f
//#define MAX 6.0f

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    data1(false), data2(false), data3(false), data4(false),
    pulse1(false), pulse2(false), pulse3(false), pulse4(false),
    ready1(false), ready2(false), ready3(false), ready4(false),
    termoSensor(false), incub(false), waitPulse(false), single(true),
    pBar1(new ProgressTimerBar), pBar2(new ProgressTimerBar),
    pBar3(new ProgressTimerBar), pBar4(new ProgressTimerBar),
    START_DX(0.1), STOP_DX(0.1), MIN(-6.0), MAX(6.0),
    startWin(new StartMeasurement)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("Программа сбора данных с АЦП(E-154) по 4 каналам");

    setupWidget();
    setupTimers();
    installEventFilter(this);

    emit onmixch1(false);
    emit onmixch2(false);
    emit onmixch3(false);
    emit onmixch4(false);
    emit onlaser(false);
}

void Widget::setupWidget()
{
    single = startWin->isSingle();
    if(single) {
        if (startWin->isChannel(1)) {
            ui->groupBox_f1->setTitle("Канал 1");
            ui->groupBox_f1->show();
        }
        else ui->groupBox_f1->hide();

        if (startWin->isChannel(2)) {

            ui->groupBox_f2->setTitle("Канал 2");
            ui->groupBox_f2->show();
        }
        else ui->groupBox_f2->hide();

        if (startWin->isChannel(3)) {
            ui->groupBox_f3->setTitle("Канал 3");
            ui->groupBox_f3->show();
        }
        else ui->groupBox_f3->hide();

        if (startWin->isChannel(4)) {
            ui->groupBox_f4->setTitle("Канал 4");
            ui->groupBox_f4->show();
        }
        else ui->groupBox_f4->hide();
    }
    else {
        if (startWin->isChannel(1)) {
            ui->groupBox_f1->setTitle("Канал 1, 2");
            ui->groupBox_f2->hide();
        }
        else {
            ui->groupBox_f1->hide();
            ui->groupBox_f2->hide();
        }

        if (startWin->isChannel(3)) {
            ui->groupBox_f3->setTitle("Канал 3, 4");
            ui->groupBox_f4->hide();
        }
        else {
            ui->groupBox_f3->hide();
            ui->groupBox_f4->hide();
        }
    }
    setupRealtimeData(single);
}

//Widget::Widget(StartMeasurement *sw, QWidget *parent) : Widget(parent)
//{
//    startWin = sw;
//    setupWidget();
//}

//void Widget::setStartWindow(StartMeasurement *sw)
//{
//    startWin = sw;
//    setupWidget();
//}

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
        return QWidget::eventFilter(watched, event);
    }
//    if(event->type() == QEvent::KeyPress) {
//        qDebug() << "Event kayPress";
//        QKeyEvent *kayEvent = static_cast<QKeyEvent *>(event);
//        if(kayEvent->key() == Qt::Key_Enter) {
//            bool b = ui->groupBox_Mix->isVisible();
//            if(b) {
//                ui->groupBox_Mix->setVisible(false);
//                qDebug() << "setVisible(false)";
//            }
//            else {
//                ui->groupBox_Mix->setVisible(true);
//                qDebug() << "setVisible(true)";
//            }
//        }
//        return QWidget::eventFilter(watched, event);
//    }
    return QWidget::eventFilter(watched, event);
}

void Widget::setupRealtimeData(bool single) {
    if(single) {
        customPlot1 = ui->frame_1;
        ui->groupBox_f1->layout()->addWidget(pBar1);
        customPlot2 = ui->frame_2;
        ui->groupBox_f2->layout()->addWidget(pBar2);
        customPlot3 = ui->frame_3;
        ui->groupBox_f3->layout()->addWidget(pBar3);
        customPlot4 = ui->frame_4;
        ui->groupBox_f4->layout()->addWidget(pBar4);

        QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
        timeTicker->setTimeFormat("%m:%s");

        customPlot1->addGraph();
        customPlot1->graph(0)->setPen(QPen(QColor(10, 110, 40)));
        customPlot1->xAxis->setTicker(timeTicker);
        customPlot1->axisRect()->setupFullAxesBox();
        customPlot1->xAxis->setLabel("сек");
        customPlot1->yAxis2->setLabel("Вольт");
        customPlot1->yAxis->setRange(MIN, MAX);

        // make left and bottom axes transfer their ranges to right and top axes:
        connect(customPlot1->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot1->xAxis2, SLOT(setRange(QCPRange)));
        connect(customPlot1->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot1->yAxis2, SLOT(setRange(QCPRange)));

        customPlot2->addGraph();
        customPlot2->graph(0)->setPen(QPen(QColor(255, 110, 40)));
        customPlot2->xAxis->setTicker(timeTicker);
        customPlot2->axisRect()->setupFullAxesBox();
        customPlot2->xAxis->setLabel("сек");
        customPlot2->yAxis2->setLabel("Вольт");
        customPlot2->yAxis->setRange(MIN, MAX);

        connect(customPlot2->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot2->xAxis2, SLOT(setRange(QCPRange)));
        connect(customPlot2->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot2->yAxis2, SLOT(setRange(QCPRange)));

        customPlot3->addGraph();
        customPlot3->graph(0)->setPen(QPen(QColor(255, 110, 200)));
        customPlot3->xAxis->setTicker(timeTicker);
        customPlot3->axisRect()->setupFullAxesBox();
        customPlot3->xAxis->setLabel("сек");
        customPlot3->yAxis2->setLabel("Вольт");
        customPlot3->yAxis->setRange(MIN, MAX);

        connect(customPlot3->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot3->xAxis2, SLOT(setRange(QCPRange)));
        connect(customPlot3->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot3->yAxis2, SLOT(setRange(QCPRange)));

        customPlot4->addGraph();
        customPlot4->graph(0)->setPen(QPen(QColor(255, 200, 40)));
        customPlot4->xAxis->setTicker(timeTicker);
        customPlot4->axisRect()->setupFullAxesBox();
        customPlot4->xAxis->setLabel("сек");
        customPlot4->yAxis2->setLabel("Вольт");
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
        customPlot1 = ui->frame_1;
        ui->groupBox_f1->layout()->addWidget(pBar1);
        ui->groupBox_f1->layout()->addWidget(pBar2);
        customPlot2 = ui->frame_2;
        customPlot3 = ui->frame_3;
        ui->groupBox_f3->layout()->addWidget(pBar3);
        ui->groupBox_f3->layout()->addWidget(pBar4);
        customPlot4 = ui->frame_4;
        QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
        timeTicker->setTimeFormat("%m:%s");

        customPlot1->addGraph();
        customPlot1->graph(0)->setPen(QPen(QColor(10, 110, 40)));
        customPlot1->graph(1)->setPen(QPen(QColor(255, 110, 40)));
        customPlot1->xAxis->setTicker(timeTicker);
        customPlot1->axisRect()->setupFullAxesBox();
        customPlot1->xAxis->setLabel("сек");
        customPlot1->yAxis2->setLabel("Вольт");
        customPlot1->yAxis->setRange(MIN, MAX);

        // make left and bottom axes transfer their ranges to right and top axes:
        connect(customPlot1->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot1->xAxis2, SLOT(setRange(QCPRange)));
        connect(customPlot1->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot1->yAxis2, SLOT(setRange(QCPRange)));

        customPlot3->addGraph();
        customPlot3->graph(0)->setPen(QPen(QColor(255, 10, 200)));
        customPlot3->graph(1)->setPen(QPen(QColor(10, 100, 200)));
        customPlot3->xAxis->setTicker(timeTicker);
        customPlot3->axisRect()->setupFullAxesBox();
        customPlot3->xAxis->setLabel("сек");
        customPlot3->yAxis2->setLabel("Вольт");
        customPlot3->yAxis->setRange(MIN, MAX);

        connect(customPlot3->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot3->xAxis2, SLOT(setRange(QCPRange)));
        connect(customPlot3->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot3->yAxis2, SLOT(setRange(QCPRange)));
    }
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
    double dx1 = std::abs(a[0].toDouble() - lastPointV1);
    double dx2 = std::abs(a[1].toDouble() - lastPointV2);
    double dx3 = std::abs(a[2].toDouble() - lastPointV3);
    double dx4 = std::abs(a[3].toDouble() - lastPointV4);

    if((dx1 > START_DX || pulse1) && ready1) {
        pulse1 = false;
        ready1 = false;
        emit hasPulse1();
        setUserMessage("Канал 1: Введен стартовый реагент в кювету");
        qDebug() << QString("The pulse is come! dx1=%1").arg(dx1);
        getData(Channel1_ID, startWin->getTimeWrite());
    }
    lastPointV2 = a[1].toDouble();
    if((dx2 > START_DX || pulse2) && ready2) {
        pulse2 = false;
        ready2 = false;
        emit hasPulse2();
        setUserMessage("Канал 2: Введен стартовый реагент в кювету");
        qDebug() << QString("The pulse is come! dx2=%1").arg(dx2);
        getData(Channel2_ID, startWin->getTimeWrite());
    }
    lastPointV3 = a[2].toDouble();
    if((dx3 > START_DX || pulse3) && ready3) {
        pulse3 = false;
        ready3 = false;
        emit hasPulse3();
        setUserMessage("Канал 3: Введен стартовый реагент в кювету");
        qDebug() << QString("The pulse is come! dx3=%1").arg(dx3);
        getData(Channel3_ID, startWin->getTimeWrite());
    }
    lastPointV4 = a[3].toDouble();
    if((dx4 > START_DX || pulse4) && ready4) {
        pulse4 = false;
        ready4 = false;
        emit hasPulse4();
        setUserMessage("Канал 4: Введен стартовый реагент в кювету");
        qDebug() << QString("The pulse is come! dx4=%1").arg(dx4);
        getData(Channel4_ID, startWin->getTimeWrite());
    }

    if (key-lastPointKey > 0.01) {// at most add point every 10 ms
//        std::function<bool(void)> foo = [this](){
//            if(startWin == NULL) return true;
//            else return startWin->isSingle();
//        };
        if(single) {
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
          customPlot3->graph(0)->addData(key, a[2].toDouble());
          customPlot3->graph(1)->addData(key, a[3].toDouble());

          // make key axis range scroll with the data (at a constant range size of 8):
          customPlot1->xAxis->setRange(key, 8, Qt::AlignRight);
          customPlot1->replot();

//          customPlot2->xAxis->setRange(key, 8, Qt::AlignRight);
//          customPlot2->replot();

          customPlot3->xAxis->setRange(key, 8, Qt::AlignRight);
          customPlot3->replot();

//          customPlot4->xAxis->setRange(key, 8, Qt::AlignRight);
//          customPlot4->replot();
        }

        static double stop_dy1 = 0 ;
        if( data1 ) {
            map_y1.insert(key, a[0].toDouble());
            if( key <= (map_y1.begin().key() + 4) ) {
                    stop_dy1 = map_y1.last();
                    qDebug() << "STOP_DX1 = " << stop_dy1;
            }
            else {
                if(current_mode_id != TestAgr1_ID &&
                   current_mode_id != TestAgr2_ID &&
                   std::abs(map_y1.last() - stop_dy1) >= std::abs(stop_dy1*STOP_DX))
                {
                    qDebug() << "emit stopData1" << std::abs(map_y1.last() - stop_dy1) << ">=" << std::abs(stop_dy1*STOP_DX);
                    emit stopData(Channel1_ID);
                }
            }
        }
        else {
            stop_dy1 = 0;
        }

        static double stop_dy2 = 0 ;
        if( data2 ) {
            map_y2.insert(key, a[1].toDouble());
            if( key <= (map_y2.begin().key() + 4) ) {
                    stop_dy2 = map_y2.last();
                    qDebug() << "STOP_DX2 = " << stop_dy2;
            }
            else {
                if(current_mode_id != TestAgr1_ID &&
                   current_mode_id != TestAgr2_ID &&
                   std::abs(map_y2.last() - stop_dy2) >= std::abs(stop_dy2*STOP_DX) )
                {
                    qDebug() << "emit stopData2" << std::abs(map_y2.last() - stop_dy2) << ">=" << std::abs(stop_dy2*STOP_DX);
                    emit stopData(Channel2_ID);
                }
            }
        }
        else {
            stop_dy2 = 0;
        }

        static double stop_dy3 = 0 ;
        if( data3 ) {
            map_y3.insert(key, a[2].toDouble());
            if( key <= (map_y3.begin().key() + 4) ) {
                    stop_dy3 = map_y3.last();
                    qDebug() << "STOP_DX3 = " << stop_dy3;
            }
            else {
                if(current_mode_id != TestAgr1_ID &&
                   current_mode_id != TestAgr2_ID &&
                   std::abs(map_y3.last() - stop_dy3) >= std::abs(stop_dy3*STOP_DX) )
                {
                    qDebug() << "emit stopData3" << std::abs(map_y3.last() - stop_dy3) << ">=" << std::abs(stop_dy3*STOP_DX);
                    emit stopData(Channel3_ID);
                }
            }
        }
        else {
            stop_dy3 = 0;
        }

        static double stop_dy4 = 0 ;
        if( data4 ) {
            map_y4.insert(key, a[3].toDouble());
            if( key <= (map_y4.begin().key() + 4) ) {
                    stop_dy4 = map_y4.last();
                    qDebug() << "STOP_DX4 = " << stop_dy4;
            }
            else {
                if(current_mode_id != TestAgr1_ID &&
                   current_mode_id != TestAgr2_ID &&
                   std::abs(map_y4.last() - stop_dy4) >= std::abs(stop_dy4*STOP_DX) )
                {
                    qDebug() << "emit stopData4" << std::abs(map_y4.last() - stop_dy4) << ">=" << std::abs(stop_dy4*STOP_DX);
                    emit stopData(Channel4_ID);
                }
            }
        }
        else {
            stop_dy4 = 0;
        }
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
    case ChannelAll_ID:

        break;
    }
}

void Widget::onLazer(bool arg)
{
    if(arg) setUserMessage("Включение питания лазеров каждого из каналов");
    else setUserMessage("Выключение питания лазеров каждого из каналов");
    emit onlaser(arg);
}

void Widget::test()
{
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
}

void Widget::updataTermo(bool td)
{
    if(!td) {
        ui->label_TD->setText(QString("Температура >37°C"));
        ui->label_TD->setStyleSheet("color: green");
        termoSensor = !td;
    }
    else {
        ui->label_TD->setText(QString("Температура <37°C"));
        ui->label_TD->setStyleSheet("color: red");
        termoSensor = td;
    }
}

void Widget::getData(Channel_ID c, double time_s)
{
    QString str = QString("Канал %1: Измерение %2 (c)").arg(c).arg(time_s);
    setUserMessage(str);
    emit status(str);
    std::function<void (Channel_ID)> func = [this](Channel_ID c){
        stopData(c);
    };
    switch (c) {
    case Channel1_ID:
        pBar1->startProgress(QString("%1 %p%").arg(str), time_s * 1000, std::bind(func, c));
        data1 = true;
        break;
    case Channel2_ID:
        pBar2->startProgress(QString("%1 %p%").arg(str), time_s * 1000, std::bind(func, c));
        data2 = true;
        break;
    case Channel3_ID:
        pBar3->startProgress(QString("%1 %p%").arg(str), time_s * 1000, std::bind(func, c));
        data3 = true;
        break;
    case Channel4_ID:
        pBar4->startProgress(QString("%1 %p%").arg(str), time_s * 1000, std::bind(func, c));
        data4 = true;
        break;
    default:
        break;
    }
}

void Widget::stopData(Channel_ID c)
{
    if(!isData(ChannelAll_ID)) {qDebug() << "stop"; return; }
    switch (c) {
    case Channel1_ID:
        if(data1) {
            data1 = false;
            pulse1 = false;
            onMotor(c, false); //выключение перемешивания
            calcData(c);
            writeMapData(c);
        }
        break;
    case Channel2_ID:
        if(data2) {
            data2 = false;
            pulse2 = false;
            onMotor(c, false); //выключение перемешивания
            calcData(c);
            writeMapData(c);
        }
        break;
    case Channel3_ID:
        if(data3) {
            data3 = false;
            pulse3 = false;
            onMotor(c, false); //выключение перемешивания
            calcData(c);
            writeMapData(c);
        }
        break;
    case Channel4_ID:
        if(data4) {
            data4 = false;
            pulse4 = false;
            onMotor(c, false); //выключение перемешивания
            calcData(c);
            writeMapData(c);
        }
        break;
    default: qDebug() << "n is out of data from Widget::stopData(n)";
    }
}

bool Widget::isData(Channel_ID n)
{
    switch (n) {
    case ChannelAll_ID:
        return (data1 || data2 ||data3 || data4);
    case Channel1_ID:
        return data1;
    case Channel2_ID:
        return data2;
    case Channel3_ID:
        return data3;
    case Channel4_ID:
        return data4;
    default: qDebug() << "n is out of data from Widget::isData(n)";
    }
    return 0;
}

void Widget::startIncub(int num, double time_s, std::function<void(void)> timeout_fun, QString message)
{
    int time_ms = time_s * 1000;
    incub = true;
    if(num == 1) {
        setUserMessage(QString("Инкубация %1 (c)").arg(time_s));
        //int time_ms = startWin->getTimeIncube(1) * 1000;
        std::function<void(void)> call = [=, this](){
            this->incub = false;
            timeout_fun();
        };
        pBar1->startProgress(QString("Инкубация %1 (c) %p%").arg(time_s), time_ms, call);
        pBar2->startProgress(QString("Инкубация %1 (c) %p%").arg(time_s), time_ms);
        pBar3->startProgress(QString("Инкубация %1 (c) %p%").arg(time_s), time_ms);
        pBar4->startProgress(QString("Инкубация %1 (c) %p%").arg(time_s), time_ms);
        emit status(QString("Инкубация"));
    }
    else {
        QPointer<QMessageBox> imessageBox = new QMessageBox(this);
        imessageBox->setText(QString("<div style='color: blue'>Время инкубации истекло, добавьте разведения плазмы в рабочие каналы и нажмите кнопку \"ОК\"" ));
        connect(imessageBox.data(), &QMessageBox::buttonClicked, this, &Widget::incubeTimeout_1);
        int time_ms = startWin->getTimeIncube(1) * 1000;
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
    int time_ms = startWin->getTimeIncube(2) * 1000;
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
        //stopIncub();
        if(startWin->isChannel(1)) {
            setUserMessage("Канал 1: В ожидании добавления стартового реагента");
            ready1 = true;
            waitPulse = true;
            iw->addWaiter(1);
            pBar1->Wait();
        }
        if(startWin->isChannel(2)) {
            setUserMessage("Канал 2: В ожидании добавления стартового реагента");
            ready2 = true;
            waitPulse = true;
            iw->addWaiter(2);
            pBar2->Wait();
        }
        if(startWin->isChannel(3)) {
            setUserMessage("Канал 3: В ожидании добавления стартового реагента");
            ready3 = true;
            waitPulse = true;
            iw->addWaiter(3);
            pBar3->Wait();
        }
        if(startWin->isChannel(4)) {
            setUserMessage("Канал 4: В ожидании добавления стартового реагента");
            ready4 = true;
            iw->addWaiter(4);
            waitPulse = true;
            pBar4->Wait();
        }
        setUserMessage("<div style='color: blue'>В ожидании добавления стартового реагента");
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

        connect(iw, &ImpuleWaiter::alldone, [this](){ waitPulse = false; });
        iw->startWait();
}

double Widget::calcData(Channel_ID c)
{
    double retval;
    CalcData *p = CalcData::createCalc( current_mode_id );
    if(!p) { setUserMessage(QString("Ошибка при выделении памяти под класс CalcData")); return -1; }
    switch(c) {
    case Channel1_ID:
        if(!map_y1.isEmpty()) {
            retval = p->calc(map_y1);
            setUserMessage(QString("<div style='color: green'>Канал 1: %2 %1")
                           .arg(retval)
                           .arg(p->info()));
            emit ret_value1(retval);
        }
        else {
            setUserMessage(QString("Канал 1: Массив данных не заполнен!"));
            return -1;
        }
        break;
    case Channel2_ID:
        if(!map_y2.isEmpty()) {
            retval = p->calc(map_y2);
            setUserMessage(QString("<div style='color: green'>Канал 2: %2 %1")
                           .arg(retval)
                           .arg(p->info()));
            emit ret_value2(retval);
        }
        else {
            setUserMessage(QString("Канал 2: Массив данных не заполнен!"));
            return -1;
        }
        break;
    case Channel3_ID:
        if(!map_y3.isEmpty()) {
            retval = p->calc(map_y3);
            setUserMessage(QString("<div style='color: green'>Канал 3: %2 %1")
                           .arg(retval)
                           .arg(p->info()));
            emit ret_value3(retval);
        }
        else {
            setUserMessage(QString("Канал 3: Массив данных не заполнен!"));
            return -1;
        }
        break;
    case Channel4_ID:
        if(!map_y4.isEmpty()) {
            retval = p->calc(map_y4);
            setUserMessage(QString("<div style='color: green'>Канал 4: %2 %1")
                           .arg(retval)
                           .arg(p->info()));
            emit ret_value4(retval);
        }
        else {
            setUserMessage(QString("Канал 4: Массив данных не заполнен!"));
            return -1;
        }
        break;
    }
    delete p;
    return retval;
}

void Widget::writeMapData(Channel_ID c)
{
    ProgressTimerBar *pBar;
    CalcData *p = CalcData::createCalc( current_mode_id );
    if(p == NULL) { qDebug() << "CalcData is NULL"; return; }
    setUserMessage(QString("Канал %1: Запись данных").arg(c));
    emit status(QString("Канал %1: Запись данных").arg(c));

    QStringList strList;
    auto func = [&](QMap<double, double> map) {
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
    QString filename;
    switch (c) {
    case Channel1_ID:
        pBar = pBar1;
        strList << QString("V1#%1\t").arg(startWin->getNum(1));
        func(map_y1);
        map_y1.clear();
        filename = saveFiles.writeData(strList, pBar);
        setUserMessage(QString("Канал %1: %2").arg(c).arg(filename), true, true);
        break;
    case Channel2_ID:
        pBar = pBar2;
        strList << QString("V2#%1\t").arg(startWin->getNum(2));
        func(map_y2);
        map_y2.clear();
        filename = saveFiles.writeData(strList, pBar);
        setUserMessage(QString("Канал %1: %2").arg(c).arg(filename), true, true);
        break;
    case Channel3_ID:
        pBar = pBar3;
        strList << QString("V3#%1\t").arg(startWin->getNum(3));
        func(map_y3);
        map_y3.clear();
        filename = saveFiles.writeData(strList, pBar);
        setUserMessage(QString("Канал %1: %2").arg(c).arg(filename), true, true);
        break;
    case Channel4_ID:
        pBar = pBar4;
        strList << QString("V4#%1\t").arg(startWin->getNum(4));
        func(map_y4);
        map_y4.clear();
        filename = saveFiles.writeData(strList, pBar);
        setUserMessage(QString("Канал %1: %2").arg(c).arg(filename), true, true);
        break;
    default:
        break;
    }

    if (!isData(ChannelAll_ID) && !isIncub() && !isWaitPulse()) {
        ui->pushButton->setEnabled(true);
        setUserMessage(QString("Конец сбора данных"));
        status(QString("Конец сбора данных"));
        emit done();
    }
}

void Widget::showEvent(QShowEvent *event)
{
    single = startWin->isSingle();
    state = StateBuilder::getState(startWin->getModeID());
    setupWidget();
    event->accept();
}

void Widget::updateTime()
{
    //обновление времени на часах
    dt = QDateTime::currentDateTime();
    ui->label_time->setText("Время: " + dt.toString("hh:mm:ss"));
    ui->label_date->setText("Дата: " + dt.toString("dd.MM.yyyy"));
}

void Widget::setupTimers()
{
    //настройка таймера для часов
    connect(&currentTimer, QTimer::timeout, this, Widget::updateTime);
    currentTimer.start(300);
    dt = QDateTime::currentDateTime();
    setUserMessage(QString("Начало работы программы    Дата %1")
                   .arg(dt.toString("dd.MM.yyyy")));
}

void Widget::setUserMessage(QString str, bool withtime, bool tofile)
{
    if(withtime) {
        QString msg = QString(tr("%1, Время %2"))
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

void Widget::on_pushButton_clicked()
{

    ui->pushButton->setEnabled(false);

    if( termoSensor ) {
        setUserMessage(QString("<span style='color:red'>Дождитесь нагрева термостата</span>"));
        pBar1->setFormat("В ожидании");
        pBar1->setValue(0);
        pBar2->setFormat("В ожидании");

        pBar2->setValue(0);
        pBar3->setFormat("В ожидании");
        pBar3->setValue(0);
        pBar4->setFormat("В ожидании");
        pBar4->setValue(0);
    }
    else {
        setUserMessage("<span style='color:blue'>Термостат нагрет до 37ºC</span>");
        pBar1->setFormat("Готов");
        pBar1->setValue(pBar1->getMaximum());
        pBar2->setFormat("Готов");
        pBar2->setValue(pBar2->getMaximum());
        pBar3->setFormat("Готов");
        pBar3->setValue(pBar3->getMaximum());
        pBar4->setFormat("Готов");
        pBar4->setValue(pBar4->getMaximum());
    }

    QPointer<ImpuleWaiter> iw = new ImpuleWaiter;
    //state = StateBuilder::getState(startWin->getModeID());
    current_mode_id = state->current();
    QString msg_state = state->getMessage();

    switch(current_mode_id) {
    case Test_ID:
        test();
        break;
    case Level_ID:
        if(startWin->isChannel(1)) {
            onMotor(Channel1_ID, true); //включение перемешивания 1
            getData(Channel1_ID, startWin->getTimeWrite());
        }

        if(startWin->isChannel(2)) {
            onMotor(Channel2_ID, true); //включение перемешивания 2
            getData(Channel2_ID, startWin->getTimeWrite());
        }

        if(startWin->isChannel(3)) {
            onMotor(Channel3_ID, true); //включение перемешивания 1
            getData(Channel3_ID, startWin->getTimeWrite());
        }

        if(startWin->isChannel(4)) {
            onMotor(Channel4_ID, true); //включение перемешивания 4
            getData(Channel4_ID, startWin->getTimeWrite());
        }
        break;
    case TestAgr1_ID:
        waitImpulse(iw);
        setUserMessage(QString("<div style='color: blue'>Конец TestAgr1_ID"), 0);
        ui->pushButton->setEnabled(true);
        state->reset();
        break;
    case TestKo1_ID:
        ui->pushButton->setEnabled(false);
        setUserMessage(startWin->getStringStatus());
        if(startWin->isChannel(1)) onMotor(Channel1_ID, true); //включение перемешивания 1
        if(startWin->isChannel(2)) onMotor(Channel2_ID, true); //включение перемешивания 2
        if(startWin->isChannel(3)) onMotor(Channel3_ID, true); //включение перемешивания 3
        if(startWin->isChannel(4)) onMotor(Channel4_ID, true); //включение перемешивания 4
        startIncub(1, startWin->getTimeIncube(), [=, this](){ waitImpulse(iw);});
        ////connect(iw.data(), ImpuleWaiter::alldone, [](){});
        break;
    case TestKo2_ID:
        //QMessageBox::information(this, "", msg_state);
        ui->pushButton->setEnabled(false);
        setUserMessage(startWin->getStringStatus());
        startIncub(1, startWin->getTimeIncube(), [=, this](){ waitImpulse(iw);});
        break;
    case TestKo3_ID:
        ui->pushButton->setEnabled(false);
        setUserMessage(startWin->getStringStatus());
        startIncub(1, startWin->getTimeIncube(), [=, this](){ waitImpulse(iw);});
        break;
    case TestKo4_ID:
        ui->pushButton->setEnabled(false);
        setUserMessage(startWin->getStringStatus());
        startIncub(1, startWin->getTimeIncube(), [=, this](){ waitImpulse(iw);});
        break;
    case TestKo5_ID:
        ui->pushButton->setEnabled(false);
        setUserMessage(startWin->getStringStatus());
        startIncub(1, startWin->getTimeIncube(), [=, this](){ waitImpulse(iw);});
        break;
    case BTPTestAgr1_ID:
        setUserMessage(msg_state);
        //setUserMessage(startWin->getStringStatus());
        current_mode_id = Test_ID;
        connect(this, &Widget::done, [this](){
            current_mode_id = state->current(); ui->pushButton->setEnabled(true);
        });
        if (startWin->isChannel(1)) getData(Channel1_ID, 5);
        if (startWin->isChannel(2)) getData(Channel2_ID, 5);
        if (startWin->isChannel(3)) getData(Channel3_ID, 5);
        if (startWin->isChannel(4)) getData(Channel4_ID, 5);
        //state->next();
        break;
    case OTPTestAgr1_ID:
        setUserMessage(msg_state);
        setUserMessage(QString("<span style = 'color: red'>OTPTestAgr1_ID</span>"));
        //setUserMessage(QString("<div style='color: blue'>Установите пробы с ОТП в рабочие  каналы и нажмите \"Старт\""), 0);
        ui->pushButton->setEnabled(false);
        setUserMessage(startWin->getStringStatus());
        current_mode_id = Test_ID;
        connect(this, &Widget::done, [this](){
            current_mode_id = state->current(); ui->pushButton->setEnabled(true); });
        if (startWin->isChannel(1)) getData(Channel1_ID, 5);
        if (startWin->isChannel(2)) getData(Channel2_ID, 5);
        if (startWin->isChannel(3)) getData(Channel3_ID, 5);
        if (startWin->isChannel(4)) getData(Channel4_ID, 5);
        //state->next();
        break;
    case Incubation1_ID:
        setUserMessage(msg_state);
        QMessageBox::information(this, "", msg_state);
        //current_mode_id = state->next();
        startIncub(1, startWin->getTimeIncube(1), [this](){
            setUserMessage(QString("<span style = 'color: red'>Время инкубации истекло</span>"));
            on_pushButton_clicked();
        });
        break;
    case Incubation2_ID:
        break;

    case CalibKo2_ID:
//        connect(this, SIGNAL(ret_value1(double)), , SLOT(calibrationData1Come(double)));
//        connect(widget.data(), SIGNAL(ret_value2(double)), ko2.data(), SLOT(calibrationData2Come(double)));
//        connect(widget.data(), SIGNAL(ret_value3(double)), ko2.data(), SLOT(calibrationData3Come(double)));
//        connect(widget.data(), SIGNAL(ret_value4(double)), ko2.data(), SLOT(calibrationData4Come(double)));
        setUserMessage(msg_state);
        ui->pushButton->setEnabled(false);
        setUserMessage(startWin->getStringStatus());
        if(startWin->isChannel(1)) onMotor(Channel1_ID, true); //включение перемешивания 1
        if(startWin->isChannel(2)) onMotor(Channel2_ID, true); //включение перемешивания 2
        if(startWin->isChannel(3)) onMotor(Channel3_ID, true); //включение перемешивания 3
        if(startWin->isChannel(4)) onMotor(Channel4_ID, true); //включение перемешивания 4
        startIncub(1, startWin->getTimeIncube(), [=, this](){ waitImpulse(iw);});
        break;
    default:
        if(startWin->isChannel(1)) onMotor(Channel1_ID, true); //включение перемешивания 1
        if(startWin->isChannel(2)) onMotor(Channel2_ID, true); //включение перемешивания 2
        if(startWin->isChannel(3)) onMotor(Channel3_ID, true); //включение перемешивания 3
        if(startWin->isChannel(4)) onMotor(Channel4_ID, true); //включение перемешивания 4

        connect(startWin, &StartMeasurement::startMeasurment, [=](StartMeasurement* sm){
            startWin = sm;
            disconnect(startWin, &StartMeasurement::startMeasurment, 0, 0);
        });
        startWin->show();
        qDebug() << QString("called default startMeasurment()");
        break;
    } //end switch
    if(state->hasNext()) state->next();
}
