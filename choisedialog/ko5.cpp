#include "ko5.h"
#include "ui_ko5.h"

Ko5::Ko5(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ko5)
{
    ui->setupUi(this);
}

Ko5::~Ko5()
{
    delete ui;
}

void Ko5::on_startButton_clicked()
{
    emit measurement();
}

void Ko5::on_calibr1Button_clicked()
{
    emit calibration();
}

void Ko5::on_calibr2Button_clicked()
{
    emit calibration();
}
