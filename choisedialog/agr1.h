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

private:
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
    QString t_print() override;
    void setT1(double) override;
    void setT2(double) override;
    void setT3(double) override;
    void setT4(double) override;

    QString c_print() override;
    void calibrationData1Come(double) override;
    void calibrationData2Come(double) override;
    void calibrationData3Come(double) override;
    void calibrationData4Come(double) override;

    void btp1Come(double) override;
    void btp2Come(double) override;
    void btp3Come(double) override;
    void btp4Come(double) override;

    void otp1Come(double) override;
    void otp2Come(double) override;
    void otp3Come(double) override;
    void otp4Come(double) override;

signals:
    void measurement(StartMeasurement*);
    void calibration(StartMeasurement*);

private:
    Ui::Agr1 *ui;
    TestAgr1 *t_agr1;
    CalibrationAgr1 *c_agr1;
};

class StartCalibrationAgr1 : public StartMeasurement
{
    Q_OBJECT
public:
    StartCalibrationAgr1() = delete;
    static StartMeasurement *getStart(Calibration*);
//    static StartMeasurement *getBTP();
//    static StartMeasurement *getOTP();
};

class StartTestAgr1 : public StartMeasurement
{
    Q_OBJECT
public:
    StartTestAgr1() = delete;
    static StartMeasurement* getStart(Test* t_agr1);
};

#endif // AGR1_H
