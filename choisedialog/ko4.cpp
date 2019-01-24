#include "ko4.h"
#include "ui_ko4.h"

Ko4::Ko4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ko4)
{
    ui->setupUi(this);
    open();
    //connect(ui->page_2, &StartMeasurment::startMeasurment, this, &Ko4::measurement);
}

Ko4::~Ko4()
{
    save();
    delete ui;
}

void Ko4::calibrationDataCome(int n, double deta)
{
    //один параметр контрольной нормальной плазмы
    QDateTime dt = QDateTime::currentDateTime();
    //ui->label_calibrationData->setText(dt.toString("dd.MM.yyyy ") + dt.toString("hh:mm:ss"));
//    if(param.count() <= n)
//        param.push_back(QString("%1").arg(deta));
//    else param.replace(n, QString("%1").arg(deta));
//    file.saveKo4(param);
}

void Ko4::open()
{
/* Старый метод загрузки параметов из TXT*/
//    file.openKo4(param);
//    if( !param.isEmpty() && param.count() >= 10 ) {
//        ui->label_calibrationData->setText(param.at(0));
//        ui->lineEdit_1->setText(param.at(1));
//        ui->lineEdit_2->setText(param.at(2));
//        ui->lineEdit_3->setText(param.at(3));
//        ui->lineEdit_4->setText(param.at(4));
//        ui->lineEdit_5->setText(param.at(5));
//    } else
//        param = QStringList({0, 0, 0, 0, 0, 0, 0 , 0 , 0, 0});//10 параметров
/* Новый метод загрузки параметров из XML */
    QString str;
        str = QString("Дата проведения %1\n").arg(c_ko4.getDate().toString("dd.MM.yyyy"))
            + QString("Номер серия реагентов %1\n").arg(c_ko4.getReagent_serial())
            + QString("Срок годности реагентов %1\n").arg(c_ko4.getReagent_date().toString("dd.MM.yyyy"));

    ui->label_test1CalibrString->setText(str);

    ui->doubleSpinBox_test2IncubeTime->setValue(c_ko4.getIncube_time());
    ui->doubleSpinBox_test2WriteTime->setValue(c_ko4.getWrite_time());

    if( t_ko4.getSingle() ) {
        ui->radioButton_test1Single->setChecked(true);
        ui->radioButton_test2Single->setChecked(true);
    }
    else {
        ui->radioButton_test1Double->setChecked(true);
        ui->radioButton_test2Double->setChecked(true);
    }

    if( t_ko4.getK1() ) {
        ui->checkBox_test1Ch1->setChecked(true);
        ui->lineEdit_test1Ch1->setText(t_ko4.getNum1());
        ui->checkBox_test2Ch1->setChecked(true);
        ui->lineEdit_test2Ch1->setText(t_ko4.getNum1());
    }
    else {
        ui->checkBox_test1Ch1->setChecked(false);
        ui->checkBox_test2Ch1->setChecked(false);
    }

    if( t_ko4.getK2() ) {
        ui->checkBox_test1Ch2->setChecked(true);
        ui->lineEdit_test1Ch2->setText(t_ko4.getNum2());
        ui->checkBox_test2Ch2->setChecked(true);
        ui->lineEdit_test2Ch2->setText(t_ko4.getNum2());
    }
    else {
        ui->checkBox_test1Ch2->setChecked(false);
        ui->checkBox_test2Ch2->setChecked(false);
    }

    if( t_ko4.getK3() ) {
        ui->checkBox_test1Ch3->setChecked(true);
        ui->lineEdit_test1Ch3->setText(t_ko4.getNum3());
        ui->checkBox_test2Ch3->setChecked(true);
        ui->lineEdit_test2Ch3->setText(t_ko4.getNum3());
    }
    else {
        ui->checkBox_test1Ch3->setChecked(false);
        ui->checkBox_test2Ch3->setChecked(false);
    }

    if( t_ko4.getK4() ) {
        ui->checkBox_test1Ch4->setChecked(true);
        ui->lineEdit_test1Ch4->setText(t_ko4.getNum4());
        ui->checkBox_test2Ch4->setChecked(true);
        ui->lineEdit_test2Ch4->setText(t_ko4.getNum4());

    }
    else {
        ui->checkBox_test1Ch4->setChecked(false);
        ui->checkBox_test2Ch4->setChecked(false);
    }

    ui->checkBox_calibCh1->setChecked(c_ko4.getK1());
    ui->checkBox_calibCh2->setChecked(c_ko4.getK2());
    ui->checkBox_calibCh3->setChecked(c_ko4.getK3());
    ui->checkBox_calibCh4->setChecked(c_ko4.getK4());

    ui->doubleSpinBox_calibIncubeTime->setValue(c_ko4.getIncube_time());
    ui->doubleSpinBox_calibWriteTime->setValue(c_ko4.getWrite_time());
}

