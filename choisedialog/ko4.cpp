#include "ko4.h"
#include "ui_ko4.h"

Ko4::Ko4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ko4)
{
    ui->setupUi(this);
    file.openKo4(param);
    if( !param.isEmpty() && param.count() == 6 ) {
        ui->label_calibrationData->setText(param.at(0));
        ui->lineEdit_1->setText(param.at(1));
        ui->lineEdit_2->setText(param.at(2));
        ui->lineEdit_3->setText(param.at(3));
        ui->lineEdit_4->setText(param.at(4));
        ui->lineEdit_5->setText(param.at(5));
    }
}

Ko4::~Ko4()
{
    param.clear();
    param << ui->label_calibrationData->text() << ui->lineEdit_1->text()
          << ui->lineEdit_2->text() << ui->lineEdit_3->text() << ui->lineEdit_4->text()
          << ui->lineEdit_5->text();
    file.saveKo4(param);
    delete ui;
}

void Ko4::on_startButton_clicked()
{
    emit measurement();
}

void Ko4::on_calibr1Button_clicked()
{
    emit calibration();
}
