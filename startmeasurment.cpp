#include "startmeasurment.h"
#include "ui_startmeasurment.h"

#include <QMessageBox>
#include <QString>

StartMeasurment::StartMeasurment(int mode, QDialog *parent) :
    QDialog(parent),
    ui(new Ui::StartMeasurment)
{
    ui->setupUi(this);
    setModal(true);
    file.openStartWin(param);
    if( !param.isEmpty() && param.count() == 10 ) {
        QString(param.at(0)).toInt();
        ui->checkBox_ch1->setCheckState(static_cast<Qt::CheckState>(QString(param.at(0)).toInt()));
        ui->checkBox_ch2->setCheckState(static_cast<Qt::CheckState>(QString(param.at(1)).toInt()));
        ui->checkBox_ch3->setCheckState(static_cast<Qt::CheckState>(QString(param.at(2)).toInt()));
        ui->checkBox_ch4->setCheckState(static_cast<Qt::CheckState>(QString(param.at(3)).toInt()));
        ui->lineEdit_ch1->setText(param.at(4));
        ui->lineEdit_ch2->setText(param.at(5));
        ui->lineEdit_ch3->setText(param.at(6));
        ui->lineEdit_ch4->setText(param.at(7));
        ui->lineEdit_incube->setText(param.at(8));
        ui->lineEdit_time->setText(param.at(9));
    }
    cancel = true;
    single = true;
    channel_1 = false;
    channel_2 = false;
    channel_3 = false;
    channel_4 = false;
    num_1 = 0;
    num_2 = 0;
    num_3 = 0;
    num_4 = 0;
    time = 0;
    time_incube = 0;
    if(mode == 1 || mode == 2 ) {
        ui->lineEdit_incube_2->setVisible(true);
        ui->label_incube_2->setVisible(true);
        ui->label_incube->setText(QString("Время инкубации 1"));

    }
    else {
        ui->lineEdit_incube_2->setVisible(false);
        ui->label_incube_2->setVisible(false);
        ui->label_incube->setText(QString("Время инкубации"));
    }
}

StartMeasurment::~StartMeasurment()
{
    saveData();
    delete ui;
}


void StartMeasurment::saveData()
{
    param.clear();
    param << QString("%1").arg(static_cast<int>(ui->checkBox_ch1->checkState()))
          << QString("%1").arg(static_cast<int>(ui->checkBox_ch2->checkState()))
          << QString("%1").arg(static_cast<int>(ui->checkBox_ch3->checkState()))
          << QString("%1").arg(static_cast<int>(ui->checkBox_ch4->checkState()))
          << ui->lineEdit_ch1->text() << ui->lineEdit_ch2->text()
          << ui->lineEdit_ch3->text() << ui->lineEdit_ch4->text()
          << ui->lineEdit_incube->text() << ui->lineEdit_time->text();
    file.saveStartWin(param);
}

bool StartMeasurment::isCancel()
{
    return cancel;
}

bool StartMeasurment::isSingle()
{
    return single;
}

bool StartMeasurment::isChannel_1()
{
    return channel_1;
}

bool StartMeasurment::isChannel_2()
{
    return channel_2;
}

bool StartMeasurment::isChannel_3()
{
    return channel_3;
}

bool StartMeasurment::isChannel_4()
{
    return channel_4;
}

int StartMeasurment::getNum_1()
{
    return num_1;
}

int StartMeasurment::getNum_2()
{
    return num_2;
}

int StartMeasurment::getNum_3()
{
    return num_3;
}

int StartMeasurment::getNum_4()
{
    return num_4;
}

int StartMeasurment::getTime()
{
    return time;
}

int StartMeasurment::getTimeIncube(int i)
{
    if(i == 1)
        return time_incube;
    else return time_incube_2;
}

QString StartMeasurment::getStringStatus()
{
    return QString("");
}

void StartMeasurment::on_checkBox_ch1_stateChanged(int arg1)
{
    if(arg1) ui->lineEdit_ch1->setEnabled(true);
    else ui->lineEdit_ch1->setEnabled(false);
}

void StartMeasurment::on_checkBox_ch2_stateChanged(int arg1)
{
    if(arg1) ui->lineEdit_ch2->setEnabled(true);
    else ui->lineEdit_ch2->setEnabled(false);
}

