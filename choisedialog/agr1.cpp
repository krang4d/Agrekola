#include "agr1.h"
#include "ui_agr1.h"

Agr1::Agr1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Agr1)
{
    ui->setupUi(this);
    ui->page_2->setMode(1);
    file.openAgr1(param);
    if( !param.isEmpty() && param.count() >= 3 ) { //3 парамеьра
        ui->lineEdit_1->setText(param.at(0));
        ui->lineEdit_2->setText(param.at(1));
        ui->lineEdit_3->setText(param.at(2));
    } else
        param = QStringList({0, 0, 0, 0, 0, 0, 0});
    connect(ui->page_2, &StartMeasurment::startMeasurment, this, &Agr1::measurement);
}

Agr1::~Agr1()
{
    //param.clear();
    param.replace(0, ui->lineEdit_1->text());
    param.replace(1, ui->lineEdit_2->text());
    param.replace(2, ui->lineEdit_3->text());
    file.saveAgr1(param);
    delete ui;
}

void Agr1::on_kolibrButton_clicked()
{
    emit calibration(StartCalibrationAgr1::getStart());
}

void Agr1::calibrationDataCome(int n, double deta)
{
    //один параметр контрольной нормальной плазмы
    QDateTime dt = QDateTime::currentDateTime();
    ui->label_calibrationData->setText(dt.toString("dd.MM.yyyy ") + dt.toString("hh:mm:ss"));
    if(param.count() <= n)
        param.push_back(QString("%1").arg(deta));
    else param.replace(n, QString("%1").arg(deta));
    file.saveAgr1(param);
}

void Agr1::calibrationData1Come(double t0)
{
    calibrationDataCome(3, t0);
}

void Agr1::calibrationData2Come(double t0)
{
    calibrationDataCome(4, t0);
}

void Agr1::calibrationData3Come(double t0)
{
    calibrationDataCome(5, t0);
}

void Agr1::calibrationData4Come(double t0)
{
    calibrationDataCome(6, t0);
}

StartMeasurment *StartCalibrationAgr1::getStart()
{
    StartMeasurment *sm = new StartMeasurment(0);
    sm->setChannels(true, true, true, true);
    sm->setNum(1, "Калибровка");
    sm->setNum(2, "Калибровка");
    sm->setNum(3, "Калибровка");
    sm->setNum(4, "Калибровка");
    sm->setTime(10);
    sm->setTimeIncube(1, 3);
    sm->setTimeIncube(2, 4);
    //stKo2->cancel = false;
    return sm;
}
