#ifndef CALIBPARAM_H
#define CALIBPARAM_H

#include <QDialog>
#include <QString>
#include <calculatedata.h>

namespace Ui {
class CalibParam;
}

class CalibParam : public QDialog
{
    Q_OBJECT

public:
    explicit CalibParam(CalcData *p, QWidget *parent = 0);
    ~CalibParam();

protected:
    void setCalc(CalcData *);
    void createPlot();
    void setText();

private:
    Ui::CalibParam *ui;
    CalcData *calc;
    QCustomPlot *customPlot;
    Mode_ID mode;
};

#endif // CALIBPARAM_H
