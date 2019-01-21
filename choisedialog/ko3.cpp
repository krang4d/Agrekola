//Фибриноген
#include "ko3.h"
#include "ui_ko3.h"

Ko3::Ko3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ko3)
{
    ui->setupUi(this);
    open();
    //connect(ui->page_2, &StartMeasurment::startMeasurment, this, &Ko3::measurement);
}

Ko3::~Ko3()
{
    save();
    delete ui;
}

void Ko3::calibrationDataCome(int n, double deta)
{
    //один параметр контрольной нормальной плазмы
    QDateTime dt = QDateTime::currentDateTime();
    //ui->label_calibrationData->setText(dt.toString("dd.MM.yyyy ") + dt.toString("hh:mm:ss"));
    if(param.count() <= n)
        param.push_back(QString("%1").arg(deta));
    else param.replace(n, QString("%1").arg(deta));
    file.saveKo2(param);
}

void Ko3::open()
{
/* Старый метод загрузки параметов из TXT*/
//    file.openKo3(param);
//    if( !param.isEmpty() && param.count() >= 8 ) {
//        //ui->label_calibrationData->setText(param.at(0));
//        ui->lineEdit_1->setText(param.at(1));
//        ui->lineEdit_2->setText(param.at(2));
//        ui->lineEdit_3->setText(param.at(3));
//    } else
//        param = QStringList({0, 0, 0, 0, 0, 0, 0, 0}); //8 параметров
/* Новый метод загрузки параметров из XML */
    QString str;
        str = QString("Дата проведения %1\n").arg(c_ko3.getDate().toString("dd.MM.yyyy"))
            + QString("Номер серия реагентов %1\n").arg(c_ko3.getReagent_serial())
            + QString("Срок годности реагентов %1\n").arg(c_ko3.getReagent_date().toString("dd.MM.yyyy"));
    ui->label_testCalibString->setText(str);

    if( t_ko3.getSingle() ) {
        ui->radioButton_testSingle->setChecked(true);
    }
    else {
        ui->radioButton_testDouble->setChecked(true);
    }

    if( t_ko3.getK1() ) {
        ui->checkBox_testCh1->setChecked(true);
        ui->lineEdit_testCh1->setText(t_ko3.getNum1());
    }
    else {
        ui->checkBox_testCh1->setChecked(false);
    }

    if( t_ko3.getK2() ) {
        ui->checkBox_testCh2->setChecked(true);
        ui->lineEdit_testCh2->setText(t_ko3.getNum2());
    }
    else {
        ui->checkBox_testCh2->setChecked(false);
    }

    if( t_ko3.getK3() ) {
        ui->checkBox_testCh3->setChecked(true);
        ui->lineEdit_testCh3->setText(t_ko3.getNum3());

    }
    else {
        ui->checkBox_testCh3->setChecked(false);
    }

    if( t_ko3.getK4() ) {
        ui->checkBox_testCh4->setChecked(true);
        ui->lineEdit_testCh4->setText(t_ko3.getNum4());

    }
    else {
        ui->checkBox_testCh4->setChecked(false);
    }

    ui->doubleSpinBox_calibIncube->setValue(c_ko3.getIncube_time());
    ui->doubleSpinBox_calibWriteTime->setValue(c_ko3.getWrite_time());
}

void Ko3::save()
{
    //param.clear();
    //param.replace(0, ui->label_calibrationData->text());
//    param.replace(1, ui->lineEdit_1->text());
//    param.replace(2, ui->lineEdit_2->text());
//    param.replace(3, ui->lineEdit_3->text());
//    file.saveKo3(param);
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

void Ko3::on_pushButton_test_clicked()
{
    t_ko3.setK1(ui->checkBox_testCh1->isChecked());
    t_ko3.setK2(ui->checkBox_testCh2->isChecked());
    t_ko3.setK3(ui->checkBox_testCh3->isChecked());
    t_ko3.setK4(ui->checkBox_testCh4->isChecked());

    t_ko3.setNum1(ui->lineEdit_testCh1->text());
    t_ko3.setNum2(ui->lineEdit_testCh2->text());
    t_ko3.setNum3(ui->lineEdit_testCh3->text());
    t_ko3.setNum4(ui->lineEdit_testCh4->text());

    t_ko3.setSingle(ui->radioButton_testSingle->isChecked());

    t_ko3.save();
    c_ko3.save();
    //emit measurement(StartTestKo3::getStart());
}

void Ko3::on_pushButton_calib_clicked()
{
    c_ko3.setDate(QDate::currentDate());
    c_ko3.setReagent_date(ui->dateEdit_calibReagent->date());
    c_ko3.setReagent_serial(ui->lineEdit_calibReagentSerial->text());
    c_ko3.setK_plazma_date(ui->dateEdit_calibPlazma->date());
    c_ko3.setK_plazma_serial(ui->lineEdit_calibKPlazmaSerial->text());
    c_ko3.setFibrinogen_k_plazma(ui->lineEdit_calibFibrinogenKPlazma->text().toDouble());
    c_ko3.setIncube_time(ui->doubleSpinBox_calibIncube->value());
    c_ko3.setWrite_time(ui->doubleSpinBox_calibWriteTime->value());
    c_ko3.save();
    //emit calibration(StartCalibrationKo3::getStart());
}

void Ko3::on_radioButton_testSingle_toggled(bool checked)
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

void Ko3::on_checkBox_testCh1_toggled(bool checked)
{
    ui->lineEdit_testCh1->setEnabled(checked);
    if( ui->radioButton_testDouble->isChecked())
        ui->checkBox_testCh2->setChecked(checked);
}

void Ko3::on_checkBox_testCh2_toggled(bool checked)
{
    if(ui->radioButton_testSingle->isChecked())
            ui->lineEdit_testCh2->setEnabled(checked);
}

void Ko3::on_checkBox_testCh3_toggled(bool checked)
{
    ui->lineEdit_testCh3->setEnabled(checked);
    if(ui->radioButton_testDouble->isChecked())
        ui->checkBox_testCh4->setChecked(checked);
}

void Ko3::on_checkBox_testCh4_toggled(bool checked)
{
    if( ui->radioButton_testSingle->isChecked() )
        ui->lineEdit_testCh4->setEnabled(checked);
}

void Ko3::on_lineEdit_testCh1_textChanged(const QString &arg1)
{
    if(ui->radioButton_testDouble->isChecked())
        ui->lineEdit_testCh2->setText(arg1);
}

void Ko3::on_lineEdit_testCh3_textChanged(const QString &arg1)
{
    if(ui->radioButton_testDouble->isChecked())
        ui->lineEdit_testCh4->setText(arg1);
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

StartMeasurment *StartTestKo3::getStart()
{
    StartMeasurment *sm = new StartMeasurment(0);
    sm->setChannels(true, true, true, true);
    sm->setNum(1, "Измерение");
    sm->setNum(2, "Измерение");
    sm->setNum(3, "Измерение");
    sm->setNum(4, "Измерение");
    sm->setTime(10);
    sm->setTimeIncube(1, 3);
    return sm;
}
