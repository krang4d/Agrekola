#include "ko3.h"
#include "ui_ko3.h"

Ko3::Ko3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ko3)
{
    ui->setupUi(this);
    file.openKo3(param);
    if( !param.isEmpty() && param.count() == 4 ) {
        ui->label_calibrationData->setText(param.at(0));
        ui->lineEdit_1->setText(param.at(1));
        ui->lineEdit_2->setText(param.at(2));
        ui->lineEdit_3->setText(param.at(3));
    }
}

Ko3::~Ko3()
{
    param.clear();
    param << ui->label_calibrationData->text() << ui->lineEdit_1->text()
          << ui->lineEdit_2->text() << ui->lineEdit_3->text();
    file.saveKo3(param);
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

