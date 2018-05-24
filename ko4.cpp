#include "ko4.h"
#include "ui_ko4.h"

Ko4::Ko4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ko4)
{
    ui->setupUi(this);
}

Ko4::~Ko4()
{
    delete ui;
}

void Ko4::on_pushButton_clicked()
{
    emit measurement();
}
