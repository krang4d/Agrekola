#include "agr2.h"
#include "ui_agr2.h"

Agr2::Agr2(QWidget *parent) :
    QWidget(parent),
    c_agr2(new CalibrationAgr2),
    t_agr2(new TestAgr2),
    ui(new Ui::Agr2)
{
    ui->setupUi(this);
    open();
//    selcalibrAgr1 = new SelectCalibrationAgr1();
//    selInductor = new SelectInductor();
//    connect(ui->page_2, &StartMeasurment::startMeasurment, this, &Agr2::measurement);
}

void Agr2::setTab(int i)
{
    ui->tabWidget->setCurrentIndex(i);
}

Agr2::~Agr2()
{
    close();
    delete t_agr2;
    delete c_agr2;
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
    ui->groupBox_testCalib->setTitle(QString("Последняя калибровка: %1\n").arg(c_agr2->getDate().toString("dd.MM.yyyy")));
    QString str;
        str = QString("Номер серия реагентов %1\n").arg(c_agr2->getReagent_serial())
            + QString("Срок годности реагентов %1\n").arg(c_agr2->getReagent_date().toString("dd.MM.yyyy"));

    ui->label_testCalibString->setText(c_agr2->print());

    if( t_agr2->getSingle() ) {
        ui->radioButton_testSingle->setChecked(true);
    }
    else {
        ui->radioButton_testDouble->setChecked(true);
    }

    if( t_agr2->getK1() ) {
        ui->checkBox_testCh1->setChecked(true);
        ui->lineEdit_testCh1->setText(t_agr2->getNum1());
    }
    else {
        ui->checkBox_testCh1->setChecked(false);
    }

    if( t_agr2->getK2() ) {
        ui->checkBox_testCh2->setChecked(true);
        ui->lineEdit_testCh2->setText(t_agr2->getNum2());
    }
    else {
        ui->checkBox_testCh2->setChecked(false);
    }

    if( t_agr2->getK3() ) {
        ui->checkBox_testCh3->setChecked(true);
        ui->lineEdit_testCh3->setText(t_agr2->getNum3());

    }
    else {
        ui->checkBox_testCh3->setChecked(false);
    }

    if( t_agr2->getK4() ) {
        ui->checkBox_testCh4->setChecked(true);
        ui->lineEdit_testCh4->setText(t_agr2->getNum4());

    }
    else {
        ui->checkBox_testCh4->setChecked(false);
    }

//    ui->checkBox_calibCh1->setChecked(c_agr2->getK1());
//    ui->checkBox_calibCh2->setChecked(c_agr2->getK2());
//    ui->checkBox_calibCh3->setChecked(c_agr2->getK3());
//    ui->checkBox_calibCh4->setChecked(c_agr2->getK4());

    ui->doubleSpinBox_calibIncubeTime_1->setValue(c_agr2->getIncube_time());
    ui->doubleSpinBox_calibIncubeTime_2->setValue(c_agr2->getIncube_time_2());
    ui->doubleSpinBox_calibWriteTime->setValue(c_agr2->getWrite_time());
    ui->doubleSpinBox_calibVillebrand->setValue(c_agr2->getK_plazma());
    ui->dateEdit_calibKPlazma->setDate(c_agr2->getK_plazma_date());
    ui->lineEdit_calibKPlazmaSerial->setText(c_agr2->getK_plazma_serial());
    ui->dateEdit_calibReagent->setDate(c_agr2->getReagent_date());
    ui->lineEdit_calibReagentSerial->setText(c_agr2->getReagent_serial());
}

void Agr2::close()
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

    c_agr2->setIncube_time(ui->doubleSpinBox_calibIncubeTime_1->value());
    c_agr2->setIncube_time_2(ui->doubleSpinBox_calibIncubeTime_2->value());
    c_agr2->setWrite_time(ui->doubleSpinBox_calibWriteTime->value());
    c_agr2->setK_plazma(ui->doubleSpinBox_calibVillebrand->value());
    c_agr2->setK_plazma_date(ui->dateEdit_calibKPlazma->date());
    c_agr2->setK_plazma_serial(ui->lineEdit_calibKPlazmaSerial->text());
    c_agr2->setReagent_date(ui->dateEdit_calibReagent->date());
    c_agr2->setReagent_serial(ui->lineEdit_calibReagentSerial->text());
}

void Agr2::calibrationData1Come(double value)
{
    QDateTime dt = QDateTime::currentDateTime();
    c_agr2->setDate(dt.date());
    //c_agr2->setTime(dt.time());
    c_agr2->setCk1(value);
    //calibrationDataCome(7, t0);
}

void Agr2::calibrationData2Come(double value)
{
    QDateTime dt = QDateTime::currentDateTime();
    c_agr2->setDate(dt.date());
    //c_agr2->setTime(dt.time());
    c_agr2->setCk2(value);
    //calibrationDataCome(7, t0);
}

void Agr2::calibrationData3Come(double value)
{
    QDateTime dt = QDateTime::currentDateTime();
    c_agr2->setDate(dt.date());
    //c_agr2->setTime(dt.time());
    c_agr2->setCk3(value);
    //calibrationDataCome(7, t0);
}

void Agr2::calibrationData4Come(double value)
{
    QDateTime dt = QDateTime::currentDateTime();
    c_agr2->setDate(dt.date());
    //c_agr2->setTime(dt.time());
    c_agr2->setCk4(value);
    //calibrationDataCome(7, t0);
}

