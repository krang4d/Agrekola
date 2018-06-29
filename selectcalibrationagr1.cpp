#include "selectcalibrationagr1.h"
#include "ui_selectcalibrationagr1.h"

SelectCalibrationAgr1::SelectCalibrationAgr1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectCalibrationAgr1)
{
    ui->setupUi(this);
    selInductor = new SelectInductor;
    //kalibragr2 = new KalibrAgr2;
}

SelectCalibrationAgr1::~SelectCalibrationAgr1()
{
    delete selInductor;
    //delete kalibragr2;
    delete ui;
}

void SelectCalibrationAgr1::on_pushButton_clicked()
{
    if(ui->radioButton_apply->isChecked())
    {
        //selInductor->show();
    }
    else if (ui->radioButton_newCalibration->isChecked())
    {
        //kalibragr2->show();
    }
    else if (ui->radioButton_noCalibration->isChecked())
    {

    }
}
