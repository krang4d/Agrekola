#include "agr2.h"
#include "ui_agr2.h"

Agr2::Agr2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Agr2)
{
    ui->setupUi(this);
}

Agr2::~Agr2()
{
    delete ui;
}

void Agr2::on_pushButton_clicked()
{
    emit measurement();
}
