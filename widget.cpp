#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

void Widget::setText(QString str)
{
    text += str;
    ui->textEdit->setText(text);
}

Widget::~Widget()
{
    delete ui;
}
