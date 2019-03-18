#include "calibparam.h"
#include "ui_calibparam.h"

CalibParam::CalibParam(CalcData *p, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalibParam)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    customPlot = ui->frame;
    setCalc(p);
    setText();
    createPlot();
}

CalibParam::~CalibParam()
{
    delete calc;
    delete ui;
}

void CalibParam::setText()
{
    ui->label->setText(calc->getParameters());
}

void CalibParam::setCalc(CalcData *p)
{
    calc = p;
    mode = calc->getModeID();
    switch ( mode ) {
    case CalibAgr1_ID:
        break;
    case CalibAgr2_ID:
        break;
    case CalibKo1_ID:
        break;
    case CalibKo2_ID:
        break;
    case CalibKo3_ID:
        break;
    case CalibKo4_ID:
        break;
    case CalibKo5_ID:
        break;
    case TestKo1_ID:
        customPlot->setVisible(false);
        break;
    case TestKo2_ID:
        customPlot->setVisible(false);
        break;
    case TestKo3_ID:
        break;
    case TestKo4_ID:
        customPlot->setVisible(false);
        break;
    case TestKo5_ID:
        break;
    case TestAgr1_ID:
        break;
    case TestAgr2_ID:
        break;
    default:
        break;
    }
}

void CalibParam::createPlot()
{
    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i];  // let's plot a quadratic function
    }
    // create graph and assign data to it:
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(-1, 1);
    customPlot->yAxis->setRange(0, 1);
    customPlot->replot();
}
