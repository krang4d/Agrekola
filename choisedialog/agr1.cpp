#include "agr1.h"
#include "ui_agr1.h"
#include "typeinfo"

Agr1::Agr1(QWidget *parent) :
    QWidget(parent),
    c_agr1(new CalibrationAgr1),
    t_agr1(new TestAgr1),
    ui(new Ui::Agr1)
{
    ui->setupUi(this);
    open();
}

void Agr1::setTab(int i)
{
    ui->tabWidget->setCurrentIndex(i);
}

Agr1::~Agr1()
{
    close();
    delete t_agr1;
    delete c_agr1;
    delete ui;
}

void Agr1::on_pushButton_calib_clicked()
{
    bool a, b, c, d;
    if(ui->checkBox_calibCh1->isChecked()) a = true;
    else a = false;
    if(ui->checkBox_calibCh2->isChecked()) b = true;
    else b = false;
    if(ui->checkBox_calibCh3->isChecked()) c = true;
    else c = false;
    if(ui->checkBox_calibCh4->isChecked()) d = true;
    else d = false;

    bool e = !ui->lineEdit_calibTrombotsitSerial->text().isEmpty();

    //bool c = (ui->doubleSpinBox_testIncubeTime->value() != NULL) && (ui->doubleSpinBox_testWriteTime->value() != NULL);
    if( !((a || b || c || d ) && e ) ) {
        QMessageBox::information(this, "Внимание!", "Для того чтобы продолжить необходимо выбрать рабочие каналы и заполнить все поля с параметрами!");
        return;
    }

    QDate now = QDate::currentDate();
    bool f = now <= ui->dateEdit_calibTrombotsit->date();

    if(!(f) ) {
        QMessageBox::information(this, "Внимание!", "Проверьте срок годности используемых реагентов!");
        return;
    }

    c_agr1->setDate(QDate::currentDate());
    c_agr1->setTrombotsit_date(ui->dateEdit_calibTrombotsit->date());
    c_agr1->setTrombotsit_serial(ui->lineEdit_calibTrombotsitSerial->text());
    c_agr1->setTrombotsit_concentration(ui->doubleSpinBox_calibTrombotsit->value());
    c_agr1->setIncube_time(ui->doubleSpinBox_calibIncubeTime->value());
    c_agr1->setWrite_time(ui->doubleSpinBox_calibWriteTime->value());

    c_agr1->setK1(ui->checkBox_calibCh1->isChecked());
    c_agr1->setK2(ui->checkBox_calibCh2->isChecked());
    c_agr1->setK3(ui->checkBox_calibCh3->isChecked());
    c_agr1->setK4(ui->checkBox_calibCh4->isChecked());
    c_agr1->save();
    emit calibration(StartCalibrationAgr1::getStart(c_agr1));
}

