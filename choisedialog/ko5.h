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
    void calibrationDataCome(int n, double deta);
    void open();
    void save();

private slots:
    void on_pushButton_calib_clicked();
    void on_pushButton_test_clicked();

    void on_radioButton_testSingle_toggled(bool checked);

    void on_checkBox_testCh1_toggled(bool checked);
    void on_checkBox_testCh2_toggled(bool checked);
    void on_checkBox_testCh3_toggled(bool checked);
    void on_checkBox_testCh4_toggled(bool checked);
    void on_lineEdit_testCh1_textChanged(const QString &arg1);
    void on_lineEdit_testCh3_textChanged(const QString &arg1);

public slots:
    void calibrationData1Come(double);
    void calibrationData2Come(double);
    void calibrationData3Come(double);
    void calibrationData4Come(double);

signals:
    void measurement(StartMeasurment*);
    void calibration(StartMeasurment*);

private:
    Ui::Ko5 *ui;
    TestKo5 t_ko5;
    CalibrationKo5 c_ko5;
};

class StartTestKo5 : public StartMeasurment
{
    Q_OBJECT
public:
    StartTestKo5() = delete;
    static StartMeasurment* getStart(Test* t_ko5);
};

class StartCalibrationKo5 : public StartMeasurment
{
    Q_OBJECT

public:
    StartCalibrationKo5() = delete;
    static StartMeasurment* getStart(Calibration* c_ko5);
};

#endif // KO5_H
