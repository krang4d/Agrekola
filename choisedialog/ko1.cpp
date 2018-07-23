#include "ko1.h"
#include "ui_ko1.h"

Ko1::Ko1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ko1)
{
    ui->setupUi(this);
    file.openKo1(param);
    if(!param.isEmpty() && param.count() == 2) {
        ui->lineEdit_1->setText(param.at(0));
        ui->lineEdit_2->setText(param.at(1));
    }
}

Ko1::~Ko1()
{
    param.clear();
    param << ui->lineEdit_1->text() << ui->lineEdit_2->text();
    file.saveKo1(param);
    delete ui;
}

void Ko1::on_startButton_clicked()
{
    emit measurement();
}
