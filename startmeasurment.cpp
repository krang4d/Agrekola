#include "startmeasurment.h"
#include "ui_startmeasurment.h"

#include <QMessageBox>
#include <QString>

StartMeasurment::StartMeasurment(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::StartMeasurment)
{
    ui->setupUi(this);
    setModal(true);
    setMode(0);
    cancel = true;
    single = true;
    channel_1 = false;
    channel_2 = false;
    channel_3 = false;
    channel_4 = false;
    num_1 = "";
    num_2 = "";
    num_3 = "";
    num_4 = "";
    time = 0;
    time_incube = 0;

    openData();
    ui->label_iname->setVisible(false);
    ui->lineEdit_iname->setVisible(false);
}

StartMeasurment::StartMeasurment(int mode, QDialog *parent) :
    StartMeasurment(parent)
{
    setMode(mode);
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
          << ui->lineEdit_ch1->text()
          << ui->lineEdit_ch2->text()
          << ui->lineEdit_ch3->text()
          << ui->lineEdit_ch4->text()
          << ui->lineEdit_incube->text()
          << ui->lineEdit_time->text()
          << ui->lineEdit_incube_2->text();
    file.saveStartWin(param);
}

void StartMeasurment::openData()
{
    file.openStartWin(param);
    if( !param.isEmpty() && param.count() >= 11 ) {
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
        ui->lineEdit_incube_2->setText(param.at(10));
    }
}

bool StartMeasurment::isChannel(int ch)
{
    switch (ch) {
    case 0:
        return channel_1 || channel_2 ||channel_3 || channel_4;
        break;
    case 1:
        return channel_1;
        break;
    case 2:
        return channel_2;
        break;
    case 3:
        return channel_3;
        break;
    case 4:
        return channel_4;
        break;
    default:
        return channel_1 || channel_2 ||channel_3 || channel_4;
    }
}

void StartMeasurment::setChannels(bool ch1, bool ch2, bool ch3, bool ch4)
{
    num = 0;
    if(ch1) num++;
    if(ch2) num++;
    if(ch3) num++;
    if(ch4) num++;
    channel_1 = ch1;
    channel_2 = ch2;
    channel_3 = ch3;
    channel_4 = ch4;
    if( ch1 || ch2 || ch3 || ch4 ) {
        cancel = false;
    }else cancel = true;
}

void StartMeasurment::setMode(int mode, bool s)
{
    single = s;
    if(mode == 1 || mode == 2 ) {
        ui->lineEdit_incube_2->setVisible(true);
        ui->label_incube_2->setVisible(true);
        ui->label_incube->setText(QString("Время инкубации 1"));
        ui->comboBox_inductor->setVisible(true);
        ui->label_itype->setVisible(true);
    }
    else {
        ui->lineEdit_incube_2->setVisible(false);
        ui->label_incube_2->setVisible(false);
        ui->label_incube->setText(QString("Время инкубации"));
        ui->comboBox_inductor->setVisible(false);
        ui->label_itype->setVisible(false);
    }
}

bool StartMeasurment::isCancel()
{
    return cancel;
}

bool StartMeasurment::isSingle()
{
    return single;
}

QString StartMeasurment::getNum(const int ch)
{
    switch ( ch ) {
    case 1:
        return num_1;
        break;
    case 2:
        return num_2;
        break;
    case 3:
        return num_3;
        break;
    case 4:
        return num_4;
        break;
    default:
        return 0;
    }
    return num_1;
}

void StartMeasurment::setNum(const int ch, const QString num)
{
    switch ( ch ) {
    case 1:
        num_1 = num;
        break;
    case 2:
        num_2 = num;
        break;
    case 3:
        num_3 = num;
        break;
    case 4:
        num_4 = num;
        break;
    default:
        return;
    }
}

int StartMeasurment::getTime()
{
    return time;
}

void StartMeasurment::setTime(int ts)
{
    time = ts;
}

int StartMeasurment::getTimeIncube(int i)
{
    if(i == 1)
        return time_incube;
    else return time_incube_2;
}

void StartMeasurment::setTimeIncube(int i, int ts)
{
    if(i == 1)
        time_incube = ts;
    else time_incube_2 = ts;
}

QString StartMeasurment::getStringStatus()
{
    QString msg;
    if(isSingle()) {
        if (isChannel(1)) {
            msg += QString("№1 = %1, ").arg(getNum(1));
        }
        else {
            msg += QString("№1 - выкл., ");
        }

        if (isChannel(2)) {
            msg += QString("№2 = %1, ").arg(getNum(2));
        }
        else {
            msg += QString("№2 - выкл., ");
        }

        if (isChannel(3)) {
            msg += QString("№3 = %1, ").arg(getNum(3));
        }
        else {
            msg += QString("№3 - выкл., ");
        }

        if (isChannel(4)) {
            msg += QString("№4 = %1 ").arg(getNum(4));
        }
        else {
            msg += QString("№4 - выкл. ");
        }
//        //---->> магические числа для времени инкубации 2
//        if(getMode() == 1 && getMode() == 2) {
//            msg = QString("Начало сбора данных, одиночные пробы (t = %1c, %2)")
//                    .arg(startWin->getTime()).arg(msg);
//        }
        msg = QString("Одиночные пробы (t = %1c, %2)")
                .arg(getTime()).arg(msg);
    }
    else {
        if (isChannel(1)) {
            msg += QString("№1, 2 = %1, ").arg(getNum(1));
        }
        else {
            msg += QString("№1, 2 - выкл., ");
        }

        if (isChannel(3)) {
            msg += QString("№3, 4 = %1, ").arg(getNum(3));
        }
        else {
            msg += QString("№3, 4 - выкл., ");
        }
        msg = QString("Парные пробы (t = %1c, %2)")
                .arg(getTime()).arg(msg);
    }
    return msg;
}

