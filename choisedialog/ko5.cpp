#include "ko5.h"
#include "ui_ko5.h"

Ko5::Ko5(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ko5),
    t_ko5(new TestKo5),
    c_ko5(new CalibrationKo5)

{
    ui->setupUi(this);
    open();
}

void Ko5::setTab(int i)
{
    ui->tabWidget->setCurrentIndex(i);
}

Ko5::~Ko5()
{
    close();
    delete ui;
    delete c_ko5;
    delete t_ko5;
}

void Ko5::on_pushButton_calib_clicked()
{
    mode = CalibKo5_ID;
    bool e = !ui->lineEdit_calibKPlazmaNum->text().isEmpty();
    bool f = !ui->lineEdit_calibReagentSerial->text().isEmpty();

    if( !(e && f) ) {
        QMessageBox::information(this, "Внимание!", "Для того чтобы продолжить необходимо выбрать рабочие каналы и заполнить все поля с параметрами!");
        return;
    }

    QDate now = QDate::currentDate();
    bool g = now <= ui->dateEdit_calibKPlazma->date();
    bool i = now <= ui->dateEdit_calibReagent->date();

    if(!(g && i) ) {
        QMessageBox::information(this, "Внимание!", "Проверьте срок годности используемых реагентов!");
        return;
    }

    c_ko5->setReagent_date(ui->dateEdit_calibReagent->date());
    c_ko5->setReagent_serial(ui->lineEdit_calibReagentSerial->text());

    c_ko5->setK_plazma_date(ui->dateEdit_calibKPlazma->date());
    c_ko5->setK_plazma_serial(ui->lineEdit_calibKPlazmaNum->text());

    c_ko5->setIncube_time(ui->doubleSpinBox_calibIncubeTime->value());
    c_ko5->setWrite_time(ui->doubleSpinBox_calibWriteTime->value());

    c_ko5->setK_protrombine_index(ui->doubleSpinBox_calibIndex->value());
    c_ko5->setK_protrombine_otn(ui->doubleSpinBox_calibOTN->value());
    c_ko5->setProtrombine_k_Kvik(ui->doubleSpinBox_calibKvik->value());

    c_ko5->save();
    emit calibration(StartCalibrationKo5::getStart(t_ko5, c_ko5));
}

void Ko5::on_pushButton_test_clicked()
{
    mode = TestKo5_ID;
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

    bool f = c_ko5->getTime_12_Kvik() || c_ko5->getTime_25_Kvik()
            || c_ko5->getTime_50_Kvik() || c_ko5->getTime_k_Kvik();

    if( !(!c_ko5->getDate().toString("dd.MM.yyyy").isEmpty() && e) ) {
        QMessageBox::information(this, "Внимание!", QString("Для того чтобы продолжить неоходимо провести калибровку."));
        return;
    }

    if ( !(a || b || c || d) ) {
        QMessageBox::information(this, "Внимание!", "Для того чтобы продолжить необходимо заполнить все поля с параметрами.");
        return;
    }

    t_ko5->setK1(ui->checkBox_testCh1->isChecked());
    t_ko5->setK2(ui->checkBox_testCh2->isChecked());
    t_ko5->setK3(ui->checkBox_testCh3->isChecked());
    t_ko5->setK4(ui->checkBox_testCh4->isChecked());

    t_ko5->setNum1(ui->lineEdit_testCh1->text());
    t_ko5->setNum2(ui->lineEdit_testCh2->text());
    t_ko5->setNum3(ui->lineEdit_testCh3->text());
    t_ko5->setNum4(ui->lineEdit_testCh4->text());

    t_ko5->setSingle(ui->radioButton_testSingle->isChecked());

    t_ko5->save();
    emit measurement(StartTestKo5::getStart(t_ko5, c_ko5));
}

void Ko5::calibrationDataCome(int n, double deta)
{
    //один параметр контрольной нормальной плазмы
    QDateTime dt = QDateTime::currentDateTime();
//  ui->label_calibrationData->setText(dt.toString("dd.MM.yyyy ") + dt.toString("hh:mm:ss"));
//    if(param.count() <= n)
//        param.push_back(QString("%1").arg(deta));
//    else param.replace(n, QString("%1").arg(deta));
//    file.saveKo5(param);
}

