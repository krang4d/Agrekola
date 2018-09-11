#ifndef KO2_H
#define KO2_H

#include <QWidget>
#include "savefiles.h"
#include "startmeasurment.h"

namespace Ui {
class Ko2;
}

class Ko2 : public QWidget
{
    Q_OBJECT

public:
    explicit Ko2(QWidget *parent = 0);
    ~Ko2();

private:
    void calibration_data_come(int n, double deta);

private slots:
    void on_calibr1Button_clicked();

public slots:
    void calibration_data1_come(double);
    void calibration_data2_come(double);
    void calibration_data3_come(double);
    void calibration_data4_come(double);

signals:
    void measurement(StartMeasurment*);
    void calibration(StartMeasurment*);

private:
    Ui::Ko2 *ui;
    SaveFiles file;
    QStringList param;
};

class StartCalibrationKo2 : public StartMeasurment
{
    Q_OBJECT
public:
    StartCalibrationKo2() = delete;
    static StartMeasurment* getStart();
};

#endif // KO2_H
