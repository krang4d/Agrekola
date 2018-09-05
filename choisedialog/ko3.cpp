#include "ko3.h"
#include "ui_ko3.h"

Ko3::Ko3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ko3)
{
    ui->setupUi(this);
    file.openKo3(param);
    if( !param.isEmpty() && param.count() >= 4 ) {
        ui->label_calibrationData->setText(param.at(0));
        ui->lineEdit_1->setText(param.at(1));
        ui->lineEdit_2->setText(param.at(2));
        ui->lineEdit_3->setText(param.at(3));
    }
    connect(ui->page_2, &StartMeasurment::startMeasurment, this, &Ko3::measurement);
}

Ko3::~Ko3()
{
    //param.clear();
    param.replace(0, ui->label_calibrationData->text());
    param.replace(1, ui->lineEdit_1->text());
    param.replace(2, ui->lineEdit_2->text());
    param.replace(3, ui->lineEdit_3->text());
    file.saveKo3(param);
    delete ui;
}

void Ko3::on_startButton_clicked()
{
    emit measurement(ui->page_2);
}

void Ko3::on_calibr1Button_clicked()
{
    emit calibration();
}
