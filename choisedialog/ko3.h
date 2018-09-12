#ifndef KO3_H
#define KO3_H

#include <QWidget>
#include "savefiles.h"
#include "startmeasurment.h"

namespace Ui {
class Ko3;
}

class Ko3 : public QWidget
{
    Q_OBJECT

public:
    explicit Ko3(QWidget *parent = 0);
    ~Ko3();

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
    Ui::Ko3 *ui;
    SaveFiles file;
    QStringList param;
};

class StartCalibrationKo3 : public StartMeasurment
{
    Q_OBJECT
public:
    StartCalibrationKo3() = delete;
    static StartMeasurment* getStart();
};

#endif // KO3_H
