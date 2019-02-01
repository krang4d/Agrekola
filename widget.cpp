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

//#define Start_DX 0.1f
//#define MIN -6.0f
//#define MAX 6.0f

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    data1(false), data2(false), data3(false), data4(false),
    pulse1(false), pulse2(false), pulse3(false), pulse4(false),
    ready1(false), ready2(false), ready3(false), ready4(false),
    termoSensor(false), incub(false), waitPulse(false),
    pBar1(new ProgressTimerBar), pBar2(new ProgressTimerBar),
    pBar3(new ProgressTimerBar), pBar4(new ProgressTimerBar),
    Start_DX(0.1), Stop_DX(0.1), MIN(-6.0), MAX(6.0),
    startWin(new StartMeasurement)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("Программа сбора данных с АЦП(E-154) по 4 каналам");

    setupRealtimeData();
    setupTimers();
    installEventFilter(this);
}

Widget::Widget(StartMeasurement *sw, QWidget *parent) : Widget(parent)
{
    startWin = sw;
    setupWidget();
}

void Widget::setStartWindow(StartMeasurement *sw)
{
    startWin = sw;
    setupWidget();
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

void Widget::setupRealtimeData() {

    auto foo = [this]() { return startWin == NULL ? : startWin->isSingle(); };
    if(foo()) {
        customPlot1 = ui->frame_1;
        ui->groupBox_f1->layout()->addWidget(pBar1);
        customPlot2 = ui->frame_2;
        ui->groupBox_f2->layout()->addWidget(pBar2);
        customPlot3 = ui->frame_3;
        ui->groupBox_f3->layout()->addWidget(pBar3);
        customPlot4 = ui->frame_4;
        ui->groupBox_f4->layout()->addWidget(pBar4);
        ui->groupBox_Mix->setVisible(false);

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
        ui->groupBox_Mix->setVisible(false);
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
    if((dx1 > Start_DX || pulse1) && ready1) {
        pulse1 = false;
        ready1 = false;
        emit hasPulse1();
        setUserMessage("Канал 1: Введен стартовый реагент в кювету");
        qDebug() << QString("The pulse is come! dx1=%1").arg(dx1);
        getData(1);
    }
    lastPointV2 = a[1].toDouble();
    if((dx2 > Start_DX || pulse2) && ready2) {
        pulse2 = false;
        ready2 = false;
        emit hasPulse2();
        setUserMessage("Канал 2: Введен стартовый реагент в кювету");
        qDebug() << QString("The pulse is come! dx2=%1").arg(dx2);
        getData(2);
    }
    lastPointV3 = a[2].toDouble();
    if((dx3 > Start_DX || pulse3) && ready3) {
        pulse3 = false;
        ready3 = false;
        emit hasPulse3();
        setUserMessage("Канал 3: Введен стартовый реагент в кювету");
        qDebug() << QString("The pulse is come! dx3=%1").arg(dx3);
        getData(3);
    }
    lastPointV4 = a[3].toDouble();
    if((dx4 > Start_DX || pulse4) && ready4) {
        pulse4 = false;
        ready4 = false;
        emit hasPulse4();
        setUserMessage("Канал 4: Введен стартовый реагент в кювету");
        qDebug() << QString("The pulse is come! dx4=%1").arg(dx4);
        getData( 4 );
    }

    if (key-lastPointKey > 0.01) {// at most add point every 10 ms
        std::function<bool(void)> foo = [this](){ if(startWin == NULL) return true; else return startWin->isSingle();};
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
        if( isData( 1 ) && startWin->isChannel(1) ) {
            map_y1.insert(key, a[0].toDouble());
            if( key <= (map_y1.begin().key() + 4) ) {
                    stop_dy1 = map_y1.last();
                    qDebug() << "stop_dx1 = " << stop_dy1;
            }
            else {
                if(  getMode() != TestAgr1_ID && getMode() != TestAgr2_ID && std::abs(map_y1.last() - stop_dy1) >= std::abs(stop_dy1*Stop_DX) ) {
                    qDebug() << "emit stopData1" << std::abs(map_y1.last() - stop_dy1) << ">=" << std::abs(stop_dy1*Stop_DX);
                    emit stopData(1);
                }
            }
        }
        else {
            stop_dy1 = 0;
        }

        static double stop_dy2 = 0 ;
        if( isData( 2 ) && startWin->isChannel(2) ) {
            map_y2.insert(key, a[1].toDouble());
            if( key <= (map_y2.begin().key() + 4) ) {
                    stop_dy2 = map_y2.last();
                    qDebug() << "stop_dx2 = " << stop_dy2;
            }
            else {
                if(  getMode() != TestAgr1_ID && getMode() != TestAgr2_ID && std::abs(map_y2.last() - stop_dy2) >= std::abs(stop_dy2*Stop_DX) ) {
                    qDebug() << "emit stopData2" << std::abs(map_y2.last() - stop_dy2) << ">=" << std::abs(stop_dy2*Stop_DX);
                    emit stopData(2);
                }
            }
        }
        else {
            stop_dy2 = 0;
        }

        static double stop_dy3 = 0 ;
        if( isData( 3 ) && startWin->isChannel(3) ) {
            map_y3.insert(key, a[2].toDouble());
            if( key <= (map_y3.begin().key() + 4) ) {
                    stop_dy3 = map_y3.last();
                    qDebug() << "stop_dx3 = " << stop_dy3;
            }
            else {
                if(  getMode() != TestAgr1_ID && getMode() != TestAgr2_ID && std::abs(map_y3.last() - stop_dy3) >= std::abs(stop_dy3*Stop_DX) ) {
                    qDebug() << "emit stopData3" << std::abs(map_y3.last() - stop_dy3) << ">=" << std::abs(stop_dy3*Stop_DX);
                    emit stopData(3);
                }
            }
        }
        else {
            stop_dy3 = 0;
        }

        static double stop_dy4 = 0 ;
        if( isData( 4 ) && startWin->isChannel(4) ) {
            map_y4.insert(key, a[3].toDouble());
            if( key <= (map_y4.begin().key() + 4) ) {
                    stop_dy4 = map_y4.last();
                    qDebug() << "stop_dx4 = " << stop_dy4;
            }
            else {
                if(  getMode() != TestAgr1_ID && getMode() != TestAgr2_ID && std::abs(map_y4.last() - stop_dy4) >= std::abs(stop_dy4*Stop_DX) ) {
                    qDebug() << "emit stopData4" << std::abs(map_y4.last() - stop_dy4) << ">=" << std::abs(stop_dy4*Stop_DX);
                    emit stopData(4);
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

void Widget::on_checkBox_1_stateChanged(int arg1)
{
    if(arg1) setUserMessage("Канал 1: Включение двигателя магнитной мешалки");
    else setUserMessage("Канал 1: Выключение двигателя магнитной мешалки");
    emit onmixch1(arg1);
}

void Widget::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1) setUserMessage("Канал 2: Включение двигателя магнитной мешалки");
    else setUserMessage("Канал 2: Выключение двигателя магнитной мешалки");
    emit onmixch2(arg1);
}

void Widget::on_checkBox_3_stateChanged(int arg1)
{
    if(arg1) setUserMessage("Канал 3: Включение двигателя магнитной мешалки");
    else setUserMessage("Канал 3: Выключение двигателя магнитной мешалки");
    emit onmixch3(arg1);
}

void Widget::on_checkBox_4_stateChanged(int arg1)
{
    if(arg1) setUserMessage("Канал 4: Включение двигателя магнитной мешалки");
    else setUserMessage("Канал 4: Выключение двигателя магнитной мешалки");
    emit onmixch4(arg1);
}

void Widget::on_checkBox_PP_stateChanged(int arg1)
{
    if(arg1) setUserMessage("Канал РР: Включение двигателя магнитной мешалки");
    else setUserMessage("Канал РР: Выключение двигателя магнитной мешалки");
    emit onmixpp(arg1);
}

void Widget::on_checkBox_L_stateChanged(int arg1)
{
    if(arg1) setUserMessage("Включение питания лазеров каждого из каналов");
    else setUserMessage("Выключение питания лазеров каждого из каналов");
    emit onlaser(arg1);
}

void Widget::on_pushButton_clicked()
{
    static bool test = false;

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
    } else {
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
    QPointer<QMessageBox> test_dialog = new QMessageBox(this);
    //test_dialog->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    QPushButton ok;
    QPushButton cansel;
    ok.setText("Норма");
    cansel.setText("Брак");
    test_dialog->addButton(&ok, QMessageBox::AcceptRole);
    test_dialog->addButton(&cansel, QMessageBox::RejectRole);
    test_dialog->setIcon(QMessageBox::Information);
    switch(getMode()) {
    case Test_ID:
        setUserMessage("Проверка работопособности");
        test = true;
        QMessageBox::StandardButton button;
        //Проверка Перемешивания в канале 1
        emit onmixch1(true);
        setUserMessage(QString("Контроль включения перемешивания в канале 1"));
        test_dialog->setWindowTitle("Канал 1 - проверка");
        test_dialog->setText("Проконтролируте включение перемешивания в канале 1");
        test_dialog->exec();
        if(test_dialog->result() == 0) {
           emit onmixch1(false);
           setUserMessage("Перемешивания в канале 1 - <span style='color:blue'>НОРМА</span>");
        }
        else {
           setUserMessage(QString("Перемешивания в канале 1 - <span style='color:red'>БРАК</span>"));
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
          setUserMessage("Перемешивания в канале 2 - <span style='color:blue'>НОРМА</span>");
        }
        else {
            setUserMessage(QString("Перемешивания в канале 2 - <span style='color:red'>БРАК</span>"));
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
         setUserMessage("Перемешивания в канале 3 - <span style='color:blue'>НОРМА</span>");
        }
        else {
            setUserMessage(QString("Перемешивания в канале 3 - <span style='color:red'>БРАК</span>"));
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
            setUserMessage("Перемешивания в канале 4 - <span style='color:blue'>НОРМА</span>");
        }
        else {
            setUserMessage(QString("Перемешивания в канале 4 - <span style='color:red'>БРАК</span>"));
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
            setUserMessage("Перемешивания в канале РР - <span style='color:blue'>НОРМА</span>");
        }
        else {
            setUserMessage(QString("Перемешивания в канале РР - <span style='color:red'>БРАК</span>"));
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
        break;
    case Level_ID:
        if(startWin->isChannel(1)) ui->checkBox_1->setChecked(true); //включение перемешивания 1
        else ui->checkBox_1->setChecked(false);

        if(startWin->isChannel(2)) ui->checkBox_2->setChecked(true); //включение перемешивания 2
        else ui->checkBox_2->setChecked(false);

        if(startWin->isChannel(3)) ui->checkBox_3->setChecked(true); //включение перемешивания 3
        else ui->checkBox_3->setChecked(false);

        if(startWin->isChannel(4)) ui->checkBox_4->setChecked(true); //включение перемешивания 4
        else ui->checkBox_4->setChecked(false);

        if(test) {
            connect(startWin, &StartMeasurement::startMeasurment, [=](StartMeasurement* sm){
                setStartWindow(sm);
                getData(1);
                getData(2);
                getData(3);
                getData(4);
                disconnect(startWin, &StartMeasurement::startMeasurment, 0, 0);
                startWin->hide();
                });
            startWin->show();
        } else {
            getData(1);
            getData(2);
            getData(3);
            getData(4);
        }
        break;
    case TestAgr1_ID:
        ui->pushButton->setEnabled(false);
        setUserMessage(startWin->getStringStatus());
        startIncub(2);
        break;

    case TestKo1_ID:
        ui->pushButton->setEnabled(false);
        setUserMessage(startWin->getStringStatus());
        startIncub(1);
        break;

    case TestKo2_ID:
        ui->pushButton->setEnabled(false);
        setUserMessage(startWin->getStringStatus());
        startIncub(1);
        break;

    case TestKo3_ID:
        ui->pushButton->setEnabled(false);
        setUserMessage(startWin->getStringStatus());
        startIncub(1);
        break;

    case TestKo4_ID:
        ui->pushButton->setEnabled(false);
        setUserMessage(startWin->getStringStatus());
        startIncub(1);
        break;

    case TestKo5_ID:
        ui->pushButton->setEnabled(false);
        setUserMessage(startWin->getStringStatus());
        startIncub(1);
        break;

    default:
        if(startWin->isChannel(1)) ui->checkBox_1->setChecked(true); //включение перемешивания 1
        else ui->checkBox_1->setChecked(false);

        if(startWin->isChannel(2)) ui->checkBox_2->setChecked(true); //включение перемешивания 2
        else ui->checkBox_2->setChecked(false);

        if(startWin->isChannel(3)) ui->checkBox_3->setChecked(true); //включение перемешивания 3
        else ui->checkBox_3->setChecked(false);

        if(startWin->isChannel(4)) ui->checkBox_4->setChecked(true); //включение перемешивания 4
        else ui->checkBox_4->setChecked(false);
        connect(startWin, &StartMeasurement::startMeasurment, [=](StartMeasurement* sm){
            startMeasurment(sm);
            disconnect(startWin, &StartMeasurement::startMeasurment, 0, 0);
        });
        startWin->show();
        qDebug() << QString("called default startMeasurment()");
        break;
    } //end switch(getMode())
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

//void Widget::startMeasurment()
//{
//    //qDebug() << "Widget::startMeasurment() start pressed";
//    //ui->pushButton->setEnabled(false);
//    setUserMessage(startWin->getStringStatus());
//    setupWidget();
//    if( getMode() == TestAgr1_ID ||getMode() == TestAgr2_ID ) {
//        startIncub(2);
//    }
//    else startIncub(1);
//}

void Widget::startMeasurment(StartMeasurement *s)
{
    startWin  = s;
    on_pushButton_clicked();
}

void Widget::getLevelBTP()
{
    //определение БТП
    setMode(Level_ID);
    setStartWindow(StartCalibrationAgr1::getBTP());
    setUserMessage(QString("<div style='color: blue'>Установите пробы с БТП в рабочие  каналы и нажмите \"Старт\""), 0);

    auto savebtp2 = [&](int n, double d) {
//        static int i = 0;
//        i++;
        QStringList btp100;
        SaveFiles file_btp;
        qDebug() << QString("retavlue = %1, index = %2").arg(d).arg(n);
        file_btp.openBTP100(btp100);
        if (btp100.isEmpty() || btp100.count() != 4) {
            btp100 = QStringList({"0", "0", "0", "0"});
        }
        btp100.replace(n, QString("%1").arg(d));
        file_btp.saveBTP100(btp100);
//        if(i == startWin->num) {
//            i = 0;
//            emit btp_done();
//        }
    };

    connect(this, &Widget::ret_value1, [&](double x){ disconnect(this, &Widget::ret_value1, 0, 0);
            savebtp2(0, x); } );
    connect(this, &Widget::ret_value2, [&](double x){ disconnect(this, &Widget::ret_value2, 0, 0);
            savebtp2(1, x); } );
    connect(this, &Widget::ret_value3, [&](double x){ disconnect(this, &Widget::ret_value3, 0, 0);
            savebtp2(2, x); } );
    connect(this, &Widget::ret_value4, [&](double x){ disconnect(this, &Widget::ret_value4, 0, 0);
            savebtp2(3, x); } );
}

void Widget::getLevelOTP()
{
    //определение ОТП
    setMode(Level_ID);
    setStartWindow(StartCalibrationAgr1::getOTP());
    setUserMessage(QString("<div style='color: blue'>Установите пробы с ОТП в рабочие  каналы и нажмите \"Старт\""), 0);

    auto saveotp2 = [&](int n, double d) {
//        static int i = 0;
//        i++;
            QStringList otp0;
            SaveFiles file_otp;
            qDebug() << QString("retavlue = %1, index = %2").arg(d).arg(n);
            file_otp.openBTP0(otp0);
            if (otp0.isEmpty() || otp0.count() != 4) {
                otp0 = QStringList({"0", "0", "0", "0"});
            }
            otp0.replace(n, QString("%1").arg(d));
            file_otp.saveBTP0(otp0);
        qDebug() << "Определение ОТП контрольной плазмы";
//        if(i == startWin->num) {
//            i = 0;
//            emit otp_done();
//        }
    };

    connect(this, &Widget::ret_value1, [&](double x){ disconnect(this, &Widget::ret_value1, 0, 0);
            saveotp2(0, x); } );
    connect(this, &Widget::ret_value2, [&](double x){ disconnect(this, &Widget::ret_value2, 0, 0);
            saveotp2(1, x); } );
    connect(this, &Widget::ret_value3, [&](double x){ disconnect(this, &Widget::ret_value3, 0, 0);
            saveotp2(2, x); } );
    connect(this, &Widget::ret_value4, [&](double x){ disconnect(this, &Widget::ret_value4, 0, 0);
            saveotp2(3, x); } );
}

void Widget::getData(int n)
{
    QString str = QString("Канал %1: Измерение").arg(n);
    setUserMessage(str);
    emit status(str);
    std::function<void (int)> func = [this](int n){
        stopData(n);
    };
    switch (n) {
    case 1:
        pBar1->startProgress(QString("%1 %p%").arg(str), startWin->getTime() * 1000, std::bind(func, n));
        data1 = true;
        break;
    case 2:
        pBar2->startProgress(QString("%1 %p%").arg(str), startWin->getTime() * 1000, std::bind(func, n));
        data2 = true;
        break;
    case 3:
        pBar3->startProgress(QString("%1 %p%").arg(str), startWin->getTime() * 1000, std::bind(func, n));
        data3 = true;
        break;
    case 4:
        pBar4->startProgress(QString("%1 %p%").arg(str), startWin->getTime() * 1000, std::bind(func, n));
        data4 = true;
        break;
    default:
        break;
    }
}

void Widget::stopData(int n)
{
    if(!isData()) {qDebug() << "stop"; return; }
    switch (n) {
    case 1:
        if(data1) {
            data1 = false;
            pulse1 = false;
            ui->checkBox_1->setChecked(false); //включение перемешивания
            writeMapData( 1 );
        }
        break;
    case 2:
        if(data2) {
            data2 = false;
            pulse2 = false;
            ui->checkBox_2->setChecked(false);
            writeMapData( 2 );
        }
        break;
    case 3:
        if(data3) {
            data3 = false;
            pulse3 = false;
            ui->checkBox_3->setChecked(false);
            writeMapData( 3 );
        }
        break;
    case 4:
        if(data4) {
            data4 = false;
            pulse4 = false;
            ui->checkBox_4->setChecked(false);
            writeMapData( 4 );
        }
        break;
    default: qDebug() << "n is out of data from Widget::stopData(n)";
    }
}

bool Widget::isData(int n)
{
    switch (n) {
    case 0:
        return (data1 || data2 ||data3 || data4);
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
    if(num == 1) {
        setUserMessage(QString("Инкубация (%1c)").arg(startWin->getTimeIncube()));
        int time_ms = startWin->getTimeIncube(1) * 1000;
        pBar1->startProgress(QString("Инкубация %p%"), time_ms, [this](){ incubeTimeout(); });
        pBar2->startProgress(QString("Инкубация %p%"), time_ms);
        pBar3->startProgress(QString("Инкубация %p%"), time_ms);
        pBar4->startProgress(QString("Инкубация %p%"), time_ms);

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

void Widget::incubeTimeout()
{
        QPointer<ImpuleWaiter> iw = new ImpuleWaiter;

        stopIncub();
        if(startWin->isChannel(1)) {
            setUserMessage("Канал 1: В ожидании введения стартового реагента");
            ready1 = true;
            waitPulse = true;
            iw->addWaiter(1);
            pBar1->Wait();
        }
        if(startWin->isChannel(2)) {
            setUserMessage("Канал 2: В ожидании введения стартового реагента");
            ready2 = true;
            waitPulse = true;
            iw->addWaiter(2);
            pBar2->Wait();
        }
        if(startWin->isChannel(3)) {
            setUserMessage("Канал 3: В ожидании введения стартового реагента");
            ready3 = true;
            waitPulse = true;
            iw->addWaiter(3);
            pBar3->Wait();
        }
        if(startWin->isChannel(4)) {
            setUserMessage("Канал 4: В ожидании введения стартового реагента");
            ready4 = true;
            iw->addWaiter(4);
            waitPulse = true;
            pBar4->Wait();
        }
        setUserMessage("<div style='color: blue'>Время инкубации истекло, добавьте стартовый реагент");
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
    incubeTimeout();
}

double Widget::writeMapData(int n)
{
    double retval;
    CalcData *p = CalcData::createCalc( getMode() );
    if(p == NULL) { qDebug() << "p is NULL"; }
    setUserMessage(QString("Канал %1: Запись данных").arg(n));
    emit status(QString("Канал %1: Запись данных").arg(n));

    ProgressTimerBar *pBar;
    switch (n) {
    case 1:
        pBar = pBar1;
        break;
    case 2:
        pBar = pBar2;
        break;
    case 3:
        pBar = pBar3;
        break;
    case 4:
        pBar = pBar4;
        break;
    default:
        break;
    }
    qDebug().noquote() << QString("Канал %1: Запись данных").arg(n);

    QStringList strList;
    auto func = [&](QMap<double, double> map) {
        strList << QString("t#%5\tti#%6\tp#%7\n").arg(startWin->getTime())
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
    if( n == 1 && !map_y1.isEmpty() ) {
        retval = p->calc(map_y1);
        setUserMessage(QString("<div style='color: green'>Канал 1: %2 %1")
                       .arg(retval)
                       .arg(p->info()));
        strList << QString("V1#%1\t").arg(startWin->getNum(1));
        func(map_y1);
        map_y1.clear();
        emit ret_value1(retval);
    }
    if( n == 2 && !map_y2.isEmpty() ) {
        retval = p->calc(map_y2);
        setUserMessage(QString("<div style='color: green'>Канал 2: %2 %1")
                       .arg(retval)
                       .arg(p->info()));
        strList << QString("V2#%1\t").arg(startWin->getNum(2));
        func(map_y2);
        map_y2.clear();
        emit ret_value2(retval);
    }
    if( n == 3 && !map_y3.isEmpty() ) {
        retval = p->calc(map_y3);
        setUserMessage(QString("<div style='color: green'>Канал 3: %2 %1")
                       .arg(retval)
                       .arg(p->info()));
        strList << QString("V3#%1\t").arg(startWin->getNum(3));
        func(map_y3);
        map_y3.clear();
        emit ret_value3(retval);
    }
    if( n == 4 && !map_y4.isEmpty() ) {
        retval = p->calc(map_y4);
        setUserMessage(QString("<div style='color: green'>Канал 4: %2 %1")
                       .arg(retval)
                       .arg(p->info()));
        strList << QString("V4#%1\t").arg(startWin->getNum(4));
        func(map_y4);
        map_y4.clear();
        emit ret_value4(retval);
    }
    QString filename = saveFiles.writeData(strList, pBar);
    setUserMessage(filename, true, true);
    //std::function<QString(void)> f1= [=](){return SaveFiles::writeData(strList);};
    //std::function<QString(void)> foo = func();
    //QFuture<QString> result = QtConcurrent::run(f1);
    //QString filename = result.result();

    if (!isData() && !isIncub() && !isWaitPulse()) {
        ui->checkBox_L->setChecked(false);
        ui->pushButton->setEnabled(true);
        setUserMessage(QString("Конец сбора данных"));
        emit done();
    }
    return retval;
}

void Widget::on_comboBox_currentIndexChanged(int index)
{
    QString str;
    switch (index) {
    case 0:
        str = tr("Тест (Test 0)");
        setMode(Test_ID);
        break;
    case 1:
        str = tr("Определение параметров агрегации, тест (Agr1 1)");
        setMode(TestAgr1_ID);
        break;
    case 2:
        str = tr("Определение активности фактора Виллебранда, тест (Agr2 2)");
        setMode(TestAgr2_ID);
        break;
    case 3:
        str = tr("Время свертывания, тест (Ko1 3)");
        setMode(TestKo1_ID);
        break;
    case 4:
        str = tr("АЧТВ, тест (Ko2 4)");
        setMode(TestKo2_ID);
        break;
    case 5:
        str = tr("Фибриноген, тест (Ko3 5)");
        setMode(TestKo3_ID);
        break;
    case 6:
        str = tr("Тромбин, тест (Ko4 6)");
        setMode(TestKo4_ID);
        break;
    case 7:
        str = tr("Протромбиновый комплекс, тест (Ko5 7)");
        setMode(TestKo5_ID);
        break;
    case 8:
        str = tr("Определение уровня БТП, тест (8)");
        setStartWindow(StartCalibrationAgr1::getBTP());
        setMode(Level_ID);
        break;
    case 9:
        str = tr("Определение уровня ОТП, тест (9)");
        setStartWindow(StartCalibrationAgr1::getOTP());
        setMode(Level_ID);
        break;
    default:
        break;
    }
    setUserMessage(str, 0);
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

void Widget::setupTimers()
{
    //настройка таймера для часов
    connect(&currentTimer, &QTimer::timeout, [this](){ updateTime();});
    currentTimer.start(300);
    dt = QDateTime::currentDateTime();
    setUserMessage(QString("Начало работы программы    Дата %1")
                   .arg(dt.toString("dd.MM.yyyy")));
}

void Widget::setupWidget()
{
    if(!startWin->isCancel()) {
        if(startWin->isSingle()) {
            if (startWin->isChannel(1)) {
                ui->groupBox_f1->setTitle("Канал 1");
                ui->groupBox_f1->show();
            }
            else {
                ui->groupBox_f1->hide();
            }

            if (startWin->isChannel(2)) {

                ui->groupBox_f2->setTitle("Канал 2");
                ui->groupBox_f2->show();
            }
            else {
                ui->groupBox_f2->hide();
            }

            if (startWin->isChannel(3)) {

                ui->groupBox_f3->setTitle("Канал 3");
                ui->groupBox_f3->show();
            }
            else {
                ui->groupBox_f3->hide();
            }

            if (startWin->isChannel(4)) {

                ui->groupBox_f4->setTitle("Канал 4");
                ui->groupBox_f4->show();
            }
            else {
                ui->groupBox_f4->hide();
            }
            //setUserMessage(startWin->getStringStatus());
            ui->checkBox_L->setChecked(true); //включение лазеров
            setupRealtimeData();
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
            setupRealtimeData();
        }
    }
}

//DoThis::DoThis(Widget *obj)
//{
//    this->obj = obj;
//    self = NULL;
//}

//Incubation::Incubation(Widget *obj) : DoThis(obj)
//{

//}

