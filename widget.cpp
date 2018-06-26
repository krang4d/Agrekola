#include "widget.h"
#include "ui_widget.h"
#include <QScrollBar>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->frame->addGraph();
}

void Widget::setText(QString str)
{
    ui->textEdit->append(str);
}

void Widget::setAgrekola(useE154 *agr)
{
    Agrecola = agr;
}

void Widget::setupQuadraticPlot(QCustomPlot *customPlot, QVector<double> data)
{

    // generate some data:
//    if (data.isEmpty() == 0)
//    {
//        QVector<double> x(101), y(101); // initialize with entries 0..100
//        for (int i=0; i<101; ++i)
//            {
//              x[i] = i/50.0 - 1; // x goes from -1 to 1
//              y[i] = x[i]*x[i];  // let's plot a quadratic function
//            }
//        customPlot->graph(0)->setData(x, y);
//    }
//    else
//    {
        QVector<double> x;
        for(int i = 0; i < data.count(); i++)
        {
            x.append(double(i));
        }
        customPlot->graph(0)->setData(x, data);
//    }
    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(-1, data.length());
    customPlot->yAxis->setRange(-3, 3);
    customPlot->replot();
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
    setupQuadraticPlot(ui->frame, Agrecola->vec_data);
    QScrollBar *vb = ui->textEdit->verticalScrollBar();
    int max = vb->maximum();
    vb->setValue(max);
}
