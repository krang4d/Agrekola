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
    ui->label_filename->setText(tr("Нет открытых файлов"));
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
    customPlot->graph(0)->setPen(QPen(QColor(10, 110, 40)));
    customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));
    customPlot->graph(2)->setPen(QPen(QColor(255, 110, 200)));
    customPlot->graph(3)->setPen(QPen(QColor(200, 150, 0)));

    // connect slot that ties some axis selections together (especially opposite axes):
    connect(customPlot, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    // connect slot that shows a message in the status bar when a graph is clicked:
    connect(customPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*,int)));

}

void ViewPlot::rePlot()
{
    const QStringList headList = {param.at(0), param.at(1), param.at(2), param.at(3), param.at(4)};
    tb->setHorizontalHeaderLabels(headList);
    //customPlot->graph(0)->setSelectable(QCP::stSingleData);
    customPlot->xAxis->setRange(0, t.back());
    //customPlot->rescaleAxes();


    customPlot->graph(0)->setName(param.at(0));
    //customPlot->graph(0)->setLineStyle(QCPGraph::LineStyle::lsStepCenter);
//    QCPScatterStyle myScatter;
//    myScatter.setShape(QCPScatterStyle::ssCircle);
//    myScatter.setPen(QPen(Qt::blue));
//    myScatter.setBrush(Qt::white);
//    myScatter.setSize(5);
//    customPlot->graph(0)->setScatterStyle(myScatter);
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::blue, Qt::white, 3));
    customPlot->graph(0)->setData(t.toVector(), v1.toVector(), true);

    customPlot->graph(1)->setName(param.at(1));
    customPlot->graph(1)->setData(t.toVector(), v2.toVector(), true);

    customPlot->graph(2)->setName(param.at(2));
    customPlot->graph(2)->setData(t.toVector(), v3.toVector(), true);

    customPlot->graph(3)->setName(param.at(3));
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
    ui->label_filename->setText(SaveFiles::openData(this, v1,v2,v3,v4,t,param));
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

void ViewPlot::on_pushButton_print_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранение графиков...", qApp->applicationDirPath(), "*.pdf");
    if (!fileName.isEmpty())
    {
        customPlot->savePdf(fileName);
    }
}

void ViewPlot::selectionChanged()
{
    /*
     normally, axis base line, axis tick labels and axis labels are selectable separately, but we want
     the user only to be able to select the axis as a whole, so we tie the selected states of the tick labels
     and the axis base line together. However, the axis label shall be selectable individually.

     The selection state of the left and right axes shall be synchronized as well as the state of the
     bottom and top axes.

     Further, we want to synchronize the selection of the graphs with the selection state of the respective
     legend item belonging to that graph. So the user can select a graph by either clicking on the graph itself
     or on its legend item.
    */

    // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || customPlot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
        customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
      customPlot->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
      customPlot->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }
    // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || customPlot->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
        customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
      customPlot->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
      customPlot->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }

    // synchronize selection of graphs with selection of corresponding legend items:
    for (int i=0; i<customPlot->graphCount(); ++i)
    {
      QCPGraph *graph = customPlot->graph(i);
      QCPPlottableLegendItem *item = customPlot->legend->itemWithPlottable(graph);
      if (item->selected() || graph->selected())
      {
        item->setSelected(true);
        graph->setSelection(QCPDataSelection(graph->data()->dataRange()));
      }
    }
}

void ViewPlot::mousePress()
{
    // if an axis is selected, only allow the direction of that axis to be dragged
    // if no axis is selected, both directions may be dragged
    if (customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
      customPlot->axisRect()->setRangeDrag(customPlot->xAxis->orientation());
    else if (customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
      customPlot->axisRect()->setRangeDrag(customPlot->yAxis->orientation());
    else
      customPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void ViewPlot::mouseWheel()
{
    // if an axis is selected, only allow the direction of that axis to be zoomed
    // if no axis is selected, both directions may be zoomed

    if (customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
      customPlot->axisRect()->setRangeZoom(customPlot->xAxis->orientation());
    else if (customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
      customPlot->axisRect()->setRangeZoom(customPlot->yAxis->orientation());
    else
        customPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void ViewPlot::graphClicked(QCPAbstractPlottable *plottable, int dataIndex)
{
    // since we know we only have QCPGraphs in the plot, we can immediately access interface1D()
    // usually it's better to first check whether interface1D() returns non-zero, and only then use it.
    double dataValue = plottable->interface1D()->dataMainValue(dataIndex);
    QString message = QString("Clicked on graph '%1' at data point #%2 with value %3.").arg(plottable->name()).arg(dataIndex).arg(dataValue);
    qDebug().quote() << message;
    //ui->statusBar->showMessage(message, 2500);

}
