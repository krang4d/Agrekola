#ifndef AGR1_H
#define AGR1_H

#include <QWidget>
#include <QStringList>
#include "startmeasurment.h"
#include "savefiles.h"

namespace Ui {
class Agr1;
}

class Agr1 : public QWidget
{
    Q_OBJECT

public:
    explicit Agr1(QWidget *parent = 0);
    ~Agr1();

private:
    void calibration_data_come(int n, double deta);

private slots:
    void on_kolibrButton_clicked();

public slots:
    void calibration_data1_come(double);
    void calibration_data2_come(double);
    void calibration_data3_come(double);
    void calibration_data4_come(double);

signals:
    void measurement(StartMeasurment*);
    void calibration(StartMeasurment*);

private:
    Ui::Agr1 *ui;
    SaveFiles file;
    QStringList param;
};

class StartCalibrationAgr1 : public StartMeasurment
{
    Q_OBJECT
public:
    StartCalibrationAgr1() = delete;
    static StartMeasurment *getStart();
};

#endif // AGR1_H
