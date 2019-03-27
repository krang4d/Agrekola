#include "ko2.h"
#include "ui_ko2.h"
#include <QDateTime>
#include <QDate>

Ko2::Ko2(QWidget *parent) :
    QWidget(parent),
    t_ko2_1(new TestKo2(this)),
    t_ko2_2(new TestKo2(WithoutCalibration(), this)),
    c_ko2(new CalibrationKo2),
    ui(new Ui::Ko2)
{
    ui->setupUi(this);
    t_ko2 = t_ko2_1;
    ui->tabWidget->setTabEnabled(0, true);
    open();
    //connect(ui->page_1, SIGNAL(startMeasurment(StartMeasurment*)), this, SIGNAL(measurement(StartMeasurment*)));
    //connect(ui->page_2, &StartMeasurment::startMeasurment, this, &Ko2::measurement);
}

void Ko2::setTab(int i)
{
    ui->tabWidget->setCurrentIndex(i);
}

void Ko2::on_tabWidget_currentChanged(int index)
{
    if(index == 1)
        t_ko2 = t_ko2_1;
    if(index == 2)
        t_ko2 = t_ko2_2;
}

Ko2::~Ko2()
{
    close();
    delete t_ko2_1;
    delete t_ko2_2;
    delete c_ko2;
    delete ui;
}

void Ko2::open()
{
    //окно тест
//    t_ko2_1 = new TestKo2(WithoutCalibration(), this);
//    c_ko2 = new CalibrationKo2(this);
    int i = 0;
    double sum = 0;
    if(c_ko2->getK1()) {
        i++;
        sum+= c_ko2->getA4tv_kp1();
    }
    if(c_ko2->getK2()) {
        i++;
        sum+= c_ko2->getA4tv_kp2();
    }
    if(c_ko2->getK3()) {
        i++;
        sum+= c_ko2->getA4tv_kp3();
    }
    if(c_ko2->getK4()) {
        i++;
        sum+= c_ko2->getA4tv_kp4();
    }
    sum/=i;

    ui->groupBox_test1Calib->setTitle(QString("Последняя калибровка: %1\n")
                                        .arg(c_ko2->getDate().toString("dd.MM.yyyy")));
    QString str = QString("Реагенты: %1 (до %2)\n").arg(c_ko2->getReagent_serial())
                            .arg(c_ko2->getReagent_date().toString("dd.MM.yyyy"))
                + QString("Плазма «К»: %1 (до %2)\n")
                            .arg(c_ko2->getK_plazma_serial())
                            .arg(c_ko2->getK_plazma_date().toString("dd.MM.yyyy"))
//                + QString("АЧТВ к/плазмы 1го канала: %1 с\n").arg(c_ko2->getA4tv_kp1())
//                + QString("АЧТВ к/плазмы 2го канала: %1 с\n").arg(c_ko2->getA4tv_kp2())
//                + QString("АЧТВ к/плазмы 3го канала: %1 с\n").arg(c_ko2->getA4tv_kp3())
//                + QString("АЧТВ к/плазмы 4го канала: %1 с\n").arg(c_ko2->getA4tv_kp4())
                + QString("АЧТВ к/плазмы: %1").arg(sum);

    ui->label_test1CalibString->setText(c_ko2->print());

    if( t_ko2->getSingle() ) {
        ui->radioButton_test1Single->setChecked(true);
    }
    else {
        ui->radioButton_test1Double->setChecked(true);
    }

    if( t_ko2->getK1() ) {
        ui->checkBox_test1Ch1->setChecked(true);
        ui->lineEdit_test1Ch1->setText(t_ko2->getNum1());
    }
    else {
        ui->checkBox_test1Ch1->setChecked(false);
    }

    if( t_ko2->getK2() ) {
        ui->checkBox_test1Ch2->setChecked(true);
        ui->lineEdit_test1Ch2->setText(t_ko2->getNum2());
    }
    else {
        ui->checkBox_test1Ch2->setChecked(false);
    }

    if( t_ko2->getK3() ) {
        ui->checkBox_test1Ch3->setChecked(true);
        ui->lineEdit_test1Ch3->setText(t_ko2->getNum3());
    }
    else {
        ui->checkBox_test1Ch3->setChecked(false);
    }

    if( t_ko2->getK4() ) {
        ui->checkBox_test1Ch4->setChecked(true);
        ui->lineEdit_test1Ch4->setText(t_ko2->getNum4());
    }
    else {
        ui->checkBox_test1Ch4->setChecked(false);
    }

    //дополнительные параметры для окна тест без калибровки
    if( t_ko2_1->getSingle() ) {
        ui->radioButton_test2Single->setChecked(true);
    }
    else {
        ui->radioButton_test2Double->setChecked(true);
    }

    if( t_ko2_1->getK1() ) {
        ui->checkBox_test2Ch1->setChecked(true);
        ui->lineEdit_test2Ch1->setText(t_ko2_1->getNum1());
    }
    else {
        ui->checkBox_test2Ch1->setChecked(false);
    }

    if( t_ko2_1->getK2() ) {
        ui->checkBox_test2Ch2->setChecked(true);
        ui->lineEdit_test2Ch2->setText(t_ko2_1->getNum2());
    }
    else {
        ui->checkBox_test2Ch2->setChecked(false);
    }

    if( t_ko2_1->getK3() ) {
        ui->checkBox_test2Ch3->setChecked(true);
        ui->lineEdit_test2Ch3->setText(t_ko2_1->getNum3());
    }
    else {
        ui->checkBox_test2Ch3->setChecked(false);
    }

    if( t_ko2_1->getK4() ) {
        ui->checkBox_test2Ch4->setChecked(true);
        ui->lineEdit_test2Ch4->setText(t_ko2_1->getNum4());
    }
    else {
        ui->checkBox_test2Ch4->setChecked(false);
    }
    ui->dateEdit_test2Reagent->setDate(t_ko2_1->getReagent_date());
    ui->lineEdit_test2ReagentSerial->setText(t_ko2_1->getReagent_serial());
    ui->doubleSpinBox_test2IncubeTime->setValue(t_ko2_1->getIncube_time());
    ui->doubleSpinBox_test2WriteTime->setValue(t_ko2_1->getWrite_time());
    ui->doubleSpinBox_test2a4tv->setValue(t_ko2_1->getA4tv_kp());

    //окно калибровка
    ui->checkBox_calibCh1->setChecked(c_ko2->getK1());
    ui->checkBox_calibCh2->setChecked(c_ko2->getK2());
    ui->checkBox_calibCh3->setChecked(c_ko2->getK3());
    ui->checkBox_calibCh4->setChecked(c_ko2->getK4());

    ui->doubleSpinBox_calibIncube->setValue(c_ko2->getIncube_time());
    ui->doubleSpinBox_calibWriteTime->setValue(c_ko2->getWrite_time());

    ui->lineEdit_calibKPlazmaSerial->setText(c_ko2->getK_plazma_serial());
    ui->dateEdit_calibPlazma->setDate(c_ko2->getK_plazma_date());
    ui->lineEdit_calibReagentSerial->setText(c_ko2->getReagent_serial());
    ui->dateEdit_calibReagent->setDate(c_ko2->getReagent_date());
    ui->doubleSpinBox_caliba4tv->setValue(c_ko2->getK_plazma_a4tv());
}