void Ko5::open()
{
    /* Новый метод загрузки параметров из XML */
    //Загрузка параметров для Теста
    ui->groupBox_testCalib->setTitle(QString("Последняя калибровка: "));
    ui->label_testCalibString->setText(c_ko5->print());

    if( t_ko5->getSingle() ) {
        ui->radioButton_testSingle->setChecked(true);
    }
    else {
        ui->radioButton_testDouble->setChecked(true);
    }

    if( t_ko5->getK1() ) {
        ui->checkBox_testCh1->setChecked(true);
        ui->lineEdit_testCh1->setText(t_ko5->getNum1());
    }
    else {
        ui->checkBox_testCh1->setChecked(false);
    }

    if( t_ko5->getK2() ) {
        ui->checkBox_testCh2->setChecked(true);
        ui->lineEdit_testCh2->setText(t_ko5->getNum2());
    }
    else {
        ui->checkBox_testCh2->setChecked(false);
    }

    if( t_ko5->getK3() ) {
        ui->checkBox_testCh3->setChecked(true);
        ui->lineEdit_testCh3->setText(t_ko5->getNum3());
    }
    else {
        ui->checkBox_testCh3->setChecked(false);
    }

    if( t_ko5->getK4() ) {
        ui->checkBox_testCh4->setChecked(true);
        ui->lineEdit_testCh4->setText(t_ko5->getNum4());
    }
    else {
        ui->checkBox_testCh4->setChecked(false);
    }

    //Загрузка параметров для калибровки
    ui->lineEdit_calibKPlazmaNum->setText(c_ko5->getK_plazma_serial());
    ui->dateEdit_calibKPlazma->setDate(c_ko5->getK_plazma_date());
    ui->lineEdit_calibReagentSerial->setText(c_ko5->getReagent_serial());
    ui->dateEdit_calibReagent->setDate(c_ko5->getReagent_date());
    ui->doubleSpinBox_calibKvik->setValue(c_ko5->getProtrombine_k_Kvik());
    ui->doubleSpinBox_calibOTN->setValue(c_ko5->getK_protrombine_otn());
    ui->doubleSpinBox_calibIndex->setValue(c_ko5->getK_protrombine_index());
    ui->doubleSpinBox_calibIncubeTime->setValue(c_ko5->getIncube_time());
    ui->doubleSpinBox_calibWriteTime->setValue(c_ko5->getWrite_time());
}

void Ko5::close()
{
    c_ko5->save();
    t_ko5->save();
}


void Ko5::setDate(QDate d, SaveTo b)
{
    if(b == Test_ID) {
        t_ko5->setDate(d);
        t_ko5->save();
    }
    if(b == Calib_ID) {
        c_ko5->setDate(d);
        c_ko5->save();
    }
}

void Ko5::setTime(QTime t, SaveTo b)
{
    if(b == Test_ID) {
        t_ko5->setTime(t);
        t_ko5->save();
    }
    if(b == Calib_ID) {
        c_ko5->setTime(t);
        c_ko5->save();
    }
}

void Ko5::calibrationData1Come(double t0, int i)
{
    //calibrationDataCome(7, t0);
    c_ko5->setTime_k_Kvik(t0);
    c_ko5->save();
}

void Ko5::calibrationData2Come(double t0, int i)
{
    //calibrationDataCome(8, t0);
    c_ko5->setTime_50_Kvik(t0);
    c_ko5->save();
}

void Ko5::calibrationData3Come(double t0, int i)
{
    //calibrationDataCome(9, t0);
    c_ko5->setTime_25_Kvik(t0);
    c_ko5->save();
}

void Ko5::calibrationData4Come(double t0, int i)
{
    //calibrationDataCome(10, t0);
    c_ko5->setTime_12_Kvik(t0);
    c_ko5->save();
}

void Ko5::setT1_2(double t0, int i)
{
    c_ko5->setTime_k_Kvik(t0);
    c_ko5->setTime_50_Kvik(t0);
    c_ko5->save();
}

void Ko5::setT3_4(double t0, int i)
{
    c_ko5->setTime_25_Kvik(t0);
    c_ko5->setTime_12_Kvik(t0);
    c_ko5->save();
}

