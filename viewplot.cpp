#include "viewplot.h"
#include "ui_viewplot.h"

ViewPlot::ViewPlot(QWidget *parent) :
    QWidget(parent),
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
    parentWidget()->show();
    //p->show();
    hide();
}
