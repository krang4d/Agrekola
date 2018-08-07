#include "widget.h"
#include "ui_widget.h"

#include <QScrollBar>
#include <QMessageBox>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QtConcurrent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    startWin(new StartMeasurment),
    data1(false),
    data2(false),
    data3(false),
    data4(false),
    incub(false),
    pulse1(false),
    pulse2(false),
    pulse3(false),
    pulse4(false)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("Программы сбора данных с АЦП(E-154) по 4 каналам");
    customPlot1 = ui->frame_1;
    customPlot2 = ui->frame_2;
    customPlot3 = ui->frame_3;
    customPlot4 = ui->frame_4;
    ui->groupBox_Mix->setVisible(false);
    ui->progressBar->hide();
    setupRealtimeData();
    setupTimers();

    installEventFilter(this);
    QWidget::connect(startWin, SIGNAL(startMeasurment()), this, SLOT(getData()));
}

Widget::~Widget()
{
    emit stop();
    delete startWin;
    delete ui;
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::Close)
    {
        qDebug() << "Close Event is emited in the Widget!";
        parentWidget()->show();
        return true;
    }
    if(event->type() == QEvent::KeyPress)
    {
        qDebug() << "Event kayPress";
        QKeyEvent *kayEvent = static_cast<QKeyEvent *>(event);
        if(kayEvent->key() == Qt::Key_Enter)
        {
            bool b = ui->groupBox_Mix->isVisible();
            if(b)
            {
                ui->groupBox_Mix->setVisible(false);
                qDebug() << "setVisible(false)";
            }
            else
            {
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
    if(withtime)
    {
        QString msg = QString(tr("%1,    Время %2"))
                .arg(str)
                .arg(dt.toString("hh:mm:ss"));
        ui->textEdit->append(msg);
        if(tofile) saveFiles.writeUserMsg(msg);
    }
    else
    {
        ui->textEdit->append(str);
        if(tofile) saveFiles.writeUserMsg(str);
    }
    QScrollBar *b = ui->textEdit->verticalScrollBar();
    b->triggerAction(QScrollBar::SliderToMaximum);
}

void Widget::setTestMode(bool b)
{
    //setUserMessage(QString(agrekola->GetInformation()), false);
    ui->groupBox_Mix->setVisible(b);
}

void Widget::setupRealtimeData()
{
    // include this section to fully disable antialiasing for higher performance:
    /*
    QFont font;
    font.setStyleStrategy(QFont::NoAntialias);

    customPlot1->setNotAntialiasedElements(QCP::aeAll);
    customPlot1->xAxis->setTickLabelFont(font);
    customPlot1->yAxis->setTickLabelFont(font);
    customPlot1->legend->setFont(font);

    customPlot2->setNotAntialiasedElements(QCP::aeAll);
    customPlot2->xAxis->setTickLabelFont(font);
    customPlot2->yAxis->setTickLabelFont(font);
    customPlot2->legend->setFont(font);

    customPlot3->setNotAntialiasedElements(QCP::aeAll);
    customPlot3->xAxis->setTickLabelFont(font);
    customPlot3->yAxis->setTickLabelFont(font);
    customPlot3->legend->setFont(font);

    customPlot4->setNotAntialiasedElements(QCP::aeAll);
    customPlot4->xAxis->setTickLabelFont(font);
    customPlot4->yAxis->setTickLabelFont(font);
    customPlot4->legend->setFont(font);
    */
    //customPlot1->setOpenGl(true);
    //customPlot2->setOpenGl(true);
    //customPlot3->setOpenGl(true);
    //customPlot4->setOpenGl(true);
    if(startWin->isSingle())
    {
        QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
        timeTicker->setTimeFormat("%m:%s");

        customPlot1->addGraph();
        customPlot1->graph(0)->setPen(QPen(QColor(10, 110, 40)));
        customPlot1->xAxis->setTicker(timeTicker);
        customPlot1->axisRect()->setupFullAxesBox();
        customPlot1->xAxis->setLabel("t, сек");
        customPlot1->yAxis->setLabel("V1, Вольт");
        customPlot1->yAxis->setRange(-5.5, 5.5);

        // make left and bottom axes transfer their ranges to right and top axes:
        connect(customPlot1->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot1->xAxis2, SLOT(setRange(QCPRange)));
        connect(customPlot1->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot1->yAxis2, SLOT(setRange(QCPRange)));

        customPlot2->addGraph();
        customPlot2->graph(0)->setPen(QPen(QColor(255, 110, 40)));
        customPlot2->xAxis->setTicker(timeTicker);
        customPlot2->axisRect()->setupFullAxesBox();
        customPlot2->xAxis->setLabel("t, сек");
        customPlot2->yAxis->setLabel("V2, Вотльт");
        customPlot2->yAxis->setRange(-5.5, 5.5);

        connect(customPlot2->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot2->xAxis2, SLOT(setRange(QCPRange)));
        connect(customPlot2->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot2->yAxis2, SLOT(setRange(QCPRange)));

        customPlot3->addGraph();
        customPlot3->graph(0)->setPen(QPen(QColor(255, 110, 200)));
        customPlot3->xAxis->setTicker(timeTicker);
        customPlot3->axisRect()->setupFullAxesBox();
        customPlot3->xAxis->setLabel("t, сек");
        customPlot3->yAxis->setLabel("V3, Вотльт");
        customPlot3->yAxis->setRange(-5.5, 5.5);

        connect(customPlot3->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot3->xAxis2, SLOT(setRange(QCPRange)));
        connect(customPlot3->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot3->yAxis2, SLOT(setRange(QCPRange)));

        customPlot4->addGraph();
        customPlot4->graph(0)->setPen(QPen(QColor(255, 200, 40)));
        customPlot4->xAxis->setTicker(timeTicker);
        customPlot4->axisRect()->setupFullAxesBox();
        customPlot4->xAxis->setLabel("t, сек");
        customPlot4->yAxis->setLabel("V4, Вотльт");
        customPlot4->yAxis->setRange(-5.5, 5.5);

        connect(customPlot4->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot4->xAxis2, SLOT(setRange(QCPRange)));
        connect(customPlot4->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot4->yAxis2, SLOT(setRange(QCPRange)));

//        // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
//        disconnect(&plotTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlotDuo()));
//        plotTimer.stop();
//        connect(&plotTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlotSingle()));
//        plotTimer.start(0); // Interval 0 means to refresh as fast as possible
    }
    else
    {
        QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
        timeTicker->setTimeFormat("%m:%s");

        customPlot1->addGraph();
        customPlot1->graph(0)->setPen(QPen(QColor(10, 110, 40)));
        customPlot1->graph(1)->setPen(QPen(QColor(255, 110, 40)));
        customPlot1->xAxis->setTicker(timeTicker);
        customPlot1->axisRect()->setupFullAxesBox();
        customPlot1->xAxis->setLabel("Время, с");
        customPlot1->yAxis->setLabel("Напряжение, В");
        customPlot1->yAxis->setRange(-5.5, 5.5);

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
        customPlot2->yAxis->setRange(-5.5, 5.5);

        connect(customPlot2->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot2->xAxis2, SLOT(setRange(QCPRange)));
        connect(customPlot2->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot2->yAxis2, SLOT(setRange(QCPRange)));

//        // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
//        disconnect(&plotTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlotSingle()));
//        plotTimer.stop();
//        connect(&plotTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlotDuo()));
//        plotTimer.start(0); // Interval 0 means to refresh as fast as possible
    }
}

void Widget::startProgressBarTimer(QString format, int timer_tic_ms, int time_ms)
{
    ui->progressBar->setFormat(format);
    ui->progressBar->setVisible(true);
    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(time_ms);
    progressTimer.start(timer_tic_ms);
}

void Widget::updateProgressValue()
{
    //ui->progressBar->setMaximum(progress_t-progressTimer.interval());
    int value = ui->progressBar->value();
    ui->progressBar->setValue(value+progressTimer.interval());
}

void Widget::realtimeDataSlot(QVariantList a)
{
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
    if( dx1 > 0.2f && pulse1) {
        pulse1 = false;
        qDebug() << QString("The pulse is come! da1=%1").arg(dx1);
        startData(1);
    }
    lastPointV2 = a[1].toDouble();
    if( dx2 > 0.2f && pulse2) {
        pulse2 = false;
        qDebug() << QString("The pulse is come! da2=%1").arg(dx2);
        startData(2);
    }
    lastPointV3 = a[2].toDouble();
    if( dx3 > 0.2f && pulse3) {
        pulse3 = false;
        qDebug() << QString("The pulse is come! da3=%1").arg(dx3);
        startData(3);
    }
    lastPointV4 = a[3].toDouble();
    if( dx4 > 0.2f && pulse4) {
        pulse4 = false;
        qDebug() << QString("The pulse is come! da4=%1").arg(dx4);
        startData(4);
    }

    if (key-lastPointKey > 0.01) // at most add point every 10 ms
    {
        if(startWin->isSingle()){
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
        else{
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
                y1.push_back(a[0].toDouble());
                //y1.insert(key, a[0].toDouble());
            }
        }
        if(isData(2)) {
            if(startWin->isChannel_2()) {
                map_y2.insert(key, a[1].toDouble());
                y2.push_back(a[1].toDouble());
            }
        }
        if(isData(3)) {
            if(startWin->isChannel_3()) {
                map_y3.insert(key, a[2].toDouble());
                y3.push_back(a[2].toDouble());
            }
        }
        if(isData(4)) {
            if(startWin->isChannel_4()) {
                map_y4.insert(key, a[3].toDouble());
                y4.push_back(a[3].toDouble());
            }
        }
        if(isData(1) || isData(2) || isData(3) || isData(4))
            x.push_back(key);
        lastPointKey = key;
    }
    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) {// average fps over 2 seconds
        ui->label_fps->setText(QString("%1 FPS, Total Data points: %2")
                        .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
                        .arg(customPlot1->graph(0)->data()->size()+customPlot2->graph(0)->data()->size() + customPlot3->graph(0)->data()->size() + customPlot4->graph(0)->data()->size()));
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
    startWin->show();
}

void Widget::updataTermo(bool td)
{
    if(!td)
    {
        ui->label_TD->setText(QString("Температура >37°C"));
        ui->label_TD->setStyleSheet("color: green");
    }
    else
    {
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
    else{
        ui->label_incube->setText(QString("Время инкубации, --- сек"));
        t=0;
    }
}

void Widget::getData()
{
    QString msg;
    if(!startWin->isCancel())
    {
        if(startWin->isSingle())
        {
            ui->groupBox_f1->setTitle("Канал 1");
            ui->groupBox_f2->setTitle("Канал 2");
            ui->groupBox_f3->setTitle("Канал 3");
            ui->groupBox_f4->setTitle("Канал 4");
            if(startWin->isChannel_1()) ui->groupBox_f1->show();
            else ui->groupBox_f1->hide();
            if(startWin->isChannel_2()) ui->groupBox_f2->show();
            else ui->groupBox_f2->hide();
            if(startWin->isChannel_3()) ui->groupBox_f3->show();
            else ui->groupBox_f3->hide();
            if(startWin->isChannel_4()) ui->groupBox_f4->show();
            else ui->groupBox_f4->hide();

            if (startWin->isChannel_1()) {msg += QString("№1 = %1, ").arg(startWin->getNum_1());}
            else msg += QString("№1 - выкл., ");

            if (startWin->isChannel_2()) {msg += QString("№2 = %1, ").arg(startWin->getNum_2());}
            else msg += QString("№2 - выкл., ");

            if (startWin->isChannel_3()) {msg += QString("№3 = %1, ").arg(startWin->getNum_3());}
            else msg += QString("№3 - выкл., ");

            if (startWin->isChannel_4()) {msg += QString("№4 = %1 ").arg(startWin->getNum_4());}
            else msg += QString("№4 - выкл. ");

            msg = QString("Начало сбора данных, одиночные пробы (t = %1c, %2)").arg(startWin->getTime()).arg(msg);
            setUserMessage(msg, true, true);
            setupRealtimeData();
        }
        else
        {
            ui->groupBox_f1->setTitle("Канал 1, 2");
            ui->groupBox_f2->setTitle("Канал 3, 4");
            ui->groupBox_f3->hide();
            ui->groupBox_f4->hide();

            if (startWin->isChannel_1()) {msg += QString("№1, 2 = %1, ").arg(startWin->getNum_1());}
            else msg += QString("№1, 2 - выкл., ");

            if (startWin->isChannel_3()) {msg += QString("№3, 4 = %1, ").arg(startWin->getNum_3());}
            else msg += QString("№3, 4 - выкл., ");

            msg = QString("Начало сбора данных, парные пробы (t = %1c, %2)").arg(startWin->getTime()).arg(msg);
            setUserMessage(msg, true, true);
            setupRealtimeData();
        }
        startIncub();
    }
}

void Widget::startData(int n)
{
    if(n == 1) {
        data1 = true;
        setUserMessage("Измерение по каналу 1");
        emit status(QString("Измерение по каналу 1"));
        startProgressBarTimer("Измерение по каналу 1 %p%", 10, startWin->getTime() * 1000);
        auto func = [=](){writeData(1);};
        QTimer::singleShot(startWin->getTime() * 1000, func);
    }
    if(n == 2) {
        data2 = true;
        emit status(QString("Измерение по каналу 2"));
        startProgressBarTimer("Измерение по каналу 2 %p%", 10, startWin->getTime() * 1000);
        auto func = [=](){writeData(2);};
        QTimer::singleShot(startWin->getTime() * 1000, func);
    }
    if(n == 3) {
        data3 = true;
        emit status(QString("Измерение по каналу 3"));
        startProgressBarTimer("Измерение по каналу 3 %p%", 10, startWin->getTime() * 1000);
        auto func = [=](){writeData(3);};
        QTimer::singleShot(startWin->getTime() * 1000, func);
    }
    if(n == 4) {
        data4 = true;
        emit status(QString("Измерение по каналу 4"));
        startProgressBarTimer("Измерение по каналу 4 %p%", 10, startWin->getTime() * 1000);
        auto func = [=](){writeData(4);};
        QTimer::singleShot(startWin->getTime() * 1000, func);
    }
}

void Widget::stopData(int n)
{
    if(n == 1) {
        data1 = false;
        pulse1 = false;
    }
    if(n == 2) {
        data2 = false;
        pulse2 = false;
    }
    if(n == 3) {
        data3 = false;
        pulse3 = false;
    }
    if(n == 4) {
        data4 = false;
        pulse4 = false;
    }
}

bool Widget::isData(int n)
{
    if(n == 1)
        return data1;
    if(n == 2)
        return data2;
    if(n == 3)
        return data3;
    if(n == 4)
        return data4;
    return 0;
}

void Widget::startIncub()
{
    setUserMessage("Инкубация");
    startProgressBarTimer("Инкубация %p%", 10, startWin->getTimeIncube()*1000);
    QTimer::singleShot(startWin->getTimeIncube()*1000, this, &incubeTimeout);
    incub = true;
    emit status(QString("Инкубация"));
}

void Widget::stopIncub()
{
    incub = false;
}

bool Widget::isIncub()
{
    return incub;
}

void Widget::incubeTimeout()
{
    stopIncub();
    if(startWin->isChannel_1())
        pulse1 = true;
    if(startWin->isChannel_2())
        pulse2 = true;
    if(startWin->isChannel_3())
        pulse3 = true;
    if(startWin->isChannel_4())
        pulse3 = true;
    setUserMessage("Время инкубации истекло, добавьте стартовый реагеет");
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

    //таймер для отображения процесса сбора данных
    connect(&progressTimer, SIGNAL(timeout()), SLOT(updateProgressValue()));
}

void Widget::writeData(const int n)
{
    stopData(n);
    emit status(QString("Запись данных по каналу %1").arg(n));
    ui->progressBar->setFormat("Запись данных %p%");
    qDebug().noquote() << QString("Запись данных по каналу %1").arg(n);
    QStringList strList;
    strList << QString("N\t");
    if(!y1.isEmpty())
        strList << QString("V1#%1\t").arg(startWin->getNum_1());
    else strList << QString("V1#0\t");
    if(!y2.isEmpty())
        strList << QString("V2#%1\t").arg(startWin->getNum_2());
    else strList << QString("V2#0\t");
    if(!y3.isEmpty())
        strList << QString("V3#%1\t").arg(startWin->getNum_3());
    else strList << QString("V3#0\t");
    if(!y4.isEmpty())
        strList << QString("V4#%1\t").arg(startWin->getNum_4());
    else strList << QString("V4#0\t");
    strList << QString("t#%5\tti#%6\tp#%7\n").arg(startWin->getTime())
                                             .arg(startWin->getTimeIncube())
                                             .arg(startWin->isSingle());
//    QStringList extList;
//    QMap<double, double>::const_iterator it = y1.constBegin();
//    while(it != y1.constEnd()) {
//        strList << QString("%1\t").arg(it.value()) << QString("%1\n").arg(it.key());
//    }
    for(int i=0; i<x.length(); i++)
    {
        progressTimer.stop();
        ui->progressBar->setMaximum(x.length());
        ui->progressBar->setValue(i);//i*100/x.length());

        strList << QString("%1\t").arg(i);
        if(!y1.isEmpty())
            strList << QString("%1\t").arg(y1[i]);
        if(!y2.isEmpty())
            strList << QString("%1\t").arg(y2[i]);
        if(!y3.isEmpty())
            strList << QString("%1\t").arg(y3[i]);
        if(!y4.isEmpty())
            strList << QString("%1\t").arg(y4[i]);
        strList << QString("%1\n").arg(x[i]);
    }
    y1.clear();
    y2.clear();
    y3.clear();
    y4.clear();
    x.clear();
    ui->progressBar->setVisible(false);
    setUserMessage(saveFiles.writeData(strList), true, true);
}
