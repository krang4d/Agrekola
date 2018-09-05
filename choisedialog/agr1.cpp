#include "agr1.h"
#include "ui_agr1.h"

Agr1::Agr1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Agr1)
{
    ui->setupUi(this);
    ui->page_2->setMode(1);
    file.openAgr1(param);
    if( !param.isEmpty() && param.count() >= 3 ) { //3 парамеьра
        ui->lineEdit_1->setText(param.at(0));
        ui->lineEdit_2->setText(param.at(1));
        ui->lineEdit_3->setText(param.at(2));
        connect(ui->page_2, &StartMeasurment::startMeasurment, this, &Agr1::measurement);
    }
}

Agr1::~Agr1()
{
    //param.clear();
    param.replace(0, ui->lineEdit_1->text());
    param.replace(1, ui->lineEdit_2->text());
    param.replace(2, ui->lineEdit_3->text());
    file.saveAgr1(param);
    delete ui;
}

void Agr1::on_startButton_clicked()
{
    emit measurement(ui->page_2);
}

void Agr1::on_kolibrButton_clicked()
{
    emit calibration();
}
