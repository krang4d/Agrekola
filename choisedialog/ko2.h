#ifndef KO2_H
#define KO2_H

#include <QWidget>
#include "globalvalue.h"

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
    void calibrationDataCome(int n, double deta);
    void open();
    void save();

private slots:
    void on_calibr1Button_clicked();
    void on_toolBox_currentChanged(int index);

    void on_pushButton_clicked();

public slots:
    void calibrationData1Come(double);
    void calibrationData2Come(double);
    void calibrationData3Come(double);
    void calibrationData4Come(double);

signals:
    void measurement(StartMeasurment*);
    void calibration(StartMeasurment*);

private:
    Ui::Ko2 *ui;
    SaveFiles file;
    QStringList param;
};

class StartTestKo2 : public StartMeasurment
{
    Q_OBJECT
public:
    StartTestKo2() = delete;
    static StartMeasurment* getStart();
};


class StartCalibrationKo2 : public StartMeasurment
{
    Q_OBJECT
public:
    StartCalibrationKo2() = delete;
    static StartMeasurment* getStart();
};

#endif // KO2_H
