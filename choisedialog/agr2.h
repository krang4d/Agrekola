#ifndef AGR2_H
#define AGR2_H

#include <QWidget>
#include "kalibragr2.h"
#include "selectcalibrationagr1.h"
#include "selectinductor.h"

namespace Ui {
class Agr2;
}

class Agr2 : public QWidget
{
    Q_OBJECT

public:
    explicit Agr2(QWidget *parent = 0);
    ~Agr2();

private slots:
    void on_startButton_clicked();
    void on_calibrButton_clicked();

signals:
    void measurement();
    void calibration();

private:
    Ui::Agr2 *ui;
    KalibrAgr2 *kalibragr2;
    SelectCalibrationAgr1 *selcalibrAgr1;
    SelectInductor *selInductor;
};

#endif // AGR2_H