#include "viewplot.h"
#include "ui_viewplot.h"

ViewPlot::ViewPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewPlot)
{
    ui->setupUi(this);
    initTable();
}

ViewPlot::~ViewPlot()
{
    delete ui;
}

void ViewPlot::initTable()
{
    QStringList headList;
    headList << "V1" << "V2" << "V3" << "V4" << "t";
    tb = ui->tableWidget;
    tb->setRowCount(10);
    tb->setColumnCount(5);
    tb->setHorizontalHeaderLabels(headList);
}

void ViewPlot::addData()
{

    for(int i = 0; i<10; i++)
    {
        QTableWidgetItem *it = new QTableWidgetItem(tr("%1").arg(i+1));
        tb->setItem(i,1,it);
        //QTableWidgetItem *it = ui->tableWidget->item(i, i);
        //it->setText(QString("1"));
//        for(int j = 1; j<4; j++)
//        {
//            QTableWidgetItem *it = ui->tableWidget->item(i,j);
//            it->setText(QString("%1").arg(i+j));
//            delete it;
//        }
    }
}

void ViewPlot::on_pushButton_back_clicked()
{

}

void ViewPlot::on_pushButton_print_clicked()
{

}

void ViewPlot::on_pushButton_view_clicked()
{

}
