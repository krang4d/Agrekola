#include "agr1.h"
#include "ui_agr1.h"

Agr1::Agr1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Agr1)
{
    ui->setupUi(this);
    open();
    //connect(ui->page_2, &StartMeasurment::startMeasurment, this, &Agr1::measurement);
}

Agr1::~Agr1()
{
    save();
    delete ui;
}

void Agr1::on_pushButton_test_clicked()
{
    t_agr1.setK1(ui->checkBox_testCh1->isChecked());
    t_agr1.setK2(ui->checkBox_testCh2->isChecked());
    t_agr1.setK3(ui->checkBox_testCh3->isChecked());
    t_agr1.setK4(ui->checkBox_testCh4->isChecked());

    t_agr1.setNum1(ui->lineEdit_testCh1->text());
    t_agr1.setNum2(ui->lineEdit_testCh2->text());
    t_agr1.setNum3(ui->lineEdit_testCh3->text());
    t_agr1.setNum4(ui->lineEdit_testCh4->text());

    t_agr1.setSingle(ui->radioButton_testSingle->isChecked());

    c_agr1.setIncube_time(ui->doubleSpinBox_calibIncubeTime_1->value());
    c_agr1.setIncube_time_2(ui->doubleSpinBox_calibIncubeTime_2->value());
    c_agr1.setWrite_time(ui->doubleSpinBox_calibWriteTime->value());

    t_agr1.save();
    t_agr1.save();
}

void Agr1::open()
{
//    ui->page_2->setMode(1);
//    file.openAgr1(param);
//    if( !param.isEmpty() && param.count() >= 7 ) { //7 парамеьров
//        ui->lineEdit_1->setText(param.at(0));
//        ui->lineEdit_2->setText(param.at(1));
//        ui->lineEdit_3->setText(param.at(2));
//    } else
//        param = QStringList({0, 0, 0, 0, 0, 0, 0});
    if( t_agr1.getSingle() ) {
        ui->radioButton_testSingle->setChecked(true);
    }
    else {
        ui->radioButton_testDouble->setChecked(true);
    }

    if( t_agr1.getK1() ) {
        ui->checkBox_testCh1->setChecked(true);
        ui->lineEdit_testCh1->setText(t_agr1.getNum1());
    }
    else {
        ui->checkBox_testCh1->setChecked(false);
    }

    if( t_agr1.getK2() ) {
        ui->checkBox_testCh2->setChecked(true);
        ui->lineEdit_testCh2->setText(t_agr1.getNum2());
    }
    else {
        ui->checkBox_testCh2->setChecked(false);
    }

    if( t_agr1.getK3() ) {
        ui->checkBox_testCh3->setChecked(true);
        ui->lineEdit_testCh3->setText(t_agr1.getNum3());

    }
    else {
        ui->checkBox_testCh3->setChecked(false);
    }

    if( t_agr1.getK4() ) {
        ui->checkBox_testCh4->setChecked(true);
        ui->lineEdit_testCh4->setText(t_agr1.getNum4());

    }
    else {
        ui->checkBox_testCh4->setChecked(false);
    }

    ui->doubleSpinBox_calibIncubeTime_1->setValue(c_agr1.getIncube_time());
    ui->doubleSpinBox_calibIncubeTime_2->setValue(c_agr1.getIncube_time_2());
    ui->doubleSpinBox_calibWriteTime->setValue(c_agr1.getWrite_time());
}

void Agr1::save()
{
    //param.clear();
//    param.replace(0, ui->lineEdit_1->text());
//    param.replace(1, ui->lineEdit_2->text());
//    param.replace(2, ui->lineEdit_3->text());
//    file.saveAgr1(param);
}

void Agr1::calibrationDataCome(int n, double deta)
{
    //один параметр контрольной нормальной плазмы
//    QDateTime dt = QDateTime::currentDateTime();
//    //ui->label_calibrationData->setText(dt.toString("dd.MM.yyyy ") + dt.toString("hh:mm:ss"));
//    if(param.count() <= n)
//        param.push_back(QString("%1").arg(deta));
//    else param.replace(n, QString("%1").arg(deta));
//    file.saveAgr1(param);
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

void Agr1::on_radioButton_testSingle_toggled(bool checked)
{
    if(ui->radioButton_testDouble->isChecked()) {
        ui->checkBox_testCh2->setEnabled(false);
        ui->checkBox_testCh4->setEnabled(false);
        ui->lineEdit_testCh2->setEnabled(false);
        ui->lineEdit_testCh4->setEnabled(false);
        ui->lineEdit_testCh2->setText(ui->lineEdit_testCh1->text());
        ui->lineEdit_testCh4->setText(ui->lineEdit_testCh3->text());

        if(ui->checkBox_testCh1->isChecked()) ui->checkBox_testCh2->setChecked(true);
        else ui->checkBox_testCh2->setChecked(false);
        if(ui->checkBox_testCh3->isChecked()) ui->checkBox_testCh4->setChecked(true);
        else ui->checkBox_testCh4->setChecked(false);
    }
    if(ui->radioButton_testSingle->isChecked()) {
        ui->checkBox_testCh2->setEnabled(true);
        ui->checkBox_testCh4->setEnabled(true);
        ui->lineEdit_testCh2->setEnabled(ui->checkBox_testCh2->isChecked());
        ui->lineEdit_testCh4->setEnabled(ui->checkBox_testCh4->isChecked());
    }
}

void Agr1::on_checkBox_testCh1_toggled(bool checked)
{
    ui->lineEdit_testCh1->setEnabled(checked);
    if( ui->radioButton_testDouble->isChecked())
        ui->checkBox_testCh2->setChecked(checked);
}

void Agr1::on_checkBox_testCh2_toggled(bool checked)
{
    if(ui->radioButton_testSingle->isChecked())
            ui->lineEdit_testCh2->setEnabled(checked);
}

void Agr1::on_checkBox_testCh3_toggled(bool checked)
{
    ui->lineEdit_testCh3->setEnabled(checked);
    if(ui->radioButton_testDouble->isChecked())
        ui->checkBox_testCh4->setChecked(checked);
}

void Agr1::on_checkBox_testCh4_toggled(bool checked)
{
    if( ui->radioButton_testSingle->isChecked() )
        ui->lineEdit_testCh4->setEnabled(checked);
}

void Agr1::on_lineEdit_testCh1_textChanged(const QString &arg1)
{
    if(ui->radioButton_testDouble->isChecked())
        ui->lineEdit_testCh2->setText(arg1);
}

void Agr1::on_lineEdit_testCh3_textChanged(const QString &arg1)
{
    if(ui->radioButton_testDouble->isChecked())
        ui->lineEdit_testCh4->setText(arg1);
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

StartMeasurment *StartCalibrationAgr1::getBTP100()
{
    StartMeasurment *sm = new StartMeasurment(0);
    sm->setChannels(true, true, true, true);
    sm->setNum(1, "БТП");
    sm->setNum(2, "БТП");
    sm->setNum(3, "БТП");
    sm->setNum(4, "БТП");
    sm->setTime(10);
    sm->setTimeIncube(1, 3);
    return sm;
}

StartMeasurment *StartCalibrationAgr1::getOTP0()
{
    StartMeasurment *sm = new StartMeasurment(0);
    sm->setChannels(true, true, true, true);
    sm->setNum(1, "ОТП");
    sm->setNum(2, "ОТП");
    sm->setNum(3, "ОТП");
    sm->setNum(4, "ОТП");
    sm->setTime(10);
    sm->setTimeIncube(1, 3);
    return sm;
}
