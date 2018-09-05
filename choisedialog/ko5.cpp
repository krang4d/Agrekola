#include "ko5.h"
#include "ui_ko5.h"

Ko5::Ko5(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ko5)
{
    ui->setupUi(this);
    file.openKo5(param);
    if( !param.isEmpty() && param.count() >= 7 ) {
        ui->label_calibrationData->setText(param.at(0));
        ui->lineEdit_1->setText(param.at(1));
        ui->lineEdit_2->setText(param.at(2));
        ui->lineEdit_3->setText(param.at(3));
        ui->lineEdit_4->setText(param.at(4));
        ui->lineEdit_5->setText(param.at(5));
        ui->lineEdit_6->setText(param.at(6));
    }
    connect(ui->page_2, &StartMeasurment::startMeasurment, this, &Ko5::measurement);
}

Ko5::~Ko5()
{
    //param.clear();
    param.replace(0, ui->label_calibrationData->text());
    param.replace(1, ui->lineEdit_1->text());
    param.replace(2, ui->lineEdit_2->text());
    param.replace(3, ui->lineEdit_3->text());
    param.replace(4, ui->lineEdit_4->text());
    param.replace(5, ui->lineEdit_5->text());
    param.replace(6, ui->lineEdit_6->text());
    file.saveKo5(param);
    delete ui;
}

void Ko5::on_startButton_clicked()
{
    emit measurement(ui->page_2);
}

void Ko5::on_calibr1Button_clicked()
{
    emit calibration();
}
