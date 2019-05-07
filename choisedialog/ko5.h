#ifndef KO5_H
#define KO5_H

#include <QWidget>
#include "savefiles.h"
#include "startmeasurement.h"
#include "ko_impl.h"

namespace Ui {
class Ko5;
}

class Ko5 : public QWidget, public Ko_impl
{
    Q_OBJECT

public:
    explicit Ko5(QWidget *parent = 0);
    void setTab(int);
    ~Ko5();

private:
    void calibrationDataCome(int n, double deta);

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

    // Ko_impl interface
public slots:
    void open();
    void close();

    void setDate(QDate, SaveTo) override;
    void setTime(QTime, SaveTo) override;

    QString t_print() override;
    void setT1(double value, int i) override;
    void setT2(double value, int i) override;
    void setT3(double value, int i) override;
    void setT4(double value, int i) override;
    void setT1_2(double, int) override;
    void setT3_4(double, int) override;

    QString c_print() override;
    void calibrationData1Come(double, int i) override;
    void calibrationData2Come(double, int i) override;
    void calibrationData3Come(double, int i) override;
    void calibrationData4Come(double, int i) override;
    void calibrationData1_2Come(double, int) override;
    void calibrationData2_4Come(double, int) override;

signals:
    void measurement(StartMeasurement*);
    void calibration(StartMeasurement*);

private:
    Ui::Ko5 *ui;
    TestKo5 *t_ko5;
    CalibrationKo5 *c_ko5;
    Ko_impl::Mode_ID mode;
};

class StartTestKo5 : public StartMeasurement
{
    Q_OBJECT
public:
    StartTestKo5() = delete;
    static StartMeasurement* getStart(TestKo5 *t_ko5, Calibration *c_ko5);
};

class StartCalibrationKo5 : public StartMeasurement
{
    Q_OBJECT

public:
    StartCalibrationKo5() = delete;
    static StartMeasurement* getStart(TestKo5 *t_ko5, Calibration *c_ko5);
};

#endif // KO5_H
