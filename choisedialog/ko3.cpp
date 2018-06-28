#include "ko3.h"
#include "ui_ko3.h"

Ko3::Ko3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ko3)
{
    ui->setupUi(this);
}

Ko3::~Ko3()
{
    delete ui;
}

void Ko3::on_startButton_clicked()
{
    emit measurement();
}

void Ko3::on_calibr1Button_clicked()
{
    emit calibration();
}

