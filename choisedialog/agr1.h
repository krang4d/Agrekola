#ifndef AGR1_H
#define AGR1_H

#include <QWidget>
#include <QStringList>
#include "startmeasurement.h"

struct Error_Agr1_Type_ID
{
    QString err_msg;
    Error_Agr1_Type_ID(const QString &m) : err_msg(m) {}
};

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
    void open();
    void save();

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



public slots:
    inline void btpData1Come(double d) {
        c_agr1.setBTP1(d);
    }
    inline void btpData2Come(double d) {
        c_agr1.setBTP2(d);
    }
    inline void btpData3Come(double d) {
        c_agr1.setBTP3(d);
    }
    inline void btpData4Come(double d) {
        c_agr1.setBTP4(d);
    }
    inline void otpData1Come(double d) {
        c_agr1.setOTP1(d);
    }
    inline void otpData2Come(double d) {
        c_agr1.setOTP2(d);
    }
    inline void otpData3Come(double d) {
        c_agr1.setOTP3(d);
    }
    inline void otpData4Come(double d) {
        c_agr1.setOTP4(d);
    }

signals:
    void measurement(StartMeasurement*);
    void calibration(StartMeasurement*);

private:
    Ui::Agr1 *ui;
    TestAgr1 t_agr1;
    CalibrationAgr1 c_agr1;
};

class StartCalibrationAgr1 : public StartMeasurement
{
    Q_OBJECT
public:
    StartCalibrationAgr1() = delete;
    static StartMeasurement *getStart(Calibration*);
    static StartMeasurement *getBTP();
    static StartMeasurement *getOTP();
};

class StartTestAgr1 : public StartMeasurement
{
    Q_OBJECT
public:
    StartTestAgr1() = delete;
    static StartMeasurement* getStart(Test* t_agr1);
};

#endif // AGR1_H
