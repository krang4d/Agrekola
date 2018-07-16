#include "viewplot.h"
#include "ui_viewplot.h"

ViewPlot::ViewPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewPlot)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    initTable();
    ui->groupBox->setEnabled(false);
    ui->pushButton_view->setEnabled(false);
}

ViewPlot::~ViewPlot()
{
    delete ui;
}

void ViewPlot::initTable()
{
    const QStringList headList = {"V1", "V2", "V3", "V4", "t"};
    tb = ui->tableWidget;
    tb->setColumnCount(5);
    tb->setHorizontalHeaderLabels(headList);
}

void ViewPlot::initPlot()
{
    customPlot = ui->frame;
    customPlot->addGraph();
    customPlot->addGraph();
    customPlot->addGraph();
    customPlot->addGraph();
    customPlot->graph(0)->addData(t.toVector(), v1.toVector());
    customPlot->graph(1)->addData(t.toVector(), v2.toVector());
    customPlot->graph(2)->addData(t.toVector(), v3.toVector());
    customPlot->graph(3)->addData(t.toVector(), v4.toVector());
    customPlot->xAxis->setLabel("сек");
    customPlot->yAxis->setLabel("Вольт");
    customPlot->xAxis->setRange(0, t.back());
    customPlot->yAxis->setRange(-6, 6);
    customPlot->replot();
}

void ViewPlot::addData()
{
    qDebug() << "count" << t.count();
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
    }
    initPlot();
    ui->groupBox->setEnabled(true);
    ui->checkBox_1->setChecked(true);
    ui->checkBox_2->setChecked(true);
    ui->checkBox_3->setChecked(true);
    ui->checkBox_4->setChecked(true);
    ui->pushButton_view->setEnabled(true);
}

void ViewPlot::on_pushButton_back_clicked()
{
    close();
}

void ViewPlot::on_pushButton_open_clicked()
{
    v1.clear();
    v2.clear();
    v3.clear();
    v4.clear();
    t.clear();
    tb->clearContents();
    SaveFiles::openData(this, v1,v2,v3,v4,t);
    addData();
}

void ViewPlot::on_pushButton_view_clicked()
{
    initPlot();
}

void ViewPlot::on_checkBox_1_stateChanged(int arg1)
{
    customPlot->graph(0)->setVisible(arg1);
    customPlot->replot();
}

void ViewPlot::on_checkBox_2_stateChanged(int arg1)
{
    customPlot->graph(1)->setVisible(arg1);
    customPlot->replot();
}

void ViewPlot::on_checkBox_3_stateChanged(int arg1)
{
    customPlot->graph(2)->setVisible(arg1);
    customPlot->replot();
}

void ViewPlot::on_checkBox_4_stateChanged(int arg1)
{
    customPlot->graph(3)->setVisible(arg1);
    customPlot->replot();
}
