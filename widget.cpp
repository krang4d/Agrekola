#include "widget.h"
#include "ui_widget.h"
#include <QScrollBar>
#include <QMessageBox>

#include <QThread>

Widget::Widget(useE154 *Agrekola, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setAgrekola(Agrekola);
    setWindowTitle("Программы сбора данных с АЦП(E-154) по 4 каналам");
    customPlot1 = ui->frame_1;
    customPlot2 = ui->frame_2;
    customPlot3 = ui->frame_3;
    customPlot4 = ui->frame_4;
    setupRealtimeData();

    TDTimer.start(200);
    connect(&TDTimer, SIGNAL(timeout()), this, SLOT(updataTD()));
    setText(QString("Допустимое количество потоков %1\n").arg(QThread::idealThreadCount()));
}

void Widget::setText(QString str)
{
    ui->textEdit->append(str);
}

void Widget::setAgrekola(useE154 *agr)
{
    Agrecola = agr;
}

void Widget::setupQuadraticPlot(QVector<double> data)
{
    if (data.isEmpty())
    {
        QMessageBox::warning(this, tr("My Application"),
                             tr("Нет данных для вывода графика.\n"));
    }
    customPlot1->addGraph();
    QVector<double> x;
    double average;
    for(int i = 0; i < data.count(); i++)
    {
        x.append(double(i));
        average += data[i];
    }
    average /= data.length();
    ui->label_average->setText(QString("%1").arg(average));
    customPlot1->graph(0)->setData(x, data);
    // give the axes some labels:
    customPlot1->xAxis->setLabel("x");
    customPlot1->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    customPlot1->xAxis->setRange(0, data.length());
    customPlot1->yAxis->setRange(-5, 5);
    customPlot1->replot();
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

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%m:%s");

    customPlot1->addGraph();
    customPlot1->graph(0)->setPen(QPen(QColor(10, 110, 40)));
    customPlot1->xAxis->setTicker(timeTicker);
    customPlot1->axisRect()->setupFullAxesBox();
    customPlot1->xAxis->setLabel("Время, с");
    customPlot1->yAxis->setLabel("Напряжение, В");
    customPlot1->yAxis->setRange(-5.5, 5.5);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(customPlot1->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot1->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot1->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot1->yAxis2, SLOT(setRange(QCPRange)));

    customPlot2->addGraph();
    customPlot2->graph(0)->setPen(QPen(QColor(255, 110, 40)));
    customPlot2->xAxis->setTicker(timeTicker);
    customPlot2->axisRect()->setupFullAxesBox();
    customPlot2->xAxis->setLabel("Время, с");
    customPlot2->yAxis->setLabel("Напряжение, В");
    customPlot2->yAxis->setRange(-5.5, 5.5);

    connect(customPlot2->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot2->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot2->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot2->yAxis2, SLOT(setRange(QCPRange)));

    customPlot3->addGraph();
    customPlot3->graph(0)->setPen(QPen(QColor(255, 110, 200)));
    customPlot3->xAxis->setTicker(timeTicker);
    customPlot3->axisRect()->setupFullAxesBox();
    customPlot3->xAxis->setLabel("Время, с");
    customPlot3->yAxis->setLabel("Напряжение, В");
    customPlot3->yAxis->setRange(-5.5, 5.5);

    connect(customPlot3->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot3->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot3->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot3->yAxis2, SLOT(setRange(QCPRange)));

    customPlot4->addGraph();
    customPlot4->graph(0)->setPen(QPen(QColor(255, 200, 40)));
    customPlot4->xAxis->setTicker(timeTicker);
    customPlot4->axisRect()->setupFullAxesBox();
    customPlot4->xAxis->setLabel("Время, с");
    customPlot4->yAxis->setLabel("Напряжение, В");
    customPlot4->yAxis->setRange(-5.5, 5.5);

    connect(customPlot4->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot4->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot4->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot4->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_AdcSample_clicked()
{
    double data = Agrecola->AdcSample(useE154::CH2);
    setText(QString(std::to_string(data).c_str()) + "\n");
    QScrollBar *vb = ui->textEdit->verticalScrollBar();
    int max = vb->maximum();
    vb->setValue(max);
    //Sleep(1000);
}

void Widget::on_AdcKadr_clicked()
{
    Agrecola->AdcKADR();
    string str = "ADC[1] = " + std::to_string(Agrecola->volts_array[0]) + "   ADC2 = " + std::to_string(Agrecola->volts_array[1]) +\
            "   ADC3 = " + std::to_string(Agrecola->volts_array[2]) + "   ADC3 = " + std::to_string(Agrecola->volts_array[2]) +"\r\n";
    setText(QString(str.c_str()));
    QScrollBar *vb = ui->textEdit->verticalScrollBar();
    int max = vb->maximum();
    vb->setValue(max);
}

void Widget::on_AdcSynchro_clicked()
{
    Agrecola->vec_data.clear();
    setText(QString(Agrecola->AdcSynchro().c_str()));
    setupQuadraticPlot(Agrecola->vec_data);
    QScrollBar *vb = ui->textEdit->verticalScrollBar();
    int max = vb->maximum();
    vb->setValue(max);
}

void Widget::realtimeDataSlot()
{
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.002) // at most add point every 2 ms
    {
      // add data to lines:
      double a1 = Agrecola->AdcSample(useE154::CH1);
      double a2 = Agrecola->AdcSample(useE154::CH2);
      double a3 = Agrecola->AdcSample(useE154::CH3);
      double a4 = Agrecola->AdcSample(useE154::CH4);
      customPlot1->graph(0)->addData(key, a1); //qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
      customPlot2->graph(0)->addData(key, a2); //qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
      customPlot3->graph(0)->addData(key, a3); //qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
      customPlot4->graph(0)->addData(key, a4); //qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
      //rescale value (vertical) axis to fit the current data:
      //ui->customPlot->graph(0)->rescaleValueAxis();
      //ui->customPlot->graph(1)->rescaleValueAxis(true);
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    customPlot1->xAxis->setRange(key, 8, Qt::AlignRight);
    customPlot1->replot();

    customPlot2->xAxis->setRange(key, 8, Qt::AlignRight);
    customPlot2->replot();

    customPlot3->xAxis->setRange(key, 8, Qt::AlignRight);
    customPlot3->replot();

    customPlot4->xAxis->setRange(key, 8, Qt::AlignRight);
    customPlot4->replot();

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
        ui->label_fps->setText(QString("%1 FPS, Total Data points: %2")
                        .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
                        .arg(customPlot1->graph(0)->data()->size()+customPlot2->graph(0)->data()->size() + customPlot3->graph(0)->data()->size() + customPlot4->graph(0)->data()->size()));
        lastFpsKey = key;
        frameCount = 0;
    }
}

void Widget::on_checkBox_1_stateChanged(int arg1)
{
    if(arg1){
        setText("on_checkBox_1");
        Agrecola->SetChannel(useE154::CH1, useE154::ON);
    }
    else{
        setText("off_checkBox_1");
        Agrecola->SetChannel(useE154::CH1, useE154::OFF);
    }
}

void Widget::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1){
        setText("on_checkBox_2");
        Agrecola->SetChannel(useE154::CH2, useE154::ON);
    }
    else{
        setText("off_checkBox_2");
        Agrecola->SetChannel(useE154::CH2, useE154::OFF);
    }
}

void Widget::on_checkBox_3_stateChanged(int arg1)
{
    if(arg1){
        setText("on_checkBox_3");
        Agrecola->SetChannel(useE154::CH3, useE154::ON);
    }
    else{
        setText("off_checkBox_3");
        Agrecola->SetChannel(useE154::CH3, useE154::OFF);
    }
}

void Widget::on_checkBox_4_stateChanged(int arg1)
{
    if(arg1){
        setText("on_checkBox_4");
        Agrecola->SetChannel(useE154::CH4, useE154::ON);
    }
    else{
        setText("off_checkBox_4");
        Agrecola->SetChannel(useE154::CH4, useE154::OFF);
    }
}

void Widget::updataTD()
{

    if(!Agrecola->GetStatusTD())
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
