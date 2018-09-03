#include "ko2.h"
#include "ui_ko2.h"
#include <QDateTime>

Ko2::Ko2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ko2)
{
    ui->setupUi(this);
    file.openKo2(param);
    if( !param.isEmpty() && param.count() >= 5 ) {
        ui->label_calibrationData->setText(param.at(0));
        ui->lineEdit_1->setText(param.at(1));
        ui->lineEdit_2->setText(param.at(2));
        ui->lineEdit_3->setText(param.at(3));
        ui->lineEdit_4->setText(param.at(4));
    }
}

Ko2::~Ko2()
{
    //param.clear();
    param.replace(0, ui->label_calibrationData->text());
    param.replace(1, ui->lineEdit_1->text());
    param.replace(2, ui->lineEdit_2->text());
    param.replace(3, ui->lineEdit_3->text());
    param.replace(4, ui->lineEdit_4->text());
    file.saveKo2(param);
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

void Ko2::calibration_data_come(double t0)
{
    //один параметр АЧТВ контрольной нормальной плазмы
    QDateTime dt = QDateTime::currentDateTime();
    ui->label_calibrationData->setText(dt.toString("dd.MM.yyyy ") + dt.toString("hh:mm:ss"));
    if(param.count() <= 5)
        param.push_back(QString("%1").arg(t0));
    else param.replace(5, QString("%1").arg(t0));
    file.saveKo2(param);
}
