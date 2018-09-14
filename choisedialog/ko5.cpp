#include "ko5.h"
#include "ui_ko5.h"

Ko5::Ko5(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ko5)
{
    ui->setupUi(this);
    open();
    connect(ui->page_2, &StartMeasurment::startMeasurment, this, &Ko5::measurement);
}

Ko5::~Ko5()
{
    save();
    delete ui;
}

void Ko5::on_calibr1Button_clicked()
{
    file.saveKo5(param);
    emit calibration(StartCalibrationKo5::getStart());
}

void Ko5::calibrationDataCome(int n, double deta)
{
    //один параметр контрольной нормальной плазмы
    QDateTime dt = QDateTime::currentDateTime();
    ui->label_calibrationData->setText(dt.toString("dd.MM.yyyy ") + dt.toString("hh:mm:ss"));
    if(param.count() <= n)
        param.push_back(QString("%1").arg(deta));
    else param.replace(n, QString("%1").arg(deta));
    file.saveKo5(param);
}

void Ko5::open()
{
    file.openKo5(param);
    if( !param.isEmpty() && param.count() >= 11 ) {
        ui->label_calibrationData->setText(param.at(0));
        ui->lineEdit_1->setText(param.at(1));
        ui->lineEdit_2->setText(param.at(2));
        ui->lineEdit_3->setText(param.at(3));
        ui->lineEdit_4->setText(param.at(4));
        ui->lineEdit_5->setText(param.at(5));
        ui->lineEdit_6->setText(param.at(6));
    } else
        param = QStringList({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}); //11 параметров
}

void Ko5::save()
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
}

void Ko5::calibrationData1Come(double t0)
{
    calibrationDataCome(7, t0);
}

void Ko5::calibrationData2Come(double t0)
{
    calibrationDataCome(8, t0);
}

void Ko5::calibrationData3Come(double t0)
{
    calibrationDataCome(9, t0);
}

void Ko5::calibrationData4Come(double t0)
{
    calibrationDataCome(10, t0);
}

StartMeasurment *StartCalibrationKo5::getStart()
{
    StartMeasurment *sm = new StartMeasurment(0);
    sm->setChannels(true, true, true, true);
    sm->setNum(1, "Калибровка");
    sm->setNum(2, "Калибровка");
    sm->setNum(3, "Калибровка");
    sm->setNum(4, "Калибровка");
    sm->setTime(10);
    sm->setTimeIncube(1, 3);
    return sm;
}
