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
    explicit CalibParam(QWidget *parent = 0);
    ~CalibParam();

    void setText();
    void setPlot(void);
    void setCalc(CalcData *);
    void createPlot();

private:
    Ui::CalibParam *ui;
    CalcData *calc;
};

#endif // CALIBPARAM_H
