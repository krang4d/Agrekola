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
    void calibrationDataCome(int n, double deta);
    void open();
    void save();

private slots:
    void on_calibr1Button_clicked();

public slots:
    void calibrationData1Come(double);
    void calibrationData2Come(double);
    void calibrationData3Come(double);
    void calibrationData4Come(double);

signals:
    void measurement(StartMeasurment *);
    void calibration(StartMeasurment *);

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
