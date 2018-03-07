#include "widget.h"
#include "ui_widget.h"

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
    for(int i = 0; i < 10; i++){
        setText(QString(str.c_str()));
        Sleep(1000);
    }
}
