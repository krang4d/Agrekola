#include "viewplot.h"
#include "ui_viewplot.h"

ViewPlot::ViewPlot(QWidget *parent) :
    p(parent),
    ui(new Ui::ViewPlot)
{
    ui->setupUi(this);
}

ViewPlot::~ViewPlot()
{
    delete ui;
}

void ViewPlot::on_pushButton_back_clicked()
{
    p->show();
    this->hide();
}
