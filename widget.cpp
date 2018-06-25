#include "widget.h"
#include "ui_widget.h"
#include <QScrollBar>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //ui->plotRt->drawChart();
}

void Widget::setText(QString str)
{
    ui->textEdit->append(str);
}

void Widget::setAgrekila(useE154 *agr)
{
    Agrecola = agr;
}

void Widget::setPlot()
{

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
    setText(QString(Agrecola->AdcSynchro().c_str()));
    QScrollBar *vb = ui->textEdit->verticalScrollBar();
    int max = vb->maximum();
    vb->setValue(max);
}