void Agr1::on_pushButton_test_clicked()
{  
    bool a, b, c, d;
    if(ui->checkBox_testCh1->isChecked()) {
        if(!ui->lineEdit_testCh1->text().isEmpty()) a = true;
        else a = false;
    }
    else a = true;
    if(ui->checkBox_testCh2->isChecked()) {
        if(!ui->lineEdit_testCh2->text().isEmpty()) b = true;
        else b = false;
    }
    else b = true;
    if(ui->checkBox_testCh3->isChecked()) {
        if(!ui->lineEdit_testCh3->text().isEmpty()) c = true;
        else b = false;
    }
    else c = true;
    if(ui->checkBox_testCh4->isChecked()) {
        if(!ui->lineEdit_testCh4->text().isEmpty()) d = true;
        else d = false;
    }
    else d = true;

    bool e = ui->checkBox_testCh1->isChecked() || ui->checkBox_testCh2->isChecked()
            || ui->checkBox_testCh3->isChecked() || ui->checkBox_testCh4->isChecked();

    if (  !( a && b && c && d && e ) ) {
        QMessageBox::information(this,"Внимание!","Для того чтобы продолжить необходимо"
                                                  " выбрать рабочие каналы и заполнить"
                                                  " все поля с параметрами.");
        return;
    }

    bool f = c_agr1->getCkA1() || c_agr1->getCkA2() || c_agr1->getCkA3() || c_agr1->getCkA4();
    if( !(!c_agr1->getDate().toString("dd.MM.yyyy").isEmpty() && e) ) {
        //QString str = QString("%1").arg(c_ko2.getDate().toString("dd/MM/yyyy"));
        QMessageBox::information(this, "Внимание!", QString("Для того чтобы продолжить неоходимо провести калибровку."));
        return;
    }
    //bool c = (ui->doubleSpinBox_testIncubeTime->value() != NULL) && (ui->doubleSpinBox_testWriteTime->value() != NULL);
    if ( !(a || b || c || d) ) {
        QMessageBox::information(this, "Внимание!", "Для того чтобы продолжить необходимо выбрать рабочие каналы и заполнить все поля с параметрами.");
        return;
    }
    t_agr1->setK1(ui->checkBox_testCh1->isChecked());
    t_agr1->setK2(ui->checkBox_testCh2->isChecked());
    t_agr1->setK3(ui->checkBox_testCh3->isChecked());
    t_agr1->setK4(ui->checkBox_testCh4->isChecked());

    t_agr1->setNum1(ui->lineEdit_testCh1->text());
    t_agr1->setNum2(ui->lineEdit_testCh2->text());
    t_agr1->setNum3(ui->lineEdit_testCh3->text());
    t_agr1->setNum4(ui->lineEdit_testCh4->text());

    t_agr1->setSingle(ui->radioButton_testSingle->isChecked());
    t_agr1->save();
    emit measurement(StartTestAgr1::getStart(t_agr1));
}

void Agr1::open()
{
    if( t_agr1->getSingle() ) {
        ui->radioButton_testSingle->setChecked(true);
    }
    else {
        ui->radioButton_testDouble->setChecked(true);
    }

    if( t_agr1->getK1() ) {
        ui->checkBox_testCh1->setChecked(true);
        ui->lineEdit_testCh1->setText(t_agr1->getNum1());
    }
    else {
        ui->checkBox_testCh1->setChecked(false);
    }

    if( t_agr1->getK2() ) {
        ui->checkBox_testCh2->setChecked(true);
        ui->lineEdit_testCh2->setText(t_agr1->getNum2());
    }
    else {
        ui->checkBox_testCh2->setChecked(false);
    }

    if( t_agr1->getK3() ) {
        ui->checkBox_testCh3->setChecked(true);
        ui->lineEdit_testCh3->setText(t_agr1->getNum3());
    }
    else {
        ui->checkBox_testCh3->setChecked(false);
    }

    if( t_agr1->getK4() ) {
        ui->checkBox_testCh4->setChecked(true);
        ui->lineEdit_testCh4->setText(t_agr1->getNum4());
    }
    else {
        ui->checkBox_testCh4->setChecked(false);
    }
    ui->groupBox_testCalib->setTitle(QString("Последняя калибровка: %1\n").arg(c_agr1->getDate().toString("dd.MM.yyyy")));
    QString str = QString("Номер серия тромбоцитов %1\n").arg(c_agr1->getTrombotsit_serial())
                + QString("Срок годности тромбоцитов %1\n").arg(c_agr1->getTrombotsit_date().toString("dd.MM.yyyy"))
                + QString("Концентрация тромбоцитов в калибровочном растворе %1 (тромбоцитов/мкл)").arg(c_agr1->getTrombotsit_concentration());
    ui->label_testCalibString->setText(str);
//    ui->doubleSpinBox_calibIncubeTime_1->setValue(c_agr1->getIncube_time());
//    ui->doubleSpinBox_calibIncubeTime_2->setValue(c_agr1->getIncube_time_2());
    ui->doubleSpinBox_calibWriteTime->setValue(c_agr1->getWrite_time());
    ui->doubleSpinBox_calibIncubeTime->setValue(c_agr1->getIncube_time());
    ui->doubleSpinBox_calibTrombotsit->setValue(c_agr1->getTrombotsit_concentration());
    ui->lineEdit_calibTrombotsitSerial->setText(c_agr1->getTrombotsit_serial());
    ui->dateEdit_calibTrombotsit->setDate(c_agr1->getTrombotsit_date());
}

