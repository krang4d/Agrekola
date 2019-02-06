#include "ko4.h"
#include "ui_ko4.h"

Ko4::Ko4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ko4)
{
    ui->setupUi(this);
    open();
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
    ui->groupBox_test1Calib->setTitle(QString("Последняя калибровка: %1\n").arg(c_ko4.getDate().toString("dd.MM.yyyy")));
    QString str =
              QString("Номер серия реагентов: %1\n").arg(c_ko4.getReagent_serial())
            + QString("Срок годности реагентов: %1\n").arg(c_ko4.getReagent_date().toString("dd.MM.yyyy"));

    ui->label_test1CalibrString->setText(str);

    ui->lineEdit_test2ReagentSerial->setText(c_ko4.getReagent_serial());
    ui->doubleSpinBox_test2Activity->setValue(c_ko4.getActivity());
    ui->doubleSpinBox_test2TrombineTime->setValue(c_ko4.getTrombine_time());
    ui->doubleSpinBox_test2IncubeTime->setValue(c_ko4.getIncube_time());
    ui->doubleSpinBox_test2WriteTime->setValue(c_ko4.getWrite_time());
    ui->dateEdit_test2Reagent->setDate(c_ko4.getReagent_date());


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

    ui->checkBox_calibCh1->setChecked(c_ko4.getK1());
    ui->checkBox_calibCh1->setChecked(c_ko4.getK2());
    ui->checkBox_calibCh1->setChecked(c_ko4.getK3());
    ui->checkBox_calibCh1->setChecked(c_ko4.getK4());

    ui->dateEdit_calibReagent->setDate(c_ko4.getReagent_date());
    ui->lineEdit_calibReagentSerial->setText(c_ko4.getReagent_serial());
    ui->dateEdit_calibKPlazma->setDate(c_ko4.getK_plazma_date());
    ui->lineEdit_calibKPlazmaSerial->setText(c_ko4.getK_plazma_serial());

    int i = c_ko4.getActivity();
    switch (i) {
    case 1:
        ui->radioButton_calibTrombine1->setChecked(true);
        break;
    case 2:
        ui->radioButton_calibTrombine2->setChecked(true);
        break;
    case 3:
        ui->radioButton_calibTrombine3->setChecked(true);
        break;
    default:
        break;
    }
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
    emit calibration(StartTestKo4::getStart(&t_ko4));
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

    c_ko4.setReagent_serial(ui->lineEdit_test2ReagentSerial->text());
    c_ko4.setActivity(ui->doubleSpinBox_test2Activity->value());
    c_ko4.setTrombine_time(ui->doubleSpinBox_test2TrombineTime->value());
    c_ko4.setIncube_time(ui->doubleSpinBox_test2IncubeTime->value());
    c_ko4.setWrite_time(ui->doubleSpinBox_test2WriteTime->value());
    c_ko4.setReagent_date(ui->dateEdit_test2Reagent->date());
    t_ko4.save();
    emit calibration(StartTestKo4::getStart(&t_ko4));
}

void Ko4::on_pushButton_calib_clicked()
{
    c_ko4.setDate(QDate::currentDate());
    c_ko4.setReagent_date(ui->dateEdit_calibReagent->date());
    c_ko4.setReagent_serial(ui->lineEdit_calibReagentSerial->text().toUtf8());
    c_ko4.setK_plazma_date(ui->dateEdit_calibKPlazma->date());
    c_ko4.setK_plazma_serial(ui->lineEdit_calibKPlazmaSerial->text().toUtf8());
    c_ko4.setIncube_time(ui->doubleSpinBox_calibIncubeTime->value());
    c_ko4.setWrite_time(ui->doubleSpinBox_calibWriteTime->value());

    c_ko4.setK1(ui->checkBox_calibCh1->isChecked());
    c_ko4.setK2(ui->checkBox_calibCh2->isChecked());
    c_ko4.setK3(ui->checkBox_calibCh3->isChecked());
    c_ko4.setK4(ui->checkBox_calibCh4->isChecked());

    c_ko4.save();
    emit calibration(StartCalibrationKo4::getStart(&c_ko4));
}

void Ko4::on_radioButton_calibTrombine1_toggled(bool checked)
{
    c_ko4.setActivity(1);
}

void Ko4::on_radioButton_calibTrombine2_toggled(bool checked)
{
    c_ko4.setActivity(2);
}

void Ko4::on_radioButton_calibTrombine3_toggled(bool checked)
{
    c_ko4.setActivity(3);
}

StartMeasurement* StartCalibrationKo4::getStart(Calibration *c_ko4)
{
    StartMeasurement* start = new StartMeasurement(0);
    start->setChannels(c_ko4->getK1(), c_ko4->getK2(), c_ko4->getK3(), c_ko4->getK4());
    start->setNum(1, "Калибровка");
    start->setNum(2, "Калибровка");
    start->setNum(3, "Калибровка");
    start->setNum(4, "Калибровка");
    start->setTimeWrite(c_ko4->getWrite_time());
    start->setTimeIncube(1, c_ko4->getIncube_time());
    start->setModeID(CalibKo4_ID);
    return start;
}

StartMeasurement* StartTestKo4::getStart(Test* t_ko4)
{
    StartMeasurement *start = new StartMeasurement(0);
    start->setChannels(t_ko4->getK1(), t_ko4->getK2(), t_ko4->getK3(), t_ko4->getK4());
    start->setNum(1, t_ko4->getNum1());
    start->setNum(2, t_ko4->getNum2());
    start->setNum(3, t_ko4->getNum3());
    start->setNum(4, t_ko4->getNum4());
    start->setTimeWrite(t_ko4->getWriteTime());
    start->setTimeIncube(1, t_ko4->getIncubeTime());
    start->setProbe(t_ko4->getSingle());
    start->setModeID(TestKo4_ID);
    return start;
}