void Ko2::close()
{
    c_ko2->save();
    t_ko2_1->save();
    t_ko2_2->save();
    //param.clear();
    //param.replace(0, ui->label_calibrationData->text());
    //param.replace(1, ui->lineEdit_1->text());
    //param.replace(2, ui->lineEdit_2->text());
    //param.replace(3, ui->lineEdit_3->text());
    //param.replace(4, ui->lineEdit_4->text());
    //param.replace(5, ui->lineEdit_5->text());
    //file.saveKo2(param);
}

void Ko2::calibrationDataCome(int n , double data)
{
    static int i = 0;
    //один параметр контрольной нормальной плазмы
    QDate dt = QDate::currentDate();
    c_ko2->setDate(dt);
    switch (n) {
    case 1:
        c_ko2->setA4tv_kp1(data);
        break;
    case 2:
        c_ko2->setA4tv_kp2(data);
        break;
    case 3:
        c_ko2->setA4tv_kp3(data);
        break;
    case 4:
        c_ko2->setA4tv_kp4(data);
        break;
    default:
        break;
    } i++;
    if(i == 4) {
        i = 0;
        emit calibration_done();
    }
    c_ko2->save();
    //ui->label_calibrationData->setText(dt.toString("dd.MM.yyyy ") + dt.toString("hh:mm:ss"));
//    if(param.count() <= n)
//        param.push_back(QString("%1").arg(deta));
//    else param.replace(n, QString("%1").arg(deta));
    //file.saveKo2(param);
}

QString Ko2::t_print()
{
    t_ko2->setDate(QDate::currentDate());
    return t_ko2->print();
}

void Ko2::setT1(double value)
{
    t_ko2->setT1(value);
}

void Ko2::setT2(double value)
{
    t_ko2->setT2(value);
}

void Ko2::setT3(double value)
{
    t_ko2->setT3(value);
}

void Ko2::setT4(double value)
{
    t_ko2->setT4(value);
}

QString Ko2::c_print()
{
    return c_ko2->print();
}

void Ko2::calibrationData1Come(double t0)
{
    calibrationDataCome(1, t0);
}

