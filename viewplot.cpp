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