void Ko4::save()
{
//    param.clear();
//    param.replace(0, ui->label_calibrationData->text());
//    param.replace(1, ui->lineEdit_1->text());
//    param.replace(2, ui->lineEdit_2->text());
//    param.replace(3, ui->lineEdit_3->text());
//    param.replace(4, ui->lineEdit_4->text());
//    param.replace(5, ui->lineEdit_5->text());
//    file.saveKo4(param);
}

void Ko4::calibrationData1Come(double t0)
{
    calibrationDataCome(6, t0);
}

void Ko4::calibrationData2Come(double t0)
{
    calibrationDataCome(7, t0);
}

void Ko4::calibrationData3Come(double t0)
{
    calibrationDataCome(8, t0);
}

void Ko4::calibrationData4Come(double t0)
{
    calibrationDataCome(9, t0);
}

void Ko4::on_radioButton_test1Single_toggled(bool checked)
{
    if(ui->radioButton_test1Double->isChecked()) {
        ui->checkBox_test1Ch2->setEnabled(false);
        ui->checkBox_test1Ch4->setEnabled(false);
        ui->lineEdit_test1Ch2->setEnabled(false);
        ui->lineEdit_test1Ch4->setEnabled(false);
        ui->lineEdit_test1Ch2->setText(ui->lineEdit_test1Ch1->text());
        ui->lineEdit_test1Ch4->setText(ui->lineEdit_test1Ch3->text());

        if(ui->checkBox_test1Ch1->isChecked()) ui->checkBox_test1Ch2->setChecked(true);
        else ui->checkBox_test1Ch2->setChecked(false);
        if(ui->checkBox_test1Ch3->isChecked()) ui->checkBox_test1Ch4->setChecked(true);
        else ui->checkBox_test1Ch4->setChecked(false);
    }
    if(ui->radioButton_test1Single->isChecked()) {
        ui->checkBox_test1Ch2->setEnabled(true);
        ui->checkBox_test1Ch4->setEnabled(true);
        ui->lineEdit_test1Ch2->setEnabled(ui->checkBox_test1Ch2->isChecked());
        ui->lineEdit_test1Ch4->setEnabled(ui->checkBox_test1Ch4->isChecked());
    }
}

void Ko4::on_radioButton_test2Single_toggled(bool checked)
{
    if(ui->radioButton_test2Double->isChecked()) {
        ui->checkBox_test2Ch2->setEnabled(false);
        ui->checkBox_test2Ch4->setEnabled(false);
        ui->lineEdit_test2Ch2->setEnabled(false);
        ui->lineEdit_test2Ch4->setEnabled(false);
        ui->lineEdit_test2Ch2->setText(ui->lineEdit_test2Ch1->text());
        ui->lineEdit_test2Ch4->setText(ui->lineEdit_test2Ch3->text());

        if(ui->checkBox_test2Ch1->isChecked()) ui->checkBox_test2Ch2->setChecked(true);
        else ui->checkBox_test2Ch2->setChecked(false);
        if(ui->checkBox_test2Ch3->isChecked()) ui->checkBox_test2Ch4->setChecked(true);
        else ui->checkBox_test2Ch4->setChecked(false);
    }
    if(ui->radioButton_test2Single->isChecked()) {
        ui->checkBox_test2Ch2->setEnabled(true);
        ui->checkBox_test2Ch4->setEnabled(true);
        ui->lineEdit_test2Ch2->setEnabled(ui->checkBox_test2Ch2->isChecked());
        ui->lineEdit_test2Ch4->setEnabled(ui->checkBox_test2Ch4->isChecked());
    }
}

void Ko4::on_checkBox_test1Ch1_toggled(bool checked)
{
    ui->lineEdit_test1Ch1->setEnabled(checked);
    if( ui->radioButton_test1Double->isChecked())
        ui->checkBox_test1Ch2->setChecked(checked);
}

void Ko4::on_checkBox_test1Ch2_toggled(bool checked)
{
    if(ui->radioButton_test1Single->isChecked())
            ui->lineEdit_test1Ch2->setEnabled(checked);
}

void Ko4::on_checkBox_test1Ch3_toggled(bool checked)
{
    ui->lineEdit_test1Ch3->setEnabled(checked);
    if(ui->radioButton_test1Double->isChecked())
        ui->checkBox_test1Ch4->setChecked(checked);
}

void Ko4::on_checkBox_test1Ch4_toggled(bool checked)
{
    if( ui->radioButton_test1Single->isChecked() )
        ui->lineEdit_test1Ch4->setEnabled(checked);
}

