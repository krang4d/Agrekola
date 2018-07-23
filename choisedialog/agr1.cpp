#include "agr1.h"
#include "ui_agr1.h"

Agr1::Agr1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Agr1)
{
    ui->setupUi(this);
    file.openAgr1(param);
    if( !param.isEmpty() && param.count() == 3 ) { //3 парамеьра
        ui->lineEdit_1->setText(param.at(0));
        ui->lineEdit_2->setText(param.at(1));
        ui->lineEdit_3->setText(param.at(2));
    }
}

Agr1::~Agr1()
{
    param.clear();
    param << ui->lineEdit_1->text() << ui->lineEdit_2->text() << ui->lineEdit_3->text();
    file.saveAgr1(param);
    delete ui;
}

void Agr1::on_startButton_clicked()
{
    emit measurement();
}

void Agr1::on_kolibrButton_clicked()
{
    emit calibration();
}
