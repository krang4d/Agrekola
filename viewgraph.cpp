#include "viewgraph.h"
#include "ui_viewgraph.h"

ViewGraph::ViewGraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewGraph)
{
    ui->setupUi(this);
}

ViewGraph::~ViewGraph()
{
    delete ui;
}

void ViewGraph::on_pushButton_back_clicked()
{
    hide();
    parentWidget()->show();
    //p->show();
}
