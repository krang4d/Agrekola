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
    initPlots();
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

void ViewPlot::initPlots()
{
    customPlot = ui->frame;
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                QCP::iSelectLegend | QCP::iSelectPlottables);
    // prepare legend and some graphs:
    customPlot->legend->setVisible(true);
    customPlot->addGraph()->setName("V1");
    customPlot->addGraph()->setName("V2");
    customPlot->addGraph()->setName("V3");
    customPlot->addGraph()->setName("V4");
    // create and prepare a text layout element:
    //QCPTextElement *legendTitle = new QCPTextElement(customPlot);
    //legendTitle->setLayer(customPlot->legend->layer()); // place text element on same layer as legend, or it ends up below legend
    //legendTitle->setText("Канал(номер пробы)");
    //legendTitle->setFont(QFont("sans", 9, QFont::Bold));
    // then we add it to the QCPLegend (which is a subclass of QCPLayoutGrid):
    if (customPlot->legend->hasElement(0, 0)) // if top cell isn't empty, insert an empty row at top
      customPlot->legend->insertRow(0);
    //customPlot->legend->addElement(0, 0, legendTitle); // place the text element into the empty cell
    customPlot->xAxis->setLabel("сек");
    customPlot->yAxis->setLabel("Вольт");
    customPlot->xAxis->setRange(0, 100);
    customPlot->yAxis->setRange(-6, 6);
    customPlot->axisRect()->setupFullAxesBox();
}

void ViewPlot::rePlot()
{

    //customPlot->graph(0)->setSelectable(QCP::stSingleData);
    customPlot->xAxis->setRange(0, t.back());
    customPlot->yAxis->setRange(-6, 6);
    //customPlot->rescaleAxes();

    customPlot->graph(0)->setPen(QPen(QColor(10, 110, 40)));
    //customPlot->graph(0)->setLineStyle(QCPGraph::LineStyle::lsStepCenter);
    QCPScatterStyle myScatter;
    myScatter.setShape(QCPScatterStyle::ssCircle);
    myScatter.setPen(QPen(Qt::blue));
    myScatter.setBrush(Qt::white);
    myScatter.setSize(5);
    customPlot->graph(0)->setScatterStyle(myScatter);
    customPlot->graph(0)->setData(t.toVector(), v1.toVector(), true);

    customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));
    customPlot->graph(1)->setData(t.toVector(), v2.toVector(), true);

    customPlot->graph(2)->setPen(QPen(QColor(255, 110, 200)));
    customPlot->graph(2)->setData(t.toVector(), v3.toVector(), true);

    customPlot->graph(3)->setPen(QPen(QColor(255, 200, 40)));
    customPlot->graph(3)->setData(t.toVector(), v4.toVector(), true);

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

        tb->setItem(i, 0, iv1);
        tb->setItem(i, 1, iv2);
        tb->setItem(i, 2, iv3);
        tb->setItem(i, 3, iv4);
        tb->setItem(i, 4, it);
    }
    rePlot();
    ui->groupBox->setEnabled(true);
    ui->checkBox_1->setChecked(true);
    ui->checkBox_2->setChecked(true);
    ui->checkBox_3->setChecked(true);
    ui->checkBox_4->setChecked(true);
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
