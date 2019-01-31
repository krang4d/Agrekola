#include "agr1.h"
#include "ui_agr1.h"
#include "typeinfo"

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

    c_agr1.save();
    t_agr1.save();
    emit measurement(StartTestAgr1::getStart(&t_agr1));
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
//    один параметр контрольной нормальной плазмы
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

StartMeasurement *StartCalibrationAgr1::getStart(Calibration *c_agr1)
{
    StartMeasurement *start = new StartMeasurement(0);
    start->setChannels(c_agr1->getK1(), c_agr1->getK2(), c_agr1->getK3(), c_agr1->getK4());
    start->setNum(1, "Калибровка");
    start->setNum(2, "Калибровка");
    start->setNum(3, "Калибровка");
    start->setNum(4, "Калибровка");
    start->setTime(c_agr1->getWrite_time());
    start->setTimeIncube(1, c_agr1->getIncube_time());
    start->setTimeIncube(2, static_cast<CalibrationAgr1*>(c_agr1)->getIncube_time_2());
    //stKo2->cancel = false;
    return start;
}

StartMeasurement *StartCalibrationAgr1::getBTP100()
{
    StartMeasurement *start = new StartMeasurement(0);
    start->setChannels(true, true, true, true);
    start->setNum(1, "БТП");
    start->setNum(2, "БТП");
    start->setNum(3, "БТП");
    start->setNum(4, "БТП");
    start->setTime(10);
    start->setTimeIncube(1, 3);
    start->setModeID(Level_ID);
    return start;
}

StartMeasurement *StartCalibrationAgr1::getOTP0()
{
    StartMeasurement *start = new StartMeasurement(0);
    start->setChannels(true, true, true, true);
    start->setNum(1, "ОТП");
    start->setNum(2, "ОТП");
    start->setNum(3, "ОТП");
    start->setNum(4, "ОТП");
    start->setTime(10);
    start->setTimeIncube(1, 3);
    start->setModeID(Level_ID);
    return start;
}

StartMeasurement *StartTestAgr1::getStart(Test* t_agr1)
{
    //static_cast<CalibrationAgr1>(c_agr1).getIncube_time_2()
    TestAgr1* obj = nullptr;
    if(typeid(*t_agr1) == typeid(TestAgr1)) {
        obj = dynamic_cast<TestAgr1*>(t_agr1);
        qDebug() << QString("c_agr1 get pointer to an object of type: true, incube_time2 is %1").arg(obj->getIncubeTime2());
    }
    else {
        throw Error_Agr1_Type_ID("c_agr1 get pointer to an object of type: false");
    }
    StartMeasurement *start = new StartMeasurement(0);
    start->setChannels(t_agr1->getK1(), t_agr1->getK2(), t_agr1->getK3(), t_agr1->getK4());
    start->setNum(1, t_agr1->getNum1());
    start->setNum(2, t_agr1->getNum2());
    start->setNum(3, t_agr1->getNum3());
    start->setNum(4, t_agr1->getNum4());
    start->setTime(t_agr1->getWriteTime());
    start->setTimeIncube(1, t_agr1->getIncubeTime());
    start->setTimeIncube(2, obj->getIncubeTime2());
    start->setProbe(t_agr1->getSingle());
    start->setModeID(TestAgr1_ID);
    return start;
}
