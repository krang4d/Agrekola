#ifndef SELECTCALIBRATIONAGR1_H
#define SELECTCALIBRATIONAGR1_H

#include <QDialog>

namespace Ui {
class SelectCalibrationAgr1;
}

class SelectCalibrationAgr1 : public QDialog
{
    Q_OBJECT

public:
    explicit SelectCalibrationAgr1(QWidget *parent = 0);
    ~SelectCalibrationAgr1();

private:
    Ui::SelectCalibrationAgr1 *ui;
};

#endif // SELECTCALIBRATIONAGR1_H
