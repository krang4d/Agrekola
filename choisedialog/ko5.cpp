#include "ko5.h"
#include "ui_ko5.h"

Ko5::Ko5(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ko5)
{
    ui->setupUi(this);
    file.openKo5(param);
    if( !param.isEmpty() && param.count() == 9 ) {
        ui->label_calibrationData->setText(param.at(0));
        ui->lineEdit_1->setText(param.at(1));
        ui->lineEdit_2->setText(param.at(2));
        ui->lineEdit_3->setText(param.at(3));
        ui->lineEdit_4->setText(param.at(4));
        ui->lineEdit_5->setText(param.at(5));
        ui->lineEdit_6->setText(param.at(6));
        ui->lineEdit_7->setText(param.at(7));
        ui->lineEdit_8->setText(param.at(8));
    }
}

Ko5::~Ko5()
{
    param.clear();
    param << ui->label_calibrationData->text() << ui->lineEdit_1->text()
          << ui->lineEdit_2->text() << ui->lineEdit_3->text() << ui->lineEdit_4->text()
          << ui->lineEdit_5->text() << ui->lineEdit_6->text() <<ui->lineEdit_7->text()
          << ui->lineEdit_8->text();
    file.saveKo5(param);
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
