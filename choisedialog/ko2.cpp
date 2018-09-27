#include "ko2.h"
#include "ui_ko2.h"
#include <QDateTime>

Ko2::Ko2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ko2)
{
    ui->setupUi(this);
    open();
    //connect(ui->page_1, SIGNAL(startMeasurment(StartMeasurment*)), this, SIGNAL(measurement(StartMeasurment*)));
    connect(ui->page_2, &StartMeasurment::startMeasurment, this, &Ko2::measurement);
}

Ko2::~Ko2()
{
    save();
    delete ui;
}

void Ko2::on_calibr1Button_clicked()
{
    //StartMeasurment *sm = ui->page_2;
    emit calibration(StartCalibrationKo2::getStart());
}

void Ko2::calibrationDataCome(int n , double deta)
{
    //один параметр контрольной нормальной плазмы
    QDateTime dt = QDateTime::currentDateTime();
    ui->label_calibrationData->setText(dt.toString("dd.MM.yyyy ") + dt.toString("hh:mm:ss"));
    if(param.count() <= n)
        param.push_back(QString("%1").arg(deta));
    else param.replace(n, QString("%1").arg(deta));
    file.saveKo2(param);
}

void Ko2::open()
{
    file.openKo2(param);
    if( !param.isEmpty() && param.count() >= 10 ) {
        ui->label_calibrationData->setText(param.at(0));
        ui->lineEdit_1->setText(param.at(1));
        ui->lineEdit_2->setText(param.at(2));
        ui->lineEdit_3->setText(param.at(3));
        ui->lineEdit_4->setText(param.at(4));
        ui->lineEdit_5->setText(param.at(5));
    } else
        param = QStringList({0, 0, 0, 0, 0, 0, 0, 0, 0, 0}); //10 параметров
    //connect(ui->page_1, SIGNAL(startMeasurment(StartMeasurment*)), this, SIGNAL(measurement(StartMeasurment*)));
}

void Ko2::save()
{
    //param.clear();
    param.replace(0, ui->label_calibrationData->text());
    param.replace(1, ui->lineEdit_1->text());
    param.replace(2, ui->lineEdit_2->text());
    param.replace(3, ui->lineEdit_3->text());
    param.replace(4, ui->lineEdit_4->text());
    param.replace(5, ui->lineEdit_5->text());
    file.saveKo2(param);
}

void Ko2::calibrationData1Come(double t0)
{
    calibrationDataCome(6, t0);
}

void Ko2::calibrationData2Come(double t0)
{
    calibrationDataCome(7, t0);
}

void Ko2::calibrationData3Come(double t0)
{
    calibrationDataCome(8, t0);
}

void Ko2::calibrationData4Come(double t0)
{
    calibrationDataCome(9, t0);
}

StartMeasurment *StartCalibrationKo2::getStart()
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

void Ko2::on_toolBox_currentChanged(int index)
{
    //open();
}