void Ko2::calibrationData2Come(double t0)
{
    calibrationDataCome(2, t0);
}

void Ko2::calibrationData3Come(double t0)
{
    calibrationDataCome(3, t0);
}

void Ko2::calibrationData4Come(double t0)
{
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
    bool a, b, c, d;
    if(ui->checkBox_test1Ch1->isChecked()) {
        if(!ui->lineEdit_test1Ch1->text().isEmpty()) a = true;
        else a = false;
    }
    else a = true;
    if(ui->checkBox_test1Ch2->isChecked()) {
        if(!ui->lineEdit_test1Ch2->text().isEmpty()) b = true;
        else b = false;
    }
    else b = true;
    if(ui->checkBox_test1Ch3->isChecked()) {
        if(!ui->lineEdit_test1Ch3->text().isEmpty()) c = true;
        else b = false;
    }
    else c = true;
    if(ui->checkBox_test1Ch4->isChecked()) {
        if(!ui->lineEdit_test1Ch4->text().isEmpty()) d = true;
        else d = false;
    }
    else d = true;
    bool e = ui->checkBox_test1Ch1->isChecked() || ui->checkBox_test1Ch2->isChecked()
            || ui->checkBox_test1Ch3->isChecked() || ui->checkBox_test1Ch4->isChecked();

    if (  !( a && b && c && d && e ) ) {
        QMessageBox::information(this,"Внимание!","Для того чтобы продолжить необходимо"
                                                  " выбрать рабочие каналы и заполнить"
                                                  " все поля с параметрами.");
        return;
    }

    bool f = c_ko2->getA4tv_kp1() || c_ko2->getA4tv_kp2()
            || c_ko2->getA4tv_kp3() || c_ko2->getA4tv_kp4();

    if( !(!c_ko2->getDate().toString("dd.MM.yyyy").isEmpty() && f) ) {
        QMessageBox::information(this, "Внимание!", QString("Для того чтобы продолжить необходимо провести калибровку."));
        return;
    }

    t_ko2->setK1(ui->checkBox_test1Ch1->isChecked());
    t_ko2->setK2(ui->checkBox_test1Ch2->isChecked());
    t_ko2->setK3(ui->checkBox_test1Ch3->isChecked());
    t_ko2->setK4(ui->checkBox_test1Ch4->isChecked());

    t_ko2->setNum1(ui->lineEdit_test1Ch1->text());
    t_ko2->setNum2(ui->lineEdit_test1Ch2->text());
    t_ko2->setNum3(ui->lineEdit_test1Ch3->text());
    t_ko2->setNum4(ui->lineEdit_test1Ch4->text());

    t_ko2->setSingle(ui->radioButton_test1Single->isChecked());

    t_ko2->save();
    emit measurement(StartTestKo2::getStart(this));
}

void Ko2::on_pushButton_test2_clicked()
{
    bool a, b, c, d;
    if(ui->checkBox_test2Ch1->isChecked()) {
        if(!ui->lineEdit_test2Ch1->text().isEmpty()) a = true;
        else a = false;
    }
    else a = true;
    if(ui->checkBox_test2Ch2->isChecked()) {
        if(!ui->lineEdit_test2Ch2->text().isEmpty()) b = true;
        else b = false;
    }
    else b = true;
    if(ui->checkBox_test2Ch3->isChecked()) {
        if(!ui->lineEdit_test2Ch3->text().isEmpty()) c = true;
        else b = false;
    }
    else c = true;
    if(ui->checkBox_test2Ch4->isChecked()) {
        if(!ui->lineEdit_test2Ch4->text().isEmpty()) d = true;
        else d = false;
    }
    else d = true;

    bool e = ui->checkBox_test2Ch1->isChecked() || ui->checkBox_test2Ch2->isChecked()
            || ui->checkBox_test2Ch3->isChecked() || ui->checkBox_test2Ch4->isChecked();

    bool f = !ui->lineEdit_test2ReagentSerial->text().isEmpty();

    if ( !( a && b && c && d && e && f) ) {
        QMessageBox::information(this, "Внимание!", "Для того чтобы продолжить необходимо"
                                                    " выбрать рабочие каналы"
                                                    " и заполнить все поля с параметрами!");
        return;
    }

    t_ko2_1->setK1(ui->checkBox_test2Ch1->isChecked());
    t_ko2_1->setK2(ui->checkBox_test2Ch2->isChecked());
    t_ko2_1->setK3(ui->checkBox_test2Ch3->isChecked());
    t_ko2_1->setK4(ui->checkBox_test2Ch4->isChecked());

    t_ko2_1->setNum1(ui->lineEdit_test2Ch1->text());
    t_ko2_1->setNum2(ui->lineEdit_test2Ch2->text());
    t_ko2_1->setNum3(ui->lineEdit_test2Ch3->text());
    t_ko2_1->setNum4(ui->lineEdit_test2Ch4->text());

    t_ko2_1->setSingle(ui->radioButton_test2Single->isChecked());

    t_ko2_1->setIncube_time(ui->doubleSpinBox_test2IncubeTime->value());
    t_ko2_1->setWrite_time(ui->doubleSpinBox_test2WriteTime->value());
    t_ko2_1->setA4tv_kp(ui->doubleSpinBox_test2a4tv->value());
    t_ko2_1->setReagent_date(ui->dateEdit_test2Reagent->date());
    t_ko2_1->setReagent_serial(ui->lineEdit_test2ReagentSerial->text());
    t_ko2_1->setDate(QDate::currentDate());

    t_ko2_1->save();

    emit measurement(StartTestKo2::getStart(this));
}

