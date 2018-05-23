#include "ko2.h"
#include "ui_ko2.h"

Ko2::Ko2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ko2)
{
    ui->setupUi(this);
}

Ko2::~Ko2()
{
    delete ui;
}
