#include "ko1.h"
#include "ui_ko1.h"

Ko1::Ko1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ko1)
{
    ui->setupUi(this);
    qDebug() << "Current path: " << QDir::currentPath() << t_ko1.getK1();
    ui->checkBox_ch1->setChecked(t_ko1.getK1());
    ui->lineEdit_ch1->setText(t_ko1.getNum1());
    ui->checkBox_ch2->setChecked(t_ko1.getK2());
    ui->lineEdit_ch2->setText(t_ko1.getNum2());
    ui->checkBox_ch3->setChecked(t_ko1.getK3());
    ui->lineEdit_ch3->setText(t_ko1.getNum3());
    ui->checkBox_ch4->setChecked(t_ko1.getK4());
    ui->lineEdit_ch4->setText(t_ko1.getNum4());
    t_ko1.getSingle() ? ui->radioButton_single->setChecked(true) : ui->radioButton_double->setChecked(false);

//    file.openKo1(param);
//    if(!param.isEmpty() && param.count() >= 2) {
//        ui->lineEdit_1->setText(param.at(0));
//        ui->lineEdit_2->setText(param.at(1));
//    }
    //startPar = ui->widget;
    //connect(ui->widget, SIGNAL(startMeasurment(StartMeasurment*)), this, SIGNAL(measurement(StartMeasurment*)));
    //connect(ui->widget, &StartMeasurment::startMeasurment, this, &Ko1::measurement);
}

Ko1::~Ko1()
{
    //param.clear();
//    param.replace(0, ui->lineEdit_1->text());
//    param.replace(1, ui->lineEdit_2->text());
//    file.saveKo1(param);
    delete ui;
}

void Ko1::on_pushButton_clicked()
{
    t_ko1.setK1(ui->checkBox_ch1->isChecked()); // int(ui->checkBox_ch1->isChecked()));
    t_ko1.setNum1(ui->lineEdit_ch1->text());
    t_ko1.setK2(ui->checkBox_ch2->isChecked());
    t_ko1.setNum2(ui->lineEdit_ch2->text());
    t_ko1.setK3(ui->checkBox_ch3->isChecked());
    t_ko1.setNum3(ui->lineEdit_ch3->text());
    t_ko1.setK4(ui->checkBox_ch4->isChecked());
    t_ko1.setNum4(ui->lineEdit_ch4->text());
    t_ko1.setSingle(ui->radioButton_single->isChecked());
    t_ko1.save();
    qDebug() << t_ko1.getK1();
    qDebug() << "Current path: " << QDir::currentPath();
    emit measurement(StartTestKo1::getStart());
}

void Ko1::on_checkBox_ch1_stateChanged(int arg1)
{
    ui->lineEdit_ch1->setEnabled(arg1);
}

void Ko1::on_checkBox_ch2_stateChanged(int arg1)
{
    ui->lineEdit_ch2->setEnabled(arg1);
}

void Ko1::on_checkBox_ch3_stateChanged(int arg1)
{
    ui->lineEdit_ch3->setEnabled(arg1);
}

void Ko1::on_checkBox_ch4_stateChanged(int arg1)
{
    ui->lineEdit_ch4->setEnabled(arg1);
}

StartMeasurment *StartTestKo1::getStart()
{

    StartMeasurment *sm = new StartMeasurment(0);
    sm->setModeID(TestKo1_ID); //режим определение времени свертывания
    sm->setMode(0, 1); //одиночные пробы
    sm->setChannels(true, true, true, true);
    sm->setNum(1, "Проверка");
    sm->setNum(2, "Проверка");
    sm->setNum(3, "Проверка");
    sm->setNum(4, "Проверка");
    sm->setTime(10);
    sm->setTimeIncube(1, 3);
    //stKo2->cancel = false;
    return sm;
}

StartMeasurment *StartCalibrationKo1::getStart()
{

}
