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
    string str = std::to_string(Agrecola->AdcSample()) + "\r\n";
    setText(QString(str.c_str()));
    QScrollBar *vb = ui->textEdit->verticalScrollBar();
    int max = vb->maximum();
    vb->setValue(max);
//    for(int i = 0; i < 10; i++){
//        //Sleep(1000);
//    }
}

void Widget::on_btnTest_clicked()
{

}
