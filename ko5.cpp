#include "ko5.h"
#include "ui_ko5.h"

Ko5::Ko5(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ko5)
{
    ui->setupUi(this);
}

Ko5::~Ko5()
{
    delete ui;
}

void Ko5::on_pushButton_clicked()
{
    emit measurement();
}
