#ifndef AGR2_H
#define AGR2_H

#include <QWidget>
#include "kalibragr2.h"
#include "selectcalibrationagr1.h"
#include "selectinductor.h"
#include "savefiles.h"
#include "startmeasurment.h"

namespace Ui {
class Agr2;
}

class Agr2 : public QWidget
{
    Q_OBJECT

public:
    explicit Agr2(QWidget *parent = 0);
    ~Agr2();

private:
    void calibrationDataCome(int n, double deta);
    void open();
    void save();

private slots:
    void on_calibrButton_clicked();

public slots:
    void calibrationData1Come(double);
    void calibrationData2Come(double);
    void calibrationData3Come(double);
    void calibrationData4Come(double);

signals:
    void measurement(StartMeasurment *);
    void calibration(StartMeasurment *);

private:
    Ui::Agr2 *ui;
    SaveFiles file;
    QStringList param;
};

class StartTestAgr2 : public StartMeasurment
{
    Q_OBJECT
public:
    StartTestAgr2() = delete;
    static StartMeasurment* getStart();
};

class StartCalibrationAgr2 : public StartMeasurment
{
    Q_OBJECT
public:
    StartCalibrationAgr2() = delete;
    static StartMeasurment *getStart();
};

#endif // AGR2_H
