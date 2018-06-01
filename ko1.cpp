#include "ko1.h"
#include "ui_ko1.h"

Ko1::Ko1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ko1)
{
    ui->setupUi(this);
}

Ko1::~Ko1()
{
    delete ui;
}

void Ko1::on_startButton_clicked()
{
    emit measurement();
}
