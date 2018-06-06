#include "agr1.h"
#include "ui_agr1.h"

Agr1::Agr1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Agr1)
{
    ui->setupUi(this);
}

Agr1::~Agr1()
{
    delete ui;
}

void Agr1::on_startButton_clicked()
{
    emit measurement();
}

void Agr1::on_kolibrButton_clicked()
{
    emit calibration();
}
