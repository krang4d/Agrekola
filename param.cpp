#include "param.h"
#include "ui_param.h"

Param::Param(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Param)
{
    ui->setupUi(this);
}

Param::~Param()
{
    delete ui;
}
