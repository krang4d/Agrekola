#include "agr2.h"
#include "ui_agr2.h"

Agr2::Agr2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Agr2)
{
    ui->setupUi(this);
    file.openAgr2(param);
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
    selcalibrAgr1 = new SelectCalibrationAgr1();
    selInductor = new SelectInductor();
}

Agr2::~Agr2()
{
    delete ui;
    param.clear();
    param << ui->label_calibrationData->text() << ui->lineEdit_1->text()
          << ui->lineEdit_2->text() << ui->lineEdit_3->text() << ui->lineEdit_4->text()
          << ui->lineEdit_5->text() << ui->lineEdit_6->text() <<ui->lineEdit_7->text()
          << ui->lineEdit_8->text();
    file.saveAgr2(param);
    //delete kalibragr2;
    delete selInductor;
    delete selcalibrAgr1;
}

void Agr2::on_startButton_clicked()
{
    selcalibrAgr1->show();
    emit measurement();
}

void Agr2::on_calibrButton_clicked()
{
    kalibragr2 = new KalibrAgr2();
    kalibragr2->show();
    emit calibration();
}
