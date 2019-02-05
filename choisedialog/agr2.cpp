#include "agr2.h"
#include "ui_agr2.h"

Agr2::Agr2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Agr2)
{
    ui->setupUi(this);
    open();
//    selcalibrAgr1 = new SelectCalibrationAgr1();
//    selInductor = new SelectInductor();
//    connect(ui->page_2, &StartMeasurment::startMeasurment, this, &Agr2::measurement);
}

Agr2::~Agr2()
{
    save();
    delete ui;
}

void Agr2::calibrationDataCome(int n, double deta)
{
//  один параметр контрольной нормальной плазмы
    QDateTime dt = QDateTime::currentDateTime();
//    ui->label_calibrationData->setText(dt.toString("dd.MM.yyyy ") + dt.toString("hh:mm:ss"));
//    if(param.count() <= n)
//        param.push_back(QString("%1").arg(deta));
//    else param.replace(n, QString("%1").arg(deta));
//    file.saveAgr2(param);
}

void Agr2::open()
{
//    file.openAgr2(param);
//    if( !param.isEmpty() && param.count() >= 11 ) {
        //ui->label_calibrationData->setText(param.at(0));
//        ui->lineEdit_1->setText(param.at(1));
//        ui->lineEdit_2->setText(param.at(2));
//        ui->lineEdit_3->setText(param.at(3));
//        ui->lineEdit_4->setText(param.at(4));
//        ui->lineEdit_5->setText(param.at(5));
//        ui->lineEdit_6->setText(param.at(6));
//    } else
//        param = QStringList({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    QString str;
        str = QString("Дата проведения %1\n").arg(c_agr2.getDate().toString("dd.MM.yyyy"))
            + QString("Номер серия реагентов %1\n").arg(c_agr2.getReagent_serial())
            + QString("Срок годности реагентов %1\n").arg(c_agr2.getReagent_date().toString("dd.MM.yyyy"));
    ui->label_testCalibString->setText(str);

    if( t_agr2.getSingle() ) {
        ui->radioButton_testSingle->setChecked(true);
    }
    else {
        ui->radioButton_testDouble->setChecked(true);
    }

    if( t_agr2.getK1() ) {
        ui->checkBox_testCh1->setChecked(true);
        ui->lineEdit_testCh1->setText(t_agr2.getNum1());
    }
    else {
        ui->checkBox_testCh1->setChecked(false);
    }

    if( t_agr2.getK2() ) {
        ui->checkBox_testCh2->setChecked(true);
        ui->lineEdit_testCh2->setText(t_agr2.getNum2());
    }
    else {
        ui->checkBox_testCh2->setChecked(false);
    }

    if( t_agr2.getK3() ) {
        ui->checkBox_testCh3->setChecked(true);
        ui->lineEdit_testCh3->setText(t_agr2.getNum3());

    }
    else {
        ui->checkBox_testCh3->setChecked(false);
    }

    if( t_agr2.getK4() ) {
        ui->checkBox_testCh4->setChecked(true);
        ui->lineEdit_testCh4->setText(t_agr2.getNum4());

    }
    else {
        ui->checkBox_testCh4->setChecked(false);
    }

    ui->checkBox_calibCh1->setChecked(c_agr2.getK1());
    ui->checkBox_calibCh2->setChecked(c_agr2.getK2());
    ui->checkBox_calibCh3->setChecked(c_agr2.getK3());
    ui->checkBox_calibCh4->setChecked(c_agr2.getK4());

    ui->doubleSpinBox_calibIncubeTime_1->setValue(c_agr2.getIncube_time());
    ui->doubleSpinBox_calibIncubeTime_2->setValue(c_agr2.getIncube_time_2());
    ui->doubleSpinBox_calibWriteTime->setValue(c_agr2.getWrite_time());
    ui->doubleSpinBox_calibVillebrand->setValue(c_agr2.getK_plazma());
    ui->dateEdit_calibKPlazma->setDate(c_agr2.getK_plazma_date());
    ui->lineEdit_calibKPlazmaSerial->setText(c_agr2.getK_plazma_serial());
    ui->dateEdit_calibReagent->setDate(c_agr2.getReagent_date());
    ui->lineEdit_calibReagentSerial->setText(c_agr2.getReagent_serial());
}

