#include "startmeasurment.h"
#include "ui_startmeasurment.h"

StartMeasurment::StartMeasurment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartMeasurment)
{
    ui->setupUi(this);
}

StartMeasurment::~StartMeasurment()
{
    delete ui;
}

void StartMeasurment::on_checkBox_ch1_stateChanged(int arg1)
{
    if(arg1) ui->lineEdit_ch1->setEnabled(true);
    else ui->lineEdit_ch1->setEnabled(false);
}

void StartMeasurment::on_checkBox_ch2_stateChanged(int arg1)
{
    if(arg1) ui->lineEdit_ch2->setEnabled(true);
    else ui->lineEdit_ch2->setEnabled(false);
}

void StartMeasurment::on_checkBox_ch3_stateChanged(int arg1)
{
    if(arg1) ui->lineEdit_ch3->setEnabled(true);
    else ui->lineEdit_ch3->setEnabled(false);
}

void StartMeasurment::on_checkBox_ch4_stateChanged(int arg1)
{
    if(arg1) ui->lineEdit_ch4->setEnabled(true);
    else ui->lineEdit_ch4->setEnabled(false);
}

void StartMeasurment::on_pushButton_next_clicked()
{
    hide();
    this->~StartMeasurment();
}
