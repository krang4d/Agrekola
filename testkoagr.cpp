#include "testkoagr.h"
#include "ui_testkoagr.h"

TestKoAgr::TestKoAgr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestKoAgr)
{
    ui->setupUi(this);
}

TestKoAgr::~TestKoAgr()
{
    delete ui;
}


void TestKoAgr::on_pushButton_back_clicked()
{
    accept();
}

void TestKoAgr::on_pushButton_onlaser_clicked()
{

}

void TestKoAgr::on_pushButton_offlaser_clicked()
{

}

void TestKoAgr::on_pushButton_onmotor_clicked()
{

}

void TestKoAgr::on_pushButton_offmotor_clicked()
{

}

void TestKoAgr::on_pushButton_poll_clicked()
{

}
