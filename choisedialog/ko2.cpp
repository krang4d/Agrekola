#include "ko2.h"
#include "ui_ko2.h"
#include <QDateTime>
#include <QDate>

Ko2::Ko2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ko2)
{
    ui->setupUi(this);
    open();
    //connect(ui->page_1, SIGNAL(startMeasurment(StartMeasurment*)), this, SIGNAL(measurement(StartMeasurment*)));
    //connect(ui->page_2, &StartMeasurment::startMeasurment, this, &Ko2::measurement);
}

Ko2::~Ko2()
{
    close();
    delete ui;
}

void Ko2::on_toolBox_currentChanged(int index)
{
    //open();
}

void Ko2::calibrationDataCome(int n , double deta)
{
    static int i = 0;
    //один параметр контрольной нормальной плазмы
    QDate dt = QDate::currentDate();
    c_ko2.setDate(dt);
    c_ko2.save();
    //ui->label_calibrationData->setText(dt.toString("dd.MM.yyyy ") + dt.toString("hh:mm:ss"));
//    if(param.count() <= n)
//        param.push_back(QString("%1").arg(deta));
//    else param.replace(n, QString("%1").arg(deta));
    //file.saveKo2(param);
}

void Ko2::open()
{

/* Старый метод загрузки параметов из TXT*/
//    file.openKo2(param);
//    if( !param.isEmpty() && param.count() >= 10 ) {
//        //ui->label_calibrationData->setText(param.at(0));
//        ui->lineEdit_1->setText(param.at(1));
//        //ui->lineEdit_2->setText(param.at(2));
//        ui->lineEdit_3->setText(param.at(3));
//        //ui->lineEdit_4->setText(param.at(4));
//        //ui->lineEdit_5->setText(param.at(5));
//    } else
//        param = QStringList({0, 0, 0, 0, 0, 0, 0, 0, 0, 0}); //10 параметров
/* Новый метод загрузки параметров из XML */
    QString str = QString("Номер серия реагентов %1\nСрок годности реагентов %2")
            .arg(c_ko2.getReagent_serial())
            .arg(c_ko2.getReagent_date().toString("dd.MM.yyyy"));
    ui->label_test1CalibString->setText(str);
    //connect(ui->page_1, SIGNAL(startMeasurment(StartMeasurment*)),this, SIGNAL(measurement(StartMeasurment*)));
}

void Ko2::close()
{
    //param.clear();
    //param.replace(0, ui->label_calibrationData->text());
    //param.replace(1, ui->lineEdit_1->text());
    //param.replace(2, ui->lineEdit_2->text());
    //param.replace(3, ui->lineEdit_3->text());
    //param.replace(4, ui->lineEdit_4->text());
    //param.replace(5, ui->lineEdit_5->text());
    //file.saveKo2(param);
}

void Ko2::calibrationData1Come(double t0)
{
    c_ko2.setA4tv_kp1(t0);
    calibrationDataCome(1, t0);
}

void Ko2::calibrationData2Come(double t0)
{
    c_ko2.setA4tv_kp2(t0);
    calibrationDataCome(2, t0);
}

void Ko2::calibrationData3Come(double t0)
{
    c_ko2.setA4tv_kp3(t0);
    calibrationDataCome(3, t0);
}

void Ko2::calibrationData4Come(double t0)
{
    c_ko2.setA4tv_kp4(t0);
    calibrationDataCome(4, t0);
}

void Ko2::on_pushButton_calib1_clicked()
{
    c_ko2.setDate(QDate::currentDate());
    qDebug() << "Дата " << c_ko2.getDate().toString("dd.MM.yyyy");
    c_ko2.setReagent_date(ui->dateEdit_calibReagent->date());
    qDebug() << "Дата реагентов " << c_ko2.getReagent_date().toString("dd.MM.yyyy");
    c_ko2.setReagent_serial(ui->lineEdit_calibReagentSerial->text());
    qDebug() << "Серия реагентов" << c_ko2.getReagent_serial();
    c_ko2.save();
    emit calibration(StartCalibrationKo2::getStart());
}

StartMeasurment *StartTestKo2::getStart()
{
    StartMeasurment *sm = new StartMeasurment(0);
    sm->setChannels(true, true, true, true);
    sm->setNum(1, "Измерение");
    sm->setNum(2, "Измерение");
    sm->setNum(3, "Измерение");
    sm->setNum(4, "Измерение");
    sm->setTime(10);
    sm->setTimeIncube(1, 3);
    //stKo2->cancel = false;
    return sm;
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