void StartMeasurment::on_checkBox_ch1_stateChanged(int arg1)
{
    if(arg1) {
        ui->lineEdit_ch1->setEnabled(true);
        channel_1 = true;
    }
    else {
        ui->lineEdit_ch1->setEnabled(false);
        channel_1 = false;
    }
}

void StartMeasurment::on_checkBox_ch2_stateChanged(int arg1)
{
    if(arg1) {
        ui->lineEdit_ch2->setEnabled(true);
        channel_2 = true;
    }
    else {
        ui->lineEdit_ch2->setEnabled(false);
        channel_2 = false;
    }
}

void StartMeasurment::on_checkBox_ch3_stateChanged(int arg1)
{
    if(arg1) {
        ui->lineEdit_ch3->setEnabled(true);
        channel_3 = true;
    }
    else {
        ui->lineEdit_ch3->setEnabled(false);
        channel_3 = false;
    }
}

void StartMeasurment::on_checkBox_ch4_stateChanged(int arg1)
{
    if(arg1) {
        ui->lineEdit_ch4->setEnabled(true);
        channel_4 = true;
    }
    else {
        ui->lineEdit_ch4->setEnabled(false);
        channel_4 = false;
    }
}

void StartMeasurment::on_radioButton_single_toggled(bool checked)
{
    ui->checkBox_ch1->setCheckState(Qt::Unchecked);
    ui->checkBox_ch2->setCheckState(Qt::Unchecked);
    ui->checkBox_ch3->setCheckState(Qt::Unchecked);
    ui->checkBox_ch4->setCheckState(Qt::Unchecked);
    //QMessageBox::information(0, "StartMeasurment", QString("on_radioButton_single_toggled(%1)").arg(checked));
    if(checked){
        single = true;
        ui->checkBox_ch1->setText("Канал 1");
        ui->checkBox_ch2->setText("Канал 2");
        ui->checkBox_ch2->setVisible(true);
        ui->lineEdit_ch2->setVisible(true);
        ui->checkBox_ch3->setText("Канал 3");
        ui->checkBox_ch4->setText("Канал 4");
        ui->checkBox_ch4->setVisible(true);
        ui->lineEdit_ch4->setVisible(true);
        disconnect(ui->checkBox_ch1, SIGNAL(stateChanged(int)), this, SLOT(setCheckState2(int)));
        disconnect(ui->checkBox_ch3, SIGNAL(stateChanged(int)), this, SLOT(setCheckState4(int)));
    }
    else{
        single = false;
        ui->checkBox_ch1->setEnabled(true);
        ui->checkBox_ch1->setText("Канал 1, 2");

        ui->checkBox_ch2->setVisible(false);
        ui->lineEdit_ch2->setVisible(false);

        ui->checkBox_ch3->setEnabled(true);
        ui->checkBox_ch3->setText("Канал 3, 4");

        ui->checkBox_ch4->setVisible(false);
        ui->lineEdit_ch4->setVisible(false);
        connect(ui->checkBox_ch1, SIGNAL(stateChanged(int)), this, SLOT(setCheckState2(int)));
        connect(ui->checkBox_ch3, SIGNAL(stateChanged(int)), this, SLOT(setCheckState4(int)));
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
    if(channel_1)
        num_1 = ui->lineEdit_ch1->text();

    if(channel_2) {
        if(!single) num_2 = num_1;
        else num_2 = ui->lineEdit_ch2->text();
    }
    if(channel_3)
        num_3 = ui->lineEdit_ch3->text();

    if(channel_4) {
        if(!single) num_4 = num_3;
        else num_4 = ui->lineEdit_ch4->text();
    }

    int t = ui->lineEdit_time->text().toInt();
    if( !(t>=5 && t<=900) ) {
        QMessageBox::information(this, "Агрекола-4к",
        "Время заиси должно быть в диапазоне от 5 до 900 секунд");
        return;
    }
    time = ui->lineEdit_time->text().toInt();
    time_incube = ui->lineEdit_incube->text().toInt();
    time_incube_2 = ui->lineEdit_incube_2->text().toInt();

    mb.setInformativeText("Введите недостающие данные о проводимом исследовании");
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
        //hide();
        emit startMeasurment(this);
    }
    saveData();
}

void StartMeasurment::on_comboBox_inductor_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "Другой") {
        ui->lineEdit_iname->setVisible(true);
        ui->label_iname->setVisible(true);
    }
    else
    {
        ui->lineEdit_iname->setVisible(false);
        ui->label_iname->setVisible(false);
    }
}

Mode_ID StartMeasurment::getMode() const
{
    return mode;
}