QString Ko5::t_print()
{
    //t_ko5->setDate(QDate::currentDate());
    c_ko5->save();
    return t_ko5->print();

}

void Ko5::setT1(double value, int i)
{
    t_ko5->setT1(value);
    c_ko5->save();
}

void Ko5::setT2(double value, int i)
{
    t_ko5->setT2(value);
    c_ko5->save();
}

void Ko5::setT3(double value, int i)
{
    t_ko5->setT3(value);
    t_ko5->save();
}

void Ko5::setT4(double value, int i)
{
    t_ko5->setT4(value);
    t_ko5->save();
}

void Ko5::calibrationData1_2Come(double t0, int i)
{
    switch (i) {
    case 1:
        c_ko5->setTime_k_Kvik(t0);
        break;
    case 2:
        c_ko5->setTime_25_Kvik(t0);
        break;
    default:
        break;
    }
    c_ko5->save();
}

void Ko5::calibrationData2_4Come(double t0, int i)
{
    switch (i) {
    case 1:
        c_ko5->setTime_50_Kvik(t0);
        break;
    case 2:
        c_ko5->setTime_12_Kvik(t0);
        break;
    default:
        break;
    }
    c_ko5->save();
}

QString Ko5::c_print()
{
    return c_ko5->print();
}

void Ko5::on_radioButton_testSingle_toggled(bool checked)
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

void Ko5::on_checkBox_testCh1_toggled(bool checked)
{
    ui->lineEdit_testCh1->setEnabled(checked);
    if( ui->radioButton_testDouble->isChecked())
        ui->checkBox_testCh2->setChecked(checked);
}

void Ko5::on_checkBox_testCh2_toggled(bool checked)
{
    if(ui->radioButton_testSingle->isChecked())
            ui->lineEdit_testCh2->setEnabled(checked);
}

void Ko5::on_checkBox_testCh3_toggled(bool checked)
{
    ui->lineEdit_testCh3->setEnabled(checked);
    if(ui->radioButton_testDouble->isChecked())
        ui->checkBox_testCh4->setChecked(checked);
}

void Ko5::on_checkBox_testCh4_toggled(bool checked)
{
    if( ui->radioButton_testSingle->isChecked() )
        ui->lineEdit_testCh4->setEnabled(checked);
}

void Ko5::on_lineEdit_testCh1_textChanged(const QString &arg1)
{
    if(ui->radioButton_testDouble->isChecked())
        ui->lineEdit_testCh2->setText(arg1);
}

void Ko5::on_lineEdit_testCh3_textChanged(const QString &arg1)
{
    if(ui->radioButton_testDouble->isChecked())
        ui->lineEdit_testCh4->setText(arg1);
}

StartMeasurement *StartCalibrationKo5::getStart(TestKo5 *t_ko5, Calibration *c_ko5)
{
    StartMeasurement *start = new StartMeasurement(t_ko5, c_ko5);
    start->setChannels(true, true, true, true);
    start->setNum(1, "Калибровка");
    start->setNum(2, "Калибровка");
    start->setNum(3, "Калибровка");
    start->setNum(4, "Калибровка");
    start->setTimeWrite(c_ko5->getWrite_time());
    start->setTimeIncube(1, c_ko5->getIncube_time());
    start->setProbe(false);
    start->setModeID(CalibKo5_ID);
    return start;
}

StartMeasurement *StartTestKo5::getStart(TestKo5 *t_ko5, Calibration *c_ko5)
{
    StartMeasurement *start = new StartMeasurement(t_ko5, c_ko5);
    start->setChannels(t_ko5->getK1(), t_ko5->getK2(), t_ko5->getK2(), t_ko5->getK4());
    start->setNum(1, t_ko5->getNum1());
    start->setNum(2, t_ko5->getNum2());
    start->setNum(3, t_ko5->getNum3());
    start->setNum(4, t_ko5->getNum4());
    start->setProbe(t_ko5->getSingle());
    start->setTimeWrite(c_ko5->getWrite_time());
    start->setTimeIncube(1, c_ko5->getIncube_time());
    start->setModeID(TestKo5_ID);
    return start;
}

void Ko5::on_tabWidget_currentChanged(int index)
{
    switch (index) {
    default:
        open();
        break;
    }
}
