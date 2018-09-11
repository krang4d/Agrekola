#include "agr2.h"
#include "ui_agr2.h"

Agr2::Agr2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Agr2)
{
    ui->setupUi(this);
    ui->page_2->setMode(2);
    file.openAgr2(param);
    if( !param.isEmpty() && param.count() >= 7 ) {
        ui->label_calibrationData->setText(param.at(0));
        ui->lineEdit_1->setText(param.at(1));
        ui->lineEdit_2->setText(param.at(2));
        ui->lineEdit_3->setText(param.at(3));
        ui->lineEdit_4->setText(param.at(4));
        ui->lineEdit_5->setText(param.at(5));
        ui->lineEdit_6->setText(param.at(6));
    }
    selcalibrAgr1 = new SelectCalibrationAgr1();
    selInductor = new SelectInductor();
    connect(ui->page_2, &StartMeasurment::startMeasurment, this, &Agr2::measurement);
}

Agr2::~Agr2()
{
    //param.clear();
    if(param.count() == 0) param = QStringList({0, 0, 0, 0, 0, 0, 0});
    param.replace(0, ui->label_calibrationData->text());
    param.replace(1, ui->lineEdit_1->text());
    param.replace(2, ui->lineEdit_2->text());
    param.replace(3, ui->lineEdit_3->text());
    param.replace(4, ui->lineEdit_4->text());
    param.replace(5, ui->lineEdit_5->text());
    param.replace(6, ui->lineEdit_6->text());
    file.saveAgr2(param);
    //delete kalibragr2;
    delete selInductor;
    delete selcalibrAgr1;
    delete ui;
}

void Agr2::on_calibrButton_clicked()
{
    //kalibragr2 = new KalibrAgr2();
    //kalibragr2->show();
    emit calibration(ui->page_2);
}
