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
    void calibrationDataCome(int n, double deta);

private slots:
    void on_kolibrButton_clicked();

public slots:
    void calibrationData1Come(double);
    void calibrationData2Come(double);
    void calibrationData3Come(double);
    void calibrationData4Come(double);

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
