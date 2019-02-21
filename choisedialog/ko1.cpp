#include "ko1.h"
#include "ui_ko1.h"

Ko1::Ko1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ko1)
{
    ui->setupUi(this);
    qDebug() << "Current path: " << QDir::currentPath() << t_ko1.getK1();
    if( t_ko1.getSingle() ) {
        ui->radioButton_testSingle->setChecked(true);
    }
    else {
        ui->radioButton_testDouble->setChecked(true);
    }

    if( t_ko1.getK1() ) {
        ui->checkBox_testCh1->setChecked(true);
        ui->lineEdit_testCh1->setText(t_ko1.getNum1());
    }
    else ui->checkBox_testCh1->setChecked(false);

    if( t_ko1.getK2() ) {
        ui->checkBox_testCh2->setChecked(true);
        ui->lineEdit_testCh2->setText(t_ko1.getNum2());
    }
    else ui->checkBox_testCh2->setChecked(false);

    if( t_ko1.getK3() ) {
        ui->checkBox_testCh3->setChecked(true);
        ui->lineEdit_testCh3->setText(t_ko1.getNum3());
    }
    else ui->checkBox_testCh3->setChecked(false);

    if( t_ko1.getK4() ) {
        ui->checkBox_testCh4->setChecked(true);
        ui->lineEdit_testCh4->setText(t_ko1.getNum4());
    }
    else ui->checkBox_testCh4->setChecked(false);

    ui->doubleSpinBox_testIncubeTime->setValue(c_ko1.getIncube_time());
    ui->doubleSpinBox_testWriteTime->setValue(c_ko1.getWrite_time());
}

Ko1::~Ko1()
{
    delete ui;
}

void Ko1::on_checkBox_testCh1_toggled(bool checked)
{
    ui->lineEdit_testCh1->setEnabled(checked);
    if(ui->radioButton_testDouble->isChecked())
        ui->checkBox_testCh2->setChecked(checked);
}

void Ko1::on_checkBox_testCh2_toggled(bool checked)
{
    if(ui->radioButton_testSingle->isChecked())
        ui->lineEdit_testCh2->setEnabled(checked);
}

void Ko1::on_checkBox_testCh3_toggled(bool checked)
{
    ui->lineEdit_testCh3->setEnabled(checked);
    if(ui->radioButton_testDouble->isChecked())
        ui->checkBox_testCh4->setChecked(checked);
}

void Ko1::on_checkBox_testCh4_toggled(bool checked)
{
    if(ui->radioButton_testSingle->isChecked())
        ui->lineEdit_testCh4->setEnabled(checked);
}

void Ko1::on_radioButton_testSingle_toggled(bool checked)
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

void Ko1::on_lineEdit_testCh1_textChanged(const QString &arg1)
{
    if(ui->radioButton_testDouble->isChecked())
        ui->lineEdit_testCh2->setText(arg1);
}

void Ko1::on_lineEdit_testCh3_textChanged(const QString &arg1)
{
    if(ui->radioButton_testDouble->isChecked())
        ui->lineEdit_testCh4->setText(arg1);
}

void Ko1::on_pushButton_test_clicked()
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
    //bool c = (ui->doubleSpinBox_testIncubeTime->value() != NULL) && (ui->doubleSpinBox_testWriteTime->value() != NULL);
    if ( !(a || b || c || d) ) {
        QMessageBox::information(this, "Внимание!", "Для того чтобы продолжить необходимо выбрать рабочие каналы и заполнить все поля с параметрами!");
        return;
    }
    //if()
    t_ko1.setK1(ui->checkBox_testCh1->isChecked());
    t_ko1.setK2(ui->checkBox_testCh2->isChecked());
    t_ko1.setK3(ui->checkBox_testCh3->isChecked());
    t_ko1.setK4(ui->checkBox_testCh4->isChecked());

    t_ko1.setNum1(ui->lineEdit_testCh1->text());
    t_ko1.setNum2(ui->lineEdit_testCh2->text());
    t_ko1.setNum3(ui->lineEdit_testCh3->text());
    t_ko1.setNum4(ui->lineEdit_testCh4->text());

    t_ko1.setSingle(ui->radioButton_testSingle->isChecked());

    c_ko1.setIncube_time(ui->doubleSpinBox_testIncubeTime->value());
    c_ko1.setWrite_time(ui->doubleSpinBox_testWriteTime->value());
    c_ko1.setDate(QDate::currentDate());

    t_ko1.save();
    c_ko1.save();

    emit measurement(StartTestKo1::getStart(&t_ko1));
}

StartMeasurement* StartTestKo1::getStart(Test* t_ko1)
{
    StartMeasurement* start = new StartMeasurement(0);
    start->setModeID(TestKo1_ID);  //режим определение времени свертывания
    start->setProbe(t_ko1->getSingle());          //одиночные пробы
    start->setChannels(t_ko1->getK1(), t_ko1->getK2(), t_ko1->getK3(), t_ko1->getK4());
    start->setNum(1, t_ko1->getNum1());
    start->setNum(2, t_ko1->getNum2());
    start->setNum(3, t_ko1->getNum3());
    start->setNum(4, t_ko1->getNum4());

    start->setTimeWrite(t_ko1->getWriteTime());
    start->setTimeIncube(1, t_ko1->getIncubeTime());
    //stKo2->cancel = false;
    return start;
}
