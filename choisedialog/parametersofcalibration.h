#ifndef PARAMETERSOFCALIBRATION_H
#define PARAMETERSOFCALIBRATION_H

#include <QWidget>
#include <QString>

namespace Ui {
class ParametersOfCalibration;
}

class ParametersOfCalibration : public QWidget
{
    Q_OBJECT

public:
    explicit ParametersOfCalibration(QWidget *parent = 0);
    ~ParametersOfCalibration();

    void setText(QString);

private:
    Ui::ParametersOfCalibration *ui;
};

#endif // PARAMETERSOFCALIBRATION_H
