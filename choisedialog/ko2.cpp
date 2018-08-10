#include "ko2.h"
#include "ui_ko2.h"

Ko2::Ko2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ko2)
{
    ui->setupUi(this);
    file.openKo2(param);
    if( !param.isEmpty() && param.count() == 5 ) {
        ui->label_calibrationData->setText(param.at(0));
        ui->lineEdit_1->setText(param.at(1));
        ui->lineEdit_2->setText(param.at(2));
        ui->lineEdit_3->setText(param.at(3));
        ui->lineEdit_4->setText(param.at(4));
    }
}

Ko2::~Ko2()
{
    param.clear();
    param << ui->label_calibrationData->text() << ui->lineEdit_1->text()
          << ui->lineEdit_2->text() << ui->lineEdit_3->text()
          << ui->lineEdit_4->text();
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
