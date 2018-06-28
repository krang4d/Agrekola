#ifndef SELECTCALIBRATIONAGR1_H
#define SELECTCALIBRATIONAGR1_H

#include <QDialog>
#include "kalibragr2.h"
#include "selectinductor.h"

namespace Ui {
class SelectCalibrationAgr1;
}

class SelectCalibrationAgr1 : public QDialog
{
    Q_OBJECT

public:
    explicit SelectCalibrationAgr1(QWidget *parent = 0);
    ~SelectCalibrationAgr1();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SelectCalibrationAgr1 *ui;
    KalibrAgr2 *kalibragr2;
    SelectInductor *selInductor;
};

#endif // SELECTCALIBRATIONAGR1_H
