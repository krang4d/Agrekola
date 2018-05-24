#include "selectinductor.h"
#include "ui_selectinductor.h"

SelectInductor::SelectInductor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectInductor)
{
    ui->setupUi(this);
}

SelectInductor::~SelectInductor()
{
    delete ui;
}