void Agr2::save()
{
//    param.clear();
//    param.replace(0, ui->label_calibrationData->text());
//    param.replace(1, ui->lineEdit_1->text());
//    param.replace(2, ui->lineEdit_2->text());
//    param.replace(3, ui->lineEdit_3->text());
//    param.replace(4, ui->lineEdit_4->text());
//    param.replace(5, ui->lineEdit_5->text());
//    param.replace(6, ui->lineEdit_6->text());
//    file.saveAgr2(param);

    c_agr2.setIncube_time(ui->doubleSpinBox_calibIncubeTime_1->value());
    c_agr2.setIncube_time_2(ui->doubleSpinBox_calibIncubeTime_2->value());
    c_agr2.setWrite_time(ui->doubleSpinBox_calibWriteTime->value());
    c_agr2.setK_plazma(ui->doubleSpinBox_calibVillebrand->value());
    c_agr2.setK_plazma_date(ui->dateEdit_calibKPlazma->date());
    c_agr2.setK_plazma_serial(ui->lineEdit_calibKPlazmaSerial->text());
    c_agr2.setReagent_date(ui->dateEdit_calibReagent->date());
    c_agr2.setReagent_serial(ui->lineEdit_calibReagentSerial->text());
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

void Agr2::on_pushButton_calib_clicked()
{
    c_agr2.setDate(QDate::currentDate());
    c_agr2.setReagent_date(ui->dateEdit_calibReagent->date());
    c_agr2.setReagent_serial(ui->lineEdit_calibReagentSerial->text());
    c_agr2.setK_plazma_date(ui->dateEdit_calibKPlazma->date());
    //c_agr2.setK_plazma_serial(ui->lineEdit_calibKPlazmaNum->text());
    //c_agr2.setIncube_time(ui->doubleSpinBox_calibIncubeTime_1->value());
    c_agr2.setWrite_time(ui->doubleSpinBox_calibWriteTime->value());
    c_agr2.setIncube_time_2(ui->doubleSpinBox_calibIncubeTime_2->value());

    c_agr2.setK1(ui->checkBox_calibCh1->isChecked());
    c_agr2.setK2(ui->checkBox_calibCh2->isChecked());
    c_agr2.setK3(ui->checkBox_calibCh3->isChecked());
    c_agr2.setK4(ui->checkBox_calibCh4->isChecked());

    c_agr2.save();
    emit calibration(StartCalibrationAgr2::getStart(&c_agr2));
}

void Agr2::on_pushButton_test_clicked()
{
    t_agr2.setK1(ui->checkBox_testCh1->isChecked());
    t_agr2.setK2(ui->checkBox_testCh2->isChecked());
    t_agr2.setK3(ui->checkBox_testCh3->isChecked());
    t_agr2.setK4(ui->checkBox_testCh4->isChecked());

    t_agr2.setNum1(ui->lineEdit_testCh1->text());
    t_agr2.setNum2(ui->lineEdit_testCh2->text());
    t_agr2.setNum3(ui->lineEdit_testCh3->text());
    t_agr2.setNum4(ui->lineEdit_testCh4->text());

    t_agr2.setSingle(ui->radioButton_testSingle->isChecked());

    t_agr2.save();
    emit measurement(StartTestAgr2::getStart(&t_agr2));
}

void Agr2::on_radioButton_testSingle_toggled(bool checked)
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

void Agr2::on_checkBox_testCh1_toggled(bool checked)
{
    ui->lineEdit_testCh1->setEnabled(checked);
    if( ui->radioButton_testDouble->isChecked())
        ui->checkBox_testCh2->setChecked(checked);
}

void Agr2::on_checkBox_testCh2_toggled(bool checked)
{
    if(ui->radioButton_testSingle->isChecked())
            ui->lineEdit_testCh2->setEnabled(checked);
}

void Agr2::on_checkBox_testCh3_toggled(bool checked)
{
    ui->lineEdit_testCh3->setEnabled(checked);
    if(ui->radioButton_testDouble->isChecked())
        ui->checkBox_testCh4->setChecked(checked);
}

void Agr2::on_checkBox_testCh4_toggled(bool checked)
{
    if( ui->radioButton_testSingle->isChecked() )
        ui->lineEdit_testCh4->setEnabled(checked);
}

void Agr2::on_lineEdit_testCh1_textChanged(const QString &arg1)
{
    if(ui->radioButton_testDouble->isChecked())
        ui->lineEdit_testCh2->setText(arg1);
}

void Agr2::on_lineEdit_testCh3_textChanged(const QString &arg1)
{
    if(ui->radioButton_testDouble->isChecked())
        ui->lineEdit_testCh4->setText(arg1);
}

StartMeasurement *StartCalibrationAgr2::getStart(Calibration* c_agr2)
{
    CalibrationAgr2* obj = nullptr;
    if(typeid(*c_agr2) == typeid(CalibrationAgr2)) {
        obj = dynamic_cast<CalibrationAgr2*>(c_agr2);
        qDebug() << QString("c_agr2 get pointer to an object of type: true, incube_time2 is %1")
                    .arg(obj->getIncube_time_2());
    }
    else {
        throw Error_Agr2_Type_ID("c_agr2 get pointer to an object of type: false");
    }

    StartMeasurement *start = new StartMeasurement(0);
    start->setChannels(c_agr2->getK1(), c_agr2->getK2(), c_agr2->getK3(), c_agr2->getK4());
    start->setNum(1, "Калибровка");
    start->setNum(2, "Калибровка");
    start->setNum(3, "Калибровка");
    start->setNum(4, "Калибровка");
    start->setTimeWrite(c_agr2->getWrite_time());
    start->setTimeIncube(1, c_agr2->getIncube_time());
    start->setTimeIncube(2, obj->getIncube_time_2());
    //stKo2->cancel = false;
    return start;
}

StartMeasurement *StartTestAgr2::getStart(Test* t_agr2)
{
    TestAgr2* obj = nullptr;
    if(typeid(*t_agr2) == typeid(TestAgr2)) {
        obj = dynamic_cast<TestAgr2*>(t_agr2);
        qDebug() << QString("t_agr2 get pointer to an object of type: true, incube_time2 is %1")
                    .arg(obj->getIncubeTime2());
    }
    else {
        throw Error_Agr2_Type_ID("t_agr2 get pointer to an object of type: false");
    }

    StartMeasurement *start = new StartMeasurement(0);
    start->setChannels(t_agr2->getK1(), t_agr2->getK2(), t_agr2->getK3(), t_agr2->getK4());
    start->setNum(1, t_agr2->getNum1());
    start->setNum(2, t_agr2->getNum2());
    start->setNum(3, t_agr2->getNum3());
    start->setNum(4, t_agr2->getNum4());
    start->setTimeWrite(t_agr2->getWriteTime());
    start->setProbe(obj->getIncubeTime2());
    start->setTimeIncube(1, t_agr2->getIncubeTime());
    start->setTimeIncube(2, obj->getIncubeTime2());
    return start;
}
