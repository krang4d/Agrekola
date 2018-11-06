#include "calibparam.h"
#include "ui_calibparam.h"

CalibParam::CalibParam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalibParam)
{
    ui->setupUi(this);
}

CalibParam::~CalibParam()
{
    delete ui;
}

void CalibParam::setText()
{
    ui->label->setText(calc->getParameters());
}

void CalibParam::setCalc(CalcData *p)
{
    calc = p;
}

void CalibParam::createPlot()
{
    switch (calc->getModeID() ) {
    case Ko1_ID:
        ui->frame->setVisible(false);
        break;
    case Ko2_ID:
        ui->frame->setVisible(false);
        break;
    case Ko3_ID:
        break;
    case Ko4_ID:
        ui->frame->setVisible(false);
        break;
    case Ko5_ID:
        break;
    case Agr1_ID:
        break;
    case Agr2_ID:
        break;

    default:
        break;
    }
    QString demoName = "Quadratic Demo";
    QCustomPlot *customPlot = ui->frame;
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
}


