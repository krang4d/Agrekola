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
    QString str;
        str = QString("Дата проведения %1\n").arg(c_ko2.getDate().toString("dd.MM.yyyy"))
            + QString("Номер серия реагентов %1\n").arg(c_ko2.getReagent_serial())
            + QString("Срок годности реагентов %1\n").arg(c_ko2.getReagent_date().toString("dd.MM.yyyy"))
            + QString("Номер серия контрольной плазмы %1\n").arg(c_ko2.getK_plazma_serial())
            + QString("Срок годности контрольной плазмы %1\n").arg(c_ko2.getK_plazma_date().toString("dd.MM.yyyy"))
            + QString("АЧТВ 1го канала %1\n").arg(c_ko2.getA4tv_kp1())
            + QString("АЧТВ 2го канала %1\n").arg(c_ko2.getA4tv_kp2())
            + QString("АЧТВ 3го канала %1\n").arg(c_ko2.getA4tv_kp3())
            + QString("АЧТВ 4го канала %8").arg(c_ko2.getA4tv_kp4());
    ui->label_test1CalibString->setText(str);
    //connect(ui->page_1, SIGNAL(startMeasurment(StartMeasurment*)),this, SIGNAL(measurement(StartMeasurment*)));

    if( t_ko2.getSingle() ) {
        ui->radioButton_test1Single->setChecked(true);
        ui->radioButton_test2Single->setChecked(true);
    }
    else {
        ui->radioButton_test1Double->setChecked(true);
        ui->radioButton_test2Double->setChecked(true);
    }

    if( t_ko2.getK1() ) {
        ui->checkBox_test1Ch1->setChecked(true);
        ui->checkBox_test2Ch1->setChecked(true);
        ui->lineEdit_test1Ch1->setText(t_ko2.getNum1());
        ui->lineEdit_test2Ch1->setText(t_ko2.getNum1());
    }
    else {
        ui->checkBox_test1Ch1->setChecked(false);
        ui->checkBox_test2Ch1->setChecked(false);
    }

    if( t_ko2.getK2() ) {
        ui->checkBox_test1Ch2->setChecked(true);
        ui->lineEdit_test1Ch2->setText(t_ko2.getNum2());
        ui->checkBox_test2Ch2->setChecked(true);
        ui->lineEdit_test2Ch2->setText(t_ko2.getNum2());
    }
    else {
        ui->checkBox_test1Ch2->setChecked(false);
        ui->checkBox_test2Ch2->setChecked(false);
    }

    if( t_ko2.getK3() ) {
        ui->checkBox_test1Ch3->setChecked(true);
        ui->lineEdit_test1Ch3->setText(t_ko2.getNum3());
        ui->checkBox_test2Ch3->setChecked(true);
        ui->lineEdit_test2Ch3->setText(t_ko2.getNum3());
    }
    else {
        ui->checkBox_test1Ch3->setChecked(false);
        ui->checkBox_test2Ch3->setChecked(false);
    }

    if( t_ko2.getK4() ) {
        ui->checkBox_test1Ch4->setChecked(true);
        ui->lineEdit_test1Ch4->setText(t_ko2.getNum4());
        ui->checkBox_test2Ch4->setChecked(true);
        ui->lineEdit_test2Ch4->setText(t_ko2.getNum4());
    }
    else {
        ui->checkBox_test1Ch4->setChecked(false);
        ui->checkBox_test2Ch4->setChecked(false);
    }

    ui->doubleSpinBox_calibIncube->setValue(c_ko2.getIncube_time());
    ui->doubleSpinBox_test2IncubeTime->setValue(c_ko2.getIncube_time());
    ui->doubleSpinBox_testWriteTime->setValue(c_ko2.getWrite_time());
    ui->doubleSpinBox_test2WriteTime->setValue(c_ko2.getWrite_time());
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

void Ko2::on_checkBox_test1Ch1_toggled(bool checked)
{
    ui->lineEdit_test1Ch1->setEnabled(checked);
    if( ui->radioButton_test1Double->isChecked())
        ui->checkBox_test1Ch2->setChecked(checked);
}

void Ko2::on_checkBox_test1Ch2_toggled(bool checked)
{
    if(ui->radioButton_test1Single->isChecked())
            ui->lineEdit_test1Ch2->setEnabled(checked);
}

void Ko2::on_checkBox_test1Ch3_toggled(bool checked)
{
    ui->lineEdit_test1Ch3->setEnabled(checked);
    if(ui->radioButton_test1Double->isChecked())
        ui->checkBox_test1Ch4->setChecked(checked);
}

