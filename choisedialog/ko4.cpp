#include "ko4.h"
#include "ui_ko4.h"

Ko4::Ko4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ko4)
{
    ui->setupUi(this);
    file.openKo4(param);
    if( !param.isEmpty() && param.count() >= 6 ) {
        ui->label_calibrationData->setText(param.at(0));
        ui->lineEdit_1->setText(param.at(1));
        ui->lineEdit_2->setText(param.at(2));
        ui->lineEdit_3->setText(param.at(3));
        ui->lineEdit_4->setText(param.at(4));
        ui->lineEdit_5->setText(param.at(5));
    } else
        param = QStringList({0, 0, 0, 0, 0, 0, 0 , 0 , 0, 0});//10 параметров
    connect(ui->page_2, &StartMeasurment::startMeasurment, this, &Ko4::measurement);
}

Ko4::~Ko4()
{
    //param.clear();
    param.replace(0, ui->label_calibrationData->text());
    param.replace(1, ui->lineEdit_1->text());
    param.replace(2, ui->lineEdit_2->text());
    param.replace(3, ui->lineEdit_3->text());
    param.replace(4, ui->lineEdit_4->text());
    param.replace(5, ui->lineEdit_5->text());
    file.saveKo4(param);
    delete ui;
}

void Ko4::on_startButton_clicked()
{
    emit measurement(ui->page_2);
}

void Ko4::on_calibr1Button_clicked()
{
    emit calibration(StartCalibrationKo4::getStart());
}

void Ko4::calibration_data_come(int n, double deta)
{
    //один параметр контрольной нормальной плазмы
    QDateTime dt = QDateTime::currentDateTime();
    ui->label_calibrationData->setText(dt.toString("dd.MM.yyyy ") + dt.toString("hh:mm:ss"));
    if(param.count() <= n)
        param.push_back(QString("%1").arg(deta));
    else param.replace(n, QString("%1").arg(deta));
    file.saveKo4(param);
}

void Ko4::calibration_data1_come(double t0)
{
    calibration_data_come(6, t0);
}

void Ko4::calibration_data2_come(double t0)
{
    calibration_data_come(7, t0);
}

void Ko4::calibration_data3_come(double t0)
{
    calibration_data_come(8, t0);
}

void Ko4::calibration_data4_come(double t0)
{
    calibration_data_come(9, t0);
}

StartMeasurment *StartCalibrationKo4::getStart()
{
    StartMeasurment *sm = new StartMeasurment(0);
    sm->setChannels(true, true, true, true);
    sm->setNum(1, "Калибровка");
    sm->setNum(2, "Калибровка");
    sm->setNum(3, "Калибровка");
    sm->setNum(4, "Калибровка");
    sm->setTime(10);
    sm->setTimeIncube(1, 3);
    //stKo2->cancel = false;
    return sm;
}