void Ko4::on_checkBox_test2Ch1_toggled(bool checked)
{
    ui->lineEdit_test2Ch1->setEnabled(checked);
    if( ui->radioButton_test2Double->isChecked())
        ui->checkBox_test2Ch2->setChecked(checked);
}

void Ko4::on_checkBox_test2Ch2_toggled(bool checked)
{
    if(ui->radioButton_test2Single->isChecked())
            ui->lineEdit_test2Ch2->setEnabled(checked);
}

void Ko4::on_checkBox_test2Ch3_toggled(bool checked)
{
    ui->lineEdit_test2Ch3->setEnabled(checked);
    if(ui->radioButton_test2Double->isChecked())
        ui->checkBox_test2Ch4->setChecked(checked);
}

void Ko4::on_checkBox_test2Ch4_toggled(bool checked)
{
    if( ui->radioButton_test2Single->isChecked() )
        ui->lineEdit_test2Ch4->setEnabled(checked);
}

void Ko4::on_lineEdit_test1Ch1_textChanged(const QString &arg1)
{
    if(ui->radioButton_test1Double->isChecked())
        ui->lineEdit_test1Ch2->setText(arg1);
}

void Ko4::on_lineEdit_test1Ch3_textChanged(const QString &arg1)
{
    if(ui->radioButton_test1Double->isChecked())
        ui->lineEdit_test1Ch4->setText(arg1);
}

void Ko4::on_lineEdit_test2Ch1_textChanged(const QString &arg1)
{
    if(ui->radioButton_test2Double->isChecked())
        ui->lineEdit_test2Ch2->setText(arg1);
}

void Ko4::on_lineEdit_test2Ch3_textChanged(const QString &arg1)
{
    if(ui->radioButton_test2Double->isChecked())
        ui->lineEdit_test2Ch2->setText(arg1);
}

void Ko4::on_pushButton_test1_clicked()
{
    t_ko4.setK1(ui->checkBox_test1Ch1->isChecked());
    t_ko4.setK2(ui->checkBox_test1Ch2->isChecked());
    t_ko4.setK3(ui->checkBox_test1Ch3->isChecked());
    t_ko4.setK4(ui->checkBox_test1Ch4->isChecked());

    t_ko4.setNum1(ui->lineEdit_test1Ch1->text());
    t_ko4.setNum2(ui->lineEdit_test1Ch2->text());
    t_ko4.setNum3(ui->lineEdit_test1Ch3->text());
    t_ko4.setNum4(ui->lineEdit_test1Ch4->text());

    t_ko4.setSingle(ui->radioButton_test1Single->isChecked());

    t_ko4.save();
    c_ko4.save();
     //emit calibration(StartTestKo4::getStart());
}

void Ko4::on_pushButton_test2_clicked()
{
    t_ko4.setK1(ui->checkBox_test2Ch1->isChecked());
    t_ko4.setK2(ui->checkBox_test2Ch2->isChecked());
    t_ko4.setK3(ui->checkBox_test2Ch3->isChecked());
    t_ko4.setK4(ui->checkBox_test2Ch4->isChecked());

    t_ko4.setNum1(ui->lineEdit_test2Ch1->text());
    t_ko4.setNum2(ui->lineEdit_test2Ch2->text());
    t_ko4.setNum3(ui->lineEdit_test2Ch3->text());
    t_ko4.setNum4(ui->lineEdit_test2Ch4->text());

    t_ko4.setSingle(ui->radioButton_test2Single->isChecked());

    t_ko4.save();
    c_ko4.save();
    //emit calibration(StartTestKo4::getStart());
}

void Ko4::on_pushButton_calib_clicked()
{
    c_ko4.setDate(QDate::currentDate());
    c_ko4.setReagent_date(ui->dateEdit_calibReagent->date());
    c_ko4.setReagent_serial(ui->lineEdit_calibReagentSerial->text());
    c_ko4.setK_plazma_date(ui->dateEdit_calibKPlazma->date());
    c_ko4.setK_plazma_serial(ui->lineEdit_calibKPlazmaSerial->text());
    c_ko4.setIncube_time(ui->doubleSpinBox_calibIncubeTime->value());
    c_ko4.setWrite_time(ui->doubleSpinBox_calibWriteTime->value());

    c_ko4.setK1(ui->checkBox_calibCh1->isChecked());
    c_ko4.setK2(ui->checkBox_calibCh2->isChecked());
    c_ko4.setK3(ui->checkBox_calibCh3->isChecked());
    c_ko4.setK4(ui->checkBox_calibCh4->isChecked());

    c_ko4.save();
    //emit calibration(StartCalibrationKo4::getStart());
}

StartMeasurment *StartCalibrationKo4::getStart()
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

StartMeasurment *StartTestKo4::getStart()
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