void Ko2::on_checkBox_test1Ch4_toggled(bool checked)
{
    if( ui->radioButton_test1Single->isChecked() )
        ui->lineEdit_test1Ch4->setEnabled(checked);
}

void Ko2::on_checkBox_test2Ch1_toggled(bool checked)
{
    ui->lineEdit_test2Ch1->setEnabled(checked);
    if( ui->radioButton_test2Double->isChecked() )
        ui->checkBox_test2Ch2->setChecked(checked);
}

void Ko2::on_checkBox_test2Ch2_toggled(bool checked)
{
    if( ui->radioButton_test2Single->isChecked() )
        ui->lineEdit_test2Ch2->setEnabled(checked);
}

void Ko2::on_checkBox_test2Ch3_toggled(bool checked)
{
    ui->lineEdit_test2Ch3->setEnabled(checked);
    if( ui->radioButton_test2Double->isChecked() )
        ui->checkBox_test2Ch4->setChecked(checked);
}

void Ko2::on_checkBox_test2Ch4_toggled(bool checked)
{
    if( ui->radioButton_test2Single->isChecked() )
        ui->lineEdit_test2Ch4->setEnabled(checked);
}

void Ko2::on_radioButton_test1Single_toggled(bool checked)
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

void Ko2::on_radioButton_test2Single_toggled(bool checked)
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

void Ko2::on_lineEdit_test1Ch1_textChanged(const QString &arg1)
{
    if(ui->radioButton_test1Double->isChecked())
        ui->lineEdit_test1Ch2->setText(arg1);
}

void Ko2::on_lineEdit_test1Ch3_textChanged(const QString &arg1)
{
    if(ui->radioButton_test1Double->isChecked())
        ui->lineEdit_test1Ch4->setText(arg1);
}

void Ko2::on_lineEdit_test2Ch1_textChanged(const QString &arg1)
{
    if(ui->radioButton_test2Double->isChecked())
        ui->lineEdit_test2Ch2->setText(arg1);
}

void Ko2::on_lineEdit_test2Ch3_textChanged(const QString &arg1)
{
    if(ui->radioButton_test2Double->isChecked())
        ui->lineEdit_test2Ch4->setText(arg1);
}

void Ko2::on_pushButton_test1_clicked()
{
    t_ko2.setK1(ui->checkBox_test1Ch1->isChecked());
    t_ko2.setK2(ui->checkBox_test1Ch2->isChecked());
    t_ko2.setK3(ui->checkBox_test1Ch3->isChecked());
    t_ko2.setK4(ui->checkBox_test1Ch4->isChecked());

    t_ko2.setNum1(ui->lineEdit_test1Ch1->text());
    t_ko2.setNum2(ui->lineEdit_test1Ch2->text());
    t_ko2.setNum3(ui->lineEdit_test1Ch3->text());
    t_ko2.setNum4(ui->lineEdit_test1Ch4->text());

    t_ko2.setSingle(ui->radioButton_test1Single->isChecked());

    t_ko2.save();
    c_ko2.save();

    //emit measurement(StartTestKo2::getStart());
}

void Ko2::on_pushButton_test2_clicked()
{
    t_ko2.setK1(ui->checkBox_test2Ch1->isChecked());
    t_ko2.setK2(ui->checkBox_test2Ch2->isChecked());
    t_ko2.setK3(ui->checkBox_test2Ch3->isChecked());
    t_ko2.setK4(ui->checkBox_test2Ch4->isChecked());

    t_ko2.setNum1(ui->lineEdit_test2Ch1->text());
    t_ko2.setNum2(ui->lineEdit_test2Ch2->text());
    t_ko2.setNum3(ui->lineEdit_test2Ch3->text());
    t_ko2.setNum4(ui->lineEdit_test2Ch4->text());

    t_ko2.setSingle(ui->radioButton_test2Single->isChecked());

    c_ko2.setIncube_time(ui->doubleSpinBox_test2IncubeTime->value());
    c_ko2.setWrite_time(ui->doubleSpinBox_test2WriteTime->value());

    t_ko2.save();
    c_ko2.save();

    //emit measurement(StartTestKo2::getStart());
}

void Ko2::on_pushButton_calib_clicked()
{
    c_ko2.setDate(QDate::currentDate());
    c_ko2.setK_plazma_date(ui->dateEdit_calibPlazma->date());
    c_ko2.setK_plazma_serial(ui->lineEdit_calibKPlazmaSerial->text());
    c_ko2.setReagent_date(ui->dateEdit_calibReagent->date());
    c_ko2.setReagent_serial(ui->lineEdit_calibReagentSerial->text());
    c_ko2.setIncube_time(ui->doubleSpinBox_calibIncube->value());
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
