#ifndef KO2_H
#define KO2_H

#include <QWidget>
#include "globalvalue.h"
#include "startmeasurement.h"
#include "ko_impl.h"

namespace Ui {
class Ko2;
}

class Ko2 : public QWidget, public Ko_impl
{
    Q_OBJECT

public:
    explicit Ko2(QWidget *parent = 0);
    ~Ko2();

private:
    void calibrationDataCome(int n, double data);
    void open();
    void close();

private slots:
    void on_pushButton_test1_clicked();
    void on_pushButton_test2_clicked();
    void on_pushButton_calib_clicked();

    void on_toolBox_currentChanged(int index);

    void on_radioButton_test1Single_toggled(bool checked);
    void on_radioButton_test2Single_toggled(bool checked);

    void on_checkBox_test1Ch1_toggled(bool checked);
    void on_checkBox_test1Ch2_toggled(bool checked);
    void on_checkBox_test1Ch3_toggled(bool checked);
    void on_checkBox_test1Ch4_toggled(bool checked);
    void on_checkBox_test2Ch1_toggled(bool checked);
    void on_checkBox_test2Ch2_toggled(bool checked);
    void on_checkBox_test2Ch3_toggled(bool checked);
    void on_checkBox_test2Ch4_toggled(bool checked);

    void on_lineEdit_test1Ch1_textChanged(const QString &arg1);
    void on_lineEdit_test1Ch3_textChanged(const QString &arg1);
    void on_lineEdit_test2Ch1_textChanged(const QString &arg1);
    void on_lineEdit_test2Ch3_textChanged(const QString &arg1);

public slots:
    void calibrationData1Come(double);
    void calibrationData2Come(double);
    void calibrationData3Come(double);
    void calibrationData4Come(double);

signals:
    void measurement(StartMeasurement*);
    void calibration(StartMeasurement*); 
    void calibration_done();

private:
    Ui::Ko2 *ui;
    TestKo2 *t_ko2;
    TestKo2 *t_ko2_1;
    CalibrationKo2 *c_ko2;

    friend class StartTestKo2;
    friend class StartCalibrationKo2;
};

class StartTestKo2 : public StartMeasurement
{
    Q_OBJECT
public:
    StartTestKo2() = delete;
    static StartMeasurement* getStart(Ko2 *widget);
};

class StartCalibrationKo2 : public StartMeasurement
{
    Q_OBJECT
public:
    StartCalibrationKo2() = delete;
    static StartMeasurement* getStart(Ko2 *widget);
};

#endif // KO2_H
