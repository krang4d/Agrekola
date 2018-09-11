#ifndef KO5_H
#define KO5_H

#include <QWidget>
#include "savefiles.h"
#include "startmeasurment.h"

namespace Ui {
class Ko5;
}

class Ko5 : public QWidget
{
    Q_OBJECT

public:
    explicit Ko5(QWidget *parent = 0);
    ~Ko5();

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
    Ui::Ko5 *ui;
    SaveFiles file;
    QStringList param;
};

class StartCalibrationKo5 : public StartMeasurment
{
    Q_OBJECT
public:
    StartCalibrationKo5() = delete;
    static StartMeasurment* getStart();
};

#endif // KO5_H
