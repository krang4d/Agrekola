#include "calibparam.h"
#include "ui_calibparam.h"

CalibParam::CalibParam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalibParam)
{
    ui->setupUi(this);
}

CalibParam::~CalibParam()
{
    delete ui;
}

void CalibParam::setText(QString str)
{
    ui->label->setText(str);
}
