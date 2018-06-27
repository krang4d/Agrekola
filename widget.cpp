#include "widget.h"
#include "ui_widget.h"
#include <QScrollBar>
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    customPlot = ui->frame;
    setupRealtimeData();
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
    customPlot->addGraph();
    QVector<double> x;
    double average;
    for(int i = 0; i < data.count(); i++)
    {
        x.append(double(i));
        average += data[i];
    }
    average /= data.length();
    ui->label_average->setText(QString("%1").arg(average));
    customPlot->graph(0)->setData(x, data);
    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(0, data.length());
    customPlot->yAxis->setRange(-5, 5);
    customPlot->replot();
}

void Widget::setupRealtimeData()
{
    // include this section to fully disable antialiasing for higher performance:
    /*
    customPlot->setNotAntialiasedElements(QCP::aeAll);
    QFont font;
    font.setStyleStrategy(QFont::NoAntialias);
    customPlot->xAxis->setTickLabelFont(font);
    customPlot->yAxis->setTickLabelFont(font);
    customPlot->legend->setFont(font);
    */
    customPlot->addGraph(); // blue line
    customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    customPlot->addGraph(); // red line
    customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    customPlot->xAxis->setTicker(timeTicker);
    customPlot->axisRect()->setupFullAxesBox();
    customPlot->yAxis->setRange(-6, 6);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

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
    double data = Agrecola->AdcSample(CH2);
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
      double a = Agrecola->AdcSample(CH1);
      double b = Agrecola->AdcSample(CH2);
      customPlot->graph(0)->addData(key, a); //qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
      customPlot->graph(1)->addData(key, b); //qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
      // rescale value (vertical) axis to fit the current data:
      //ui->customPlot->graph(0)->rescaleValueAxis();
      //ui->customPlot->graph(1)->rescaleValueAxis(true);
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
    customPlot->replot();

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
//    if (key-lastFpsKey > 2) // average fps over 2 seconds
//    {
//      ui->statusBar->showMessage(
//            QString("%1 FPS, Total Data points: %2")
//            .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
//            .arg(ui->customPlot->graph(0)->data()->size()+ui->customPlot->graph(1)->data()->size())
//            , 0);
//      lastFpsKey = key;
//      frameCount = 0;
//    }
}
