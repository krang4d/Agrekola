#include "ko5.h"
#include "ui_ko5.h"

Ko5::Ko5(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ko5)
{
    ui->setupUi(this);
    open();
    //connect(ui->page_2, &StartMeasurment::startMeasurment, this, &Ko5::measurement);
}

Ko5::~Ko5()
{
    save();
    delete ui;
}

void Ko5::on_pushButton_calib_clicked()
{
    //file.saveKo5(param);
    t_ko5.setK1(ui->checkBox_testCh1->isChecked());
    t_ko5.setK2(ui->checkBox_testCh2->isChecked());
    t_ko5.setK3(ui->checkBox_testCh3->isChecked());
    t_ko5.setK4(ui->checkBox_testCh4->isChecked());

    t_ko5.setNum1(ui->lineEdit_testCh1->text());
    t_ko5.setNum2(ui->lineEdit_testCh2->text());
    t_ko5.setNum3(ui->lineEdit_testCh3->text());
    t_ko5.setNum4(ui->lineEdit_testCh4->text());

    t_ko5.setSingle(ui->radioButton_testSingle->isChecked());

    c_ko5.setDate(QDate::currentDate());
    c_ko5.setReagent_date(ui->dateEdit_calibReagent->date());
    c_ko5.setReagent_serial(ui->lineEdit_calibReagentSerial->text());
    c_ko5.setK_plazma_date(ui->dateEdit_calibKPlazma->date());
    c_ko5.setK_plazma_serial(ui->lineEdit_calibKPlazmaNum->text());
    c_ko5.setIncube_time(ui->doubleSpinBox_calibIncubeTime->value());
    c_ko5.setWrite_time(ui->doubleSpinBox_calibWriteTime->value());

    t_ko5.save();
    c_ko5.save();
    emit calibration(StartCalibrationKo5::getStart());
}

void Ko5::on_pushButton_test_clicked()
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

void Ko5::calibrationDataCome(int n, double deta)
{
    //один параметр контрольной нормальной плазмы
    QDateTime dt = QDateTime::currentDateTime();
    //ui->label_calibrationData->setText(dt.toString("dd.MM.yyyy ") + dt.toString("hh:mm:ss"));
    if(param.count() <= n)
        param.push_back(QString("%1").arg(deta));
    else param.replace(n, QString("%1").arg(deta));
    file.saveKo5(param);
}

void Ko5::open()
{
/* Старый метод загрузки параметов из TXT*/
//    file.openKo5(param);
//    if( !param.isEmpty() && param.count() >= 11 ) {
//        //ui->label_calibrationData->setText(param.at(0));
//        ui->lineEdit_1->setText(param.at(1));
//        //ui->lineEdit_2->setText(param.at(2));
//        ui->lineEdit_3->setText(param.at(3));
//        ui->lineEdit_4->setText(param.at(4));
//        ui->lineEdit_5->setText(param.at(5));
//        ui->lineEdit_6->setText(param.at(6));
//    } else
//        param = QStringList({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}); //11 параметров
    /* Новый метод загрузки параметров из XML */
        QString str;
            str = QString("Дата проведения %1\n").arg(c_ko5.getDate().toString("dd.MM.yyyy"))
                + QString("Номер серия реагентов %1\n").arg(c_ko5.getReagent_serial())
                + QString("Срок годности реагентов %1\n").arg(c_ko5.getReagent_date().toString("dd.MM.yyyy"));
        ui->label_testCalibString->setText(str);

        if( t_ko5.getSingle() ) {
            ui->radioButton_testSingle->setChecked(true);
        }
        else {
            ui->radioButton_testDouble->setChecked(true);
        }

        if( t_ko5.getK1() ) {
            ui->checkBox_testCh1->setChecked(true);
            ui->lineEdit_testCh1->setText(t_ko5.getNum1());
        }
        else {
            ui->checkBox_testCh1->setChecked(false);
        }

        if( t_ko5.getK2() ) {
            ui->checkBox_testCh2->setChecked(true);
            ui->lineEdit_testCh2->setText(t_ko5.getNum2());
        }
        else {
            ui->checkBox_testCh2->setChecked(false);
        }

        if( t_ko5.getK3() ) {
            ui->checkBox_testCh3->setChecked(true);
            ui->lineEdit_testCh3->setText(t_ko5.getNum3());

        }
        else {
            ui->checkBox_testCh3->setChecked(false);
        }

        if( t_ko5.getK4() ) {
            ui->checkBox_testCh4->setChecked(true);
            ui->lineEdit_testCh4->setText(t_ko5.getNum4());

        }
        else {
            ui->checkBox_testCh4->setChecked(false);
        }

        ui->doubleSpinBox_calibIncubeTime->setValue(c_ko5.getIncube_time());
        ui->doubleSpinBox_calibWriteTime->setValue(c_ko5.getWrite_time());
}

void Ko5::save()
{
    //param.clear();
    //param.replace(0, ui->label_calibrationData->text());
//    param.replace(1, ui->lineEdit_1->text());
//    //param.replace(2, ui->lineEdit_2->text());
//    param.replace(3, ui->lineEdit_3->text());
//    param.replace(4, ui->lineEdit_4->text());
//    param.replace(5, ui->lineEdit_5->text());
//    param.replace(6, ui->lineEdit_6->text());
//    file.saveKo5(param);
}

void Ko5::calibrationData1Come(double t0)
{
    calibrationDataCome(7, t0);
}

void Ko5::calibrationData2Come(double t0)
{
    calibrationDataCome(8, t0);
}

void Ko5::calibrationData3Come(double t0)
{
    calibrationDataCome(9, t0);
}

void Ko5::calibrationData4Come(double t0)
{
    calibrationDataCome(10, t0);
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

StartMeasurment *StartTestKo5::getStart()
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

StartMeasurment *StartCalibrationKo5::getStart()
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
