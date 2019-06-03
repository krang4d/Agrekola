#ifndef KO3_H
#define KO3_H

#include <QWidget>
#include "savefiles.h"
#include "startmeasurement.h"
#include "ko_impl.h"

namespace Ui {
class Ko3;
}

class Ko3 : public QWidget, public Ko_impl
{
    Q_OBJECT

public:
    explicit Ko3(QWidget *parent = 0);
    void setTab(int);
    ~Ko3();

//    void calibrationDataCome(int n, double data);

private slots:
    void on_pushButton_test_clicked();
    void on_pushButton_calib_clicked();

    void on_radioButton_testSingle_toggled(bool checked);

    void on_checkBox_testCh1_toggled(bool checked);
    void on_checkBox_testCh2_toggled(bool checked);
    void on_checkBox_testCh3_toggled(bool checked);
    void on_checkBox_testCh4_toggled(bool checked);

    void on_lineEdit_testCh1_textChanged(const QString &arg1);
    void on_lineEdit_testCh3_textChanged(const QString &arg1);

    // Ko_impl interface
    void on_tabWidget_currentChanged(int index);

public slots:
    void open();
    void close();

    void setDate(QDate, SaveTo) override;
    void setTime(QTime, SaveTo) override;

    QString t_print() override;
    void setT1(double, int) override;
    void setT2(double, int) override;
    void setT3(double, int) override;
    void setT4(double, int) override;
    void setT1_2(double, int) override;
    void setT3_4(double, int) override;

    QString c_print() override;
    void calibrationData1Come(double, int) override {}
    void calibrationData2Come(double, int) override {}
    void calibrationData3Come(double, int) override {}
    void calibrationData4Come(double, int) override {}
    void calibrationData1_2Come(double, int) override;
    void calibrationData2_4Come(double, int) override;

signals:
    void measurement(StartMeasurement*);
    void calibration(StartMeasurement*);
    void calibration_done();

private:
    Ui::Ko3 *ui;
    TestKo3 *t_ko3;
    CalibrationKo3 *c_ko3;
    Mode_ID mode;
};

class StartTestKo3 : public StartMeasurement
{
    Q_OBJECT
public:
    StartTestKo3() = delete;
    static StartMeasurement* getStart(TestKo3 *t_ko3, CalibrationKo3 *c_ko3);
};

class StartCalibrationKo3 : public StartMeasurement
{
    Q_OBJECT
public:
    StartCalibrationKo3() = delete;
    static StartMeasurement* getStart(TestKo3 *t_ko3, CalibrationKo3 *c_ko3);
};

#endif // KO3_H