void Agr2::on_pushButton_calib_clicked()
{
//    bool a = ui->checkBox_calibCh1->isChecked();
//    bool b = ui->checkBox_calibCh2->isChecked();
//    bool c = ui->checkBox_calibCh3->isChecked();
//    bool d = ui->checkBox_calibCh4->isChecked();

    bool e = !ui->lineEdit_calibKPlazmaSerial->text().isEmpty();
    bool f = !ui->lineEdit_calibReagentSerial->text().isEmpty();

    QDate now = QDate::currentDate();
    bool g = now <= ui->dateEdit_calibKPlazma->date();
    bool i = now <= ui->dateEdit_calibReagent->date();

    if(!(g && i) ) {
        QMessageBox::information(this, "Внимание!", "Проверьте срок годности используемых реагентов!");
        return;
    }
    //bool c = (ui->doubleSpinBox_testIncubeTime->value() != NULL) && (ui->doubleSpinBox_testWriteTime->value() != NULL);
    if( !(e && f) ) {
        QMessageBox::information(this, "Внимание!", "Для того чтобы продолжить необходимо выбрать рабочие каналы и заполнить все поля с параметрами!");
        return;
    }

    c_agr2->setDate(QDate::currentDate());
    c_agr2->setReagent_date(ui->dateEdit_calibReagent->date());
    c_agr2->setReagent_serial(ui->lineEdit_calibReagentSerial->text());
    c_agr2->setK_plazma_date(ui->dateEdit_calibKPlazma->date());
    //c_agr2->setK_plazma_serial(ui->lineEdit_calibKPlazmaNum->text());
    //c_agr2->setIncube_time(ui->doubleSpinBox_calibIncubeTime_1->value());
    c_agr2->setWrite_time(ui->doubleSpinBox_calibWriteTime->value());
    c_agr2->setIncube_time_2(ui->doubleSpinBox_calibIncubeTime_2->value());

//    c_agr2->setK1(ui->checkBox_calibCh1->isChecked());
//    c_agr2->setK2(ui->checkBox_calibCh2->isChecked());
//    c_agr2->setK3(ui->checkBox_calibCh3->isChecked());
//    c_agr2->setK4(ui->checkBox_calibCh4->isChecked());

    c_agr2->save();
    emit calibration(StartCalibrationAgr2::getStart(c_agr2));
}

void Agr2::on_pushButton_test_clicked()
{
    bool a, b, c, d;
    if(ui->checkBox_testCh1->isChecked() && !ui->lineEdit_testCh1->text().isEmpty()) a = true;
    else a = false;
    if(ui->checkBox_testCh2->isChecked() && !ui->lineEdit_testCh2->text().isEmpty()) b = true;
    else b = false;
    if(ui->checkBox_testCh3->isChecked() && !ui->lineEdit_testCh3->text().isEmpty()) c = true;
    else c = false;
    if(ui->checkBox_testCh4->isChecked() && !ui->lineEdit_testCh4->text().isEmpty()) d = true;
    else d = false;

//    bool e = c_agr2->getCk1() || c_agr2->getCk2() || c_agr2->getCk3() || c_agr2->getCk4();
//    if( !(!c_agr2->getDate().toString("dd.MM.yyyy").isEmpty() && e) ) {
//        //QString str = QString("%1").arg(c_ko2.getDate().toString("dd/MM/yyyy"));
//        QMessageBox::information(this, "Внимание!", QString("Для того чтобы продолжить неоходимо провести калибровку."));
//        return;
//    }
    //bool c = (ui->doubleSpinBox_testIncubeTime->value() != NULL) && (ui->doubleSpinBox_testWriteTime->value() != NULL);
    if ( !(a || b || c || d) ) {
        QMessageBox::information(this, "Внимание!", "Для того чтобы продолжить необходимо выбрать рабочие каналы и заполнить все поля с параметрами.");
        return;
    }

    t_agr2->setK1(ui->checkBox_testCh1->isChecked());
    t_agr2->setK2(ui->checkBox_testCh2->isChecked());
    t_agr2->setK3(ui->checkBox_testCh3->isChecked());
    t_agr2->setK4(ui->checkBox_testCh4->isChecked());

    t_agr2->setNum1(ui->lineEdit_testCh1->text());
    t_agr2->setNum2(ui->lineEdit_testCh2->text());
    t_agr2->setNum3(ui->lineEdit_testCh3->text());
    t_agr2->setNum4(ui->lineEdit_testCh4->text());

    t_agr2->setSingle(ui->radioButton_testSingle->isChecked());

    t_agr2->save();
    emit measurement(StartTestAgr2::getStart(t_agr2));
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

QString Agr2::t_print()
{
    return t_agr2->print();
}

void Agr2::setT1(double value)
{
    t_agr2->setT1(value);
}

void Agr2::setT2(double value)
{
    t_agr2->setT2(value);
}

void Agr2::setT3(double value)
{
    t_agr2->setT3(value);
}

void Agr2::setT4(double value)
{
    t_agr2->setT4(value);
}

QString Agr2::c_print()
{
    return c_agr2->print();
}

void Agr2::btp1Come(double value)
{
    c_agr2->setBTP1(value);
}

void Agr2::btp2Come(double value)
{
    c_agr2->setBTP2(value);
}

void Agr2::btp3Come(double value)
{
    c_agr2->setBTP3(value);
}

void Agr2::btp4Come(double value)
{
    c_agr2->setBTP4(value);
}

void Agr2::otp1Come(double value)
{
    c_agr2->setOTP1(value);
}

void Agr2::otp2Come(double value)
{
    c_agr2->setOTP2(value);
}

void Agr2::otp3Come(double value)
{
    c_agr2->setOTP3(value);
}

void Agr2::otp4Come(double value)
{
    c_agr2->setOTP4(value);
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
    start->setModeID(CalibAgr2_ID);
    start->setBtp_time(5);
    start->setOtp_time(5);
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
    start->setModeID(TestAgr2_ID);
    start->setBtp_time(5);
    start->setOtp_time(5);
    return start;
}