void StartMeasurment::on_checkBox_ch3_stateChanged(int arg1)
{
    if(arg1) ui->lineEdit_ch3->setEnabled(true);
    else ui->lineEdit_ch3->setEnabled(false);
}

void StartMeasurment::on_checkBox_ch4_stateChanged(int arg1)
{
    if(arg1) ui->lineEdit_ch4->setEnabled(true);
    else ui->lineEdit_ch4->setEnabled(false);
}

void StartMeasurment::on_radioButton_single_toggled(bool checked)
{
    ui->checkBox_ch1->setCheckState(Qt::Unchecked);
    ui->checkBox_ch2->setCheckState(Qt::Unchecked);
    ui->checkBox_ch3->setCheckState(Qt::Unchecked);
    ui->checkBox_ch4->setCheckState(Qt::Unchecked);
   // ui->lineEdit_ch1->setText("");
   // ui->lineEdit_ch2->setText("");
   // ui->lineEdit_ch3->setText("");
   // ui->lineEdit_ch4->setText("");

    if(checked){
        ui->checkBox_ch1->setText("Канал 1");
        ui->checkBox_ch2->setText("Канал 2");
        ui->checkBox_ch2->setVisible(true);
        ui->lineEdit_ch2->setVisible(true);
        ui->checkBox_ch3->setText("Канал 3");
        ui->checkBox_ch4->setText("Канал 4");
        ui->checkBox_ch4->setVisible(true);
        ui->lineEdit_ch4->setVisible(true);
    }
    else{
        ui->checkBox_ch1->setEnabled(true);
        ui->checkBox_ch1->setText("Канал 1, 2");

        ui->checkBox_ch2->setVisible(false);
        ui->lineEdit_ch2->setVisible(false);

        ui->checkBox_ch3->setEnabled(true);
        ui->checkBox_ch3->setText("Канал 3, 4");

        ui->checkBox_ch4->setVisible(false);
        ui->lineEdit_ch4->setVisible(false);
    }
}

void StartMeasurment::on_pushButton_next_clicked()
{
    QMessageBox mb;
    mb.setIcon(QMessageBox::Information);
    mb.setInformativeText("Не выбран канал измерения!");
    if(ui->checkBox_ch1->isChecked() || ui->checkBox_ch2->isChecked() ||\
            ui->checkBox_ch3->isChecked() || ui->checkBox_ch4->isChecked());
    else {
        mb.exec();
        return;
    }
    single = ui->radioButton_single->isChecked();           //пробы одиночные?
    channel_1 = ui->checkBox_ch1->isChecked();
    if(channel_1)
        num_1 = ui->lineEdit_ch1->text().toInt();

    channel_2 = ui->checkBox_ch2->isChecked();
    if(channel_2)
        num_2 = ui->lineEdit_ch2->text().toInt();

    channel_3 = ui->checkBox_ch3->isChecked();
    if(channel_3)
        num_3 = ui->lineEdit_ch3->text().toInt();

    channel_4 = ui->checkBox_ch4->isChecked();
    if(channel_4)
        num_4 = ui->lineEdit_ch4->text().toInt();

    int t = ui->lineEdit_time->text().toInt();
    if( !(t>=5 && t<=900) ) {
        QMessageBox::information(this, "Агрекола-4к",
        "Время заиси должно быть в диапазоне от 5 до 900 секунд");
        return;
    }
    time = ui->lineEdit_time->text().toInt();
    time_incube = ui->lineEdit_incube->text().toInt();
    time_incube_2 = ui->lineEdit_incube_2->text().toInt();

    mb.setInformativeText("Введите номер пробы!");
    if(ui->checkBox_ch1->isChecked() && ui->lineEdit_ch1->text().isEmpty())
        mb.exec();
    else if(ui->checkBox_ch2->isChecked() && ui->lineEdit_ch2->text().isEmpty())
        mb.exec();
    else if(ui->checkBox_ch3->isChecked() && ui->lineEdit_ch3->text().isEmpty())
        mb.exec();
    else if(ui->checkBox_ch4->isChecked() && ui->lineEdit_ch4->text().isEmpty())
        mb.exec();
    else {
        cancel = false;
        hide();
        emit startMeasurment();
    }
    saveData();
}

void StartMeasurment::on_pushButton_cancel_clicked()
{
    cancel = true;
    hide();
}
