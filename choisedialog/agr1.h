#ifndef AGR1_H
#define AGR1_H

#include <QWidget>
#include <QStringList>
#include "startmeasurement.h"
#include "agr_impl.h"

struct Error_Agr1_Type_ID
{
    QString err_msg;
    Error_Agr1_Type_ID(const QString &m) : err_msg(m) {}
};

namespace Ui {
class Agr1;
}

class Agr1 : public QWidget, public Agr_impl
{
    Q_OBJECT

public:
    explicit Agr1(QWidget *parent = 0);
    void setTab(int);
    ~Agr1();

private slots:
    void on_pushButton_test_clicked();
    //void on_pushButton_calib_clicked();

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
    void setT1(double, int) override;
    void setT2(double, int) override;
    void setT3(double, int) override;
    void setT4(double, int) override;
    void setT1_2(double, int) override;
    void setT3_4(double, int) override;

    QString c_print() override;
    void calibrationData1Come(double, int) override;
    void calibrationData2Come(double, int) override;
    void calibrationData3Come(double, int) override;
    void calibrationData4Come(double, int) override;
    void calibrationData1_2Come(double, int) override;
    void calibrationData2_4Come(double, int) override;

    void btp1Come(double, SaveTo) override;
    void btp2Come(double, SaveTo) override;
    void btp3Come(double, SaveTo) override;
    void btp4Come(double, SaveTo) override;

    void otp1Come(double, SaveTo) override;
    void otp2Come(double, SaveTo) override;
    void otp3Come(double, SaveTo) override;
    void otp4Come(double, SaveTo) override;

signals:
    void measurement(StartMeasurement*);
    void calibration(StartMeasurement*);

private:
    Ui::Agr1 *ui;
    TestAgr1 *t_agr1;
    CalibrationAgr1 *c_agr1;
    Ko_impl::Mode_ID mode;
};

class StartCalibrationAgr1 : public StartMeasurement
{
    Q_OBJECT
public:
    StartCalibrationAgr1() = delete;
    static StartMeasurement *getStart(Test *t_agr1, Calibration *c_agr1);
//    static StartMeasurement *getBTP();
//    static StartMeasurement *getOTP();
};

class StartTestAgr1 : public StartMeasurement
{
    Q_OBJECT
public:
    StartTestAgr1() = delete;
    static StartMeasurement* getStart(Test *t_agr1, Calibration *c_agr1);
};

#endif // AGR1_H
