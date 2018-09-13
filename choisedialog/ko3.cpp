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
    } else
        param = QStringList({0, 0, 0, 0, 0, 0, 0, 0}); //8 параметров
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

void Ko3::on_calibr1Button_clicked()
{
    emit calibration(StartCalibrationKo3::getStart());
}

void Ko3::calibrationDataCome(int n, double deta)
{
    //один параметр контрольной нормальной плазмы
    QDateTime dt = QDateTime::currentDateTime();
    ui->label_calibrationData->setText(dt.toString("dd.MM.yyyy ") + dt.toString("hh:mm:ss"));
    if(param.count() <= n)
        param.push_back(QString("%1").arg(deta));
    else param.replace(n, QString("%1").arg(deta));
    file.saveKo2(param);
}

void Ko3::calibrationData1Come(double t0)
{
    //при разведении 200% контрольной нормальной плазмы
    calibrationDataCome(4, t0);
}

void Ko3::calibrationData2Come(double t0)
{
    //при разведении 100% контрольной нормальной плазмы
    calibrationDataCome(5, t0);
}

void Ko3::calibrationData3Come(double t0)
{
    //при разведении 50% контрольной нормальной плазмы
    calibrationDataCome(6, t0);
}

void Ko3::calibrationData4Come(double t0)
{
    //при разведении 25% контрольной нормальной плазмы
    calibrationDataCome(7, t0);
}

StartMeasurment *StartCalibrationKo3::getStart()
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
