#ifndef AGR2_H
#define AGR2_H

#include <QWidget>
#include "kalibragr2.h"
#include "selectcalibrationagr1.h"
#include "selectinductor.h"
#include "savefiles.h"
#include "startmeasurement.h"
#include "agr_impl.h"

struct Error_Agr2_Type_ID
{
    QString err_msg;
    Error_Agr2_Type_ID(const QString &m) : err_msg(m) {}
};

namespace Ui {
class Agr2;
}

class Agr2 : public QWidget, public Agr_impl
{
    Q_OBJECT

public:
    explicit Agr2(QWidget *parent = 0);
    void setTab(int);
    ~Agr2();

private slots:
    void on_pushButton_calib_clicked();
    void on_pushButton_test_clicked();

    void on_checkBox_testCh1_toggled(bool checked);
    void on_checkBox_testCh2_toggled(bool checked);
    void on_checkBox_testCh3_toggled(bool checked);
    void on_checkBox_testCh4_toggled(bool checked);

    void on_lineEdit_testCh1_textChanged(const QString &arg1);
    void on_lineEdit_testCh3_textChanged(const QString &arg1);

    void on_radioButton_testSingle_toggled(bool checked);

    // Ko_impl interface
public slots:
    void open();
    void close();

    void setDate(QDate, SaveTo) override;
    void setTime(QTime, SaveTo) override;

    virtual QString t_print() override;
    virtual void setT1(double) override;
    virtual void setT2(double) override;
    virtual void setT3(double) override;
    virtual void setT4(double) override;

    virtual QString c_print() override;
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

private:
    void calibrationDataCome(int n, double deta);

signals:
    void measurement(StartMeasurement *);
    void calibration(StartMeasurement *);

private:
    Ui::Agr2 *ui;
//    SaveFiles file;
//    QStringList param;

    TestAgr2 *t_agr2;
    CalibrationAgr2 *c_agr2;
};

class StartTestAgr2 : public StartMeasurement
{
    Q_OBJECT
public:
    StartTestAgr2() = delete;
    static StartMeasurement* getStart(Test *t_agr2);
};

class StartCalibrationAgr2 : public StartMeasurement
{
    Q_OBJECT
public:
    StartCalibrationAgr2() = delete;
    static StartMeasurement *getStart(Calibration *c_agr2);
};

#endif // AGR2_H