void Ko2::on_pushButton_calib_clicked()
{
    bool a = ui->checkBox_calibCh1->isChecked();
    bool b = ui->checkBox_calibCh2->isChecked();
    bool c = ui->checkBox_calibCh3->isChecked();
    bool d = ui->checkBox_calibCh4->isChecked();

    bool e = !ui->lineEdit_calibKPlazmaSerial->text().isEmpty();
    bool f = !ui->lineEdit_calibReagentSerial->text().isEmpty();

    if( !((a || b || c || d ) && e && f) ) {
        QMessageBox::information(this, "Внимание!", "Для того чтобы продолжить необходимо"
                                                    " выбрать рабочие каналы"
                                                    " и заполнить все поля с параметрами!");
        return;
    }

    QDate now = QDate::currentDate();
    bool g = now <= ui->dateEdit_calibPlazma->date();

    bool i = now <= ui->dateEdit_calibReagent->date();

    if(!(g && i) ) {
        QMessageBox::information(this, "Внимание!", "Проверьте срок годности используемых реагентов!");
        return;
    }

    c_ko2->setDate(QDate::currentDate());
    c_ko2->setReagent_date(ui->dateEdit_calibReagent->date());
    c_ko2->setReagent_serial(ui->lineEdit_calibReagentSerial->text());
    c_ko2->setK_plazma_date(ui->dateEdit_calibPlazma->date());
    c_ko2->setK_plazma_serial(ui->lineEdit_calibKPlazmaSerial->text());
    c_ko2->setK_plazma_a4tv(ui->doubleSpinBox_test2a4tv->value());
    c_ko2->setIncube_time(ui->doubleSpinBox_calibIncube->value());
    c_ko2->setWrite_time(ui->doubleSpinBox_calibWriteTime->value());

    c_ko2->setK1(ui->checkBox_calibCh1->isChecked());
    c_ko2->setK2(ui->checkBox_calibCh2->isChecked());
    c_ko2->setK3(ui->checkBox_calibCh3->isChecked());
    c_ko2->setK4(ui->checkBox_calibCh4->isChecked());

    c_ko2->save();
    emit calibration(StartCalibrationKo2::getStart(this));
}

StartMeasurement* StartCalibrationKo2::getStart(Ko2* widget)
{
    CalibrationKo2* c_ko2 = widget->c_ko2;
    StartMeasurement* start = new StartMeasurement(0);
    //start->setObj(widget);
    start->setChannels(c_ko2->getK1(), c_ko2->getK2(), c_ko2->getK3(), c_ko2->getK4());
    start->setNum(1, "к/плазма");
    start->setNum(2, "к/плазма");
    start->setNum(3, "к/плазма");
    start->setNum(4, "к/плазма");
    start->setTimeWrite(c_ko2->getWrite_time());
    start->setTimeIncube(1, c_ko2->getIncube_time());
    start->setModeID(CalibKo2_ID);
    //stKo2->cancel = false;
    return start;
}

StartMeasurement* StartTestKo2::getStart(Ko2 *widget)
{
    TestKo2* t_ko2 = widget->t_ko2;
    CalibrationKo2* c_ko2 = widget->c_ko2;
    StartMeasurement* start = new StartMeasurement(0);
    start->setChannels(t_ko2->getK1(), t_ko2->getK2(), t_ko2->getK3(), t_ko2->getK4());
    start->setNum(1, t_ko2->getNum1());
    start->setNum(2, t_ko2->getNum2());
    start->setNum(3, t_ko2->getNum3());
    start->setNum(4, t_ko2->getNum4());
    start->setTimeWrite(c_ko2->getWrite_time());
    start->setTimeIncube(1, c_ko2->getIncube_time());
    start->setProbe(t_ko2->getSingle());          //одиночные пробы
    start->setModeID(TestKo2_ID);
    //stKo2->cancel = false;
    return start;
}
