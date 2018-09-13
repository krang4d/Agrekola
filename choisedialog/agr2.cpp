#include "agr2.h"
#include "ui_agr2.h"

Agr2::Agr2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Agr2)
{
    ui->setupUi(this);
    ui->page_2->setMode(2);
    file.openAgr2(param);
    if( !param.isEmpty() && param.count() >= 7 ) {
        ui->label_calibrationData->setText(param.at(0));
        ui->lineEdit_1->setText(param.at(1));
        ui->lineEdit_2->setText(param.at(2));
        ui->lineEdit_3->setText(param.at(3));
        ui->lineEdit_4->setText(param.at(4));
        ui->lineEdit_5->setText(param.at(5));
        ui->lineEdit_6->setText(param.at(6));
    } else
        param = QStringList({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    selcalibrAgr1 = new SelectCalibrationAgr1();
    selInductor = new SelectInductor();
    connect(ui->page_2, &StartMeasurment::startMeasurment, this, &Agr2::measurement);
}

Agr2::~Agr2()
{
    //param.clear();
    param.replace(0, ui->label_calibrationData->text());
    param.replace(1, ui->lineEdit_1->text());
    param.replace(2, ui->lineEdit_2->text());
    param.replace(3, ui->lineEdit_3->text());
    param.replace(4, ui->lineEdit_4->text());
    param.replace(5, ui->lineEdit_5->text());
    param.replace(6, ui->lineEdit_6->text());
    file.saveAgr2(param);
    //delete kalibragr2;
    delete selInductor;
    delete selcalibrAgr1;
    delete ui;
}

void Agr2::on_calibrButton_clicked()
{
    //kalibragr2 = new KalibrAgr2();
    //kalibragr2->show();
    emit calibration(ui->page_2);
}


void Agr2::calibrationDataCome(int n, double deta)
{
    //один параметр контрольной нормальной плазмы
    QDateTime dt = QDateTime::currentDateTime();
    ui->label_calibrationData->setText(dt.toString("dd.MM.yyyy ") + dt.toString("hh:mm:ss"));
    if(param.count() <= n)
        param.push_back(QString("%1").arg(deta));
    else param.replace(n, QString("%1").arg(deta));
    file.saveAgr2(param);
}

void Agr2::calibrationData1Come(double t0)
{
    calibrationDataCome(7, t0);
}

void Agr2::calibrationData2Come(double t0)
{
    calibrationDataCome(8, t0);
}

void Agr2::calibrationData3Come(double t0)
{
    calibrationDataCome(9, t0);
}

void Agr2::calibrationData4Come(double t0)
{
    calibrationDataCome(10, t0);
}

StartMeasurment *StartCalibrationAgr2::getStart()
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
