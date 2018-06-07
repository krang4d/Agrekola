#include "startmeasurment.h"
#include "ui_startmeasurment.h"
#include "mainwindow.h"

#include <QMessageBox>

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
//    MainWindow *m = qobject_cast<MainWindow *>(parentWidget());
//    Measurement *cw = qobject_cast<Measurement *>(m->centralWidget());
//    cw->setFreq(ui->lineEdit_frequency->text().toDouble());
//    cw->setTime(ui->lineEdit_time->text().toInt());
    emit startMeasurment();
    hide();
}

void StartMeasurment::on_radioButton_single_toggled(bool checked)
{
    single = checked;
    QMessageBox mb;
    mb.setInformativeText("rb_single pressed");
    mb.exec();
}