void Agr1::close()
{
    t_agr1->save();
    c_agr1->save();
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

QString Agr1::t_print()
{
    return t_agr1->print();
}

void Agr1::setT1(double value)
{
    t_agr1->setT1(value);
}

void Agr1::setT2(double value)
{
    t_agr1->setT2(value);
}

void Agr1::setT3(double value)
{
    t_agr1->setT3(value);
}

void Agr1::setT4(double value)
{
    t_agr1->setT4(value);
}

QString Agr1::c_print()
{
    return c_agr1->print();
}

void Agr1::calibrationData1Come(double value)
{
    c_agr1->setCkA1(value);
}

void Agr1::calibrationData2Come(double value)
{
    c_agr1->setCkA2(value);
}

void Agr1::calibrationData3Come(double value)
{
    c_agr1->setCkA3(value);
}

void Agr1::calibrationData4Come(double value)
{
    c_agr1->setCkA4(value);
}

void Agr1::btp1Come(double value)
{
    c_agr1->setBTP1(value);
}

void Agr1::btp2Come(double value)
{
    c_agr1->setBTP2(value);
}

void Agr1::btp3Come(double value)
{
    c_agr1->setBTP3(value);
}

void Agr1::btp4Come(double value)
{
    c_agr1->setBTP4(value);
}

void Agr1::otp1Come(double value)
{
    c_agr1->setOTP1(value);
}

void Agr1::otp2Come(double value)
{
    c_agr1->setOTP2(value);
}

void Agr1::otp3Come(double value)
{
    c_agr1->setOTP3(value);
}

void Agr1::otp4Come(double value)
{
    c_agr1->setOTP4(value);
}

StartMeasurement *StartCalibrationAgr1::getStart(Calibration *c_agr1)
{
    StartMeasurement *start = new StartMeasurement(0);
    start->setChannels(c_agr1->getK1(), c_agr1->getK2(), c_agr1->getK3(), c_agr1->getK4());
    start->setNum(1, "к/плазма");
    start->setNum(2, "к/плазма");
    start->setNum(3, "к/плазма");
    start->setNum(4, "к/плазма");
    start->setTimeWrite(c_agr1->getWrite_time());
    start->setTimeIncube(1, c_agr1->getIncube_time());
    start->setTimeIncube(2, static_cast<CalibrationAgr1*>(c_agr1)->getIncube_time_2());
    start->setModeID(CalibAgr1_ID);
    return start;
}

//StartMeasurement *StartCalibrationAgr1::getBTP()
//{
//    StartMeasurement *start = new StartMeasurement(0);
//    start->setChannels(true, true, true, true);
//    start->setNum(1, "БТП");
//    start->setNum(2, "БТП");
//    start->setNum(3, "БТП");
//    start->setNum(4, "БТП");
//    start->setTimeWrite(10);
//    start->setTimeIncube(1, 3);
//    start->setModeID(BTPCalibAgr1_ID);
//    return start;
//}

//StartMeasurement *StartCalibrationAgr1::getOTP()
//{
//    StartMeasurement *start = new StartMeasurement(0);
//    start->setChannels(true, true, true, true);
//    start->setNum(1, "ОТП");
//    start->setNum(2, "ОТП");
//    start->setNum(3, "ОТП");
//    start->setNum(4, "ОТП");
//    start->setTimeWrite(10);
//    start->setTimeIncube(1, 3);
//    start->setTimeIncube(2, 4);
//    start->setModeID(OTPCalibAgr1_ID);
//    return start;
//}

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
    start->setTimeWrite(t_agr1->getWriteTime());
    start->setTimeIncube(1, t_agr1->getIncubeTime());
    start->setTimeIncube(2, obj->getIncubeTime2());
    start->setProbe(t_agr1->getSingle());
    start->setModeID(TestAgr1_ID);
    return start;
}
