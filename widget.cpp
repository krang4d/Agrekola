#include "widget.h"
#include "ui_widget.h"
#include <QScrollBar>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //connect(SIGNAL())
}

void Widget::setText(QString str)
{
    text += str;
    ui->textEdit->setText(text);
}

void Widget::setAgrekila(useE154 *agr)
{
    Agrecola = agr;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnMes_clicked()
{
        string str = std::to_string(Agrecola->AdcSample(CH2)) + "\r\n";
        setText(QString(str.c_str()));
        QScrollBar *vb = ui->textEdit->verticalScrollBar();
        int max = vb->maximum();
        vb->setValue(max);
        //Sleep(1000);
}

void Widget::on_btnTest_clicked()
{
    Agrecola->AdcKADR();
    string str = "ADC[1] = " + std::to_string(Agrecola->volts_array[0]) + "   ADC2 = " + std::to_string(Agrecola->volts_array[1]) +\
            "   ADC3 = " + std::to_string(Agrecola->volts_array[2]) + "   ADC3 = " + std::to_string(Agrecola->volts_array[2]) +"\r\n";
    setText(QString(str.c_str()));
    QScrollBar *vb = ui->textEdit->verticalScrollBar();
    int max = vb->maximum();
    vb->setValue(max);
}
