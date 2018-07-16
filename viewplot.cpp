#include "viewplot.h"
#include "ui_viewplot.h"
#include <QDebug>

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
    //QStringList headList = {"V1", "V2", "V3", "V4", "t"};
    tb = ui->tableWidget;
    tb->setRowCount(2);
    tb->setColumnCount(5);
    //tb->setHorizontalHeaderLabels(headList);
}

void ViewPlot::addData()
{
    tb->setRowCount(t.count());
    for(int i = 0; i<t.count(); i++)
    {
        QTableWidgetItem *it = new QTableWidgetItem(tr("%1").arg(t.at(i)));
        QTableWidgetItem *iv1 = new QTableWidgetItem(tr("%1").arg(v1.at(i)));
        QTableWidgetItem *iv2 = new QTableWidgetItem(tr("%1").arg(v2.at(i)));
        QTableWidgetItem *iv3 = new QTableWidgetItem(tr("%1").arg(v3.at(i)));
        QTableWidgetItem *iv4 = new QTableWidgetItem(tr("%1").arg(v4.at(i)));
        qDebug() << "t =" << t[i];
        tb->setItem(i, 0, it);
        tb->setItem(i, 1, iv1);
        tb->setItem(i, 2, iv2);
        tb->setItem(i, 3, iv3);
        tb->setItem(i, 4, iv4);
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
    v1.clear();
    v2.clear();
    v3.clear();
    v4.clear();
    SaveFiles::openData(v1,v2,v3,v4,t);
}

void ViewPlot::on_pushButton_print_clicked()
{

}

void ViewPlot::on_pushButton_view_clicked()
{
    addData();
}
