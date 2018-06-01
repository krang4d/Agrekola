#include "ko2.h"
#include "ui_ko2.h"

Ko2::Ko2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ko2)
{
    ui->setupUi(this);
}

Ko2::~Ko2()
{
    delete ui;
}

void Ko2::on_startButton_clicked()
{
    emit measurement();
}

void Ko2::on_calibr1Button_clicked()
{
    emit calibration();
}

void Ko2::on_calibr2Button_clicked()
{
    emit calibration();
}
