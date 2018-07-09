#include "startmeasurment.h"
#include "ui_startmeasurment.h"
#include "mainwindow.h"

#include <QMessageBox>

StartMeasurment::StartMeasurment(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::StartMeasurment)
{
    ui->setupUi(this);
    cancel = true;
    single = true;
    channel_1 = false;
    channel_2 = false;
    channel_3 = false;
    channel_4 = false;
    num_1 = 0;
    num_2 = 0;
    num_3 = 0;
    num_4 = 0;
    time = 0;
}

StartMeasurment::~StartMeasurment()
{
    delete ui;
}

bool StartMeasurment::isCancel()
{
    return cancel;
}

bool StartMeasurment::isSingle()
{
    return single;
}

bool StartMeasurment::isChannel_1()
{
    return channel_1;
}

bool StartMeasurment::isChannel_2()
{
    return channel_2;
}

bool StartMeasurment::isChannel_3()
{
    return channel_3;
}

bool StartMeasurment::isChannel_4()
{
    return channel_4;
}

int StartMeasurment::getNum_1()
{
    return num_1;
}

int StartMeasurment::getNum_2()
{
    return num_2;
}

int StartMeasurment::getNum_3()
{
    return num_3;
}

int StartMeasurment::getNum_4()
{
    return num_4;
}

int StartMeasurment::getTime()
{
    return time;
}

QString StartMeasurment::getStringStatus()
{
    return QString("");
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

void StartMeasurment::on_radioButton_single_toggled(bool checked)
{
    single = checked;
}

void StartMeasurment::on_pushButton_next_clicked()
{
    QMessageBox mb;
    mb.setIcon(QMessageBox::Information);
    mb.setInformativeText("Не выбран канал измерения!");
    if(ui->checkBox_ch1->isChecked() || ui->checkBox_ch2->isChecked() ||\
            ui->checkBox_ch3->isChecked() || ui->checkBox_ch4->isChecked());
    else{
        mb.exec();
        return;
    }
    single = ui->radioButton_single->isChecked();           //пробы одиночные?
    channel_1 = ui->checkBox_ch1->isChecked();
    if(channel_1)
        num_1 = ui->lineEdit_ch1->text().toInt();

    channel_2 = ui->checkBox_ch2->isChecked();
    if(channel_2)
        num_2 = ui->lineEdit_ch2->text().toInt();

    channel_3 = ui->checkBox_ch3->isChecked();
    if(channel_3)
        num_3 = ui->lineEdit_ch3->text().toInt();

    channel_4 = ui->checkBox_ch4->isChecked();
    if(channel_4)
        num_4 = ui->lineEdit_ch4->text().toInt();

    time = ui->lineEdit_time->text().toInt();               //время записи

    mb.setInformativeText("Введите номер пробы!");
    if(ui->checkBox_ch1->isChecked() && ui->lineEdit_ch1->text().isEmpty())
        mb.exec();
    else if(ui->checkBox_ch2->isChecked() && ui->lineEdit_ch2->text().isEmpty())
        mb.exec();
    else if(ui->checkBox_ch3->isChecked() && ui->lineEdit_ch3->text().isEmpty())
        mb.exec();
    else if(ui->checkBox_ch4->isChecked() && ui->lineEdit_ch4->text().isEmpty())
        mb.exec();
    else
    {
        cancel = false;
        hide();
        emit startMeasurment();

    }
}

void StartMeasurment::on_pushButton_cancel_clicked()
{
    cancel = true;
    hide();
}
