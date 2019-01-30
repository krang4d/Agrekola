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
    static StartMeasurement *getBTP100();
    static StartMeasurement *getOTP0();
};

class StartTestAgr1 : public StartMeasurement
{
    Q_OBJECT
public:
    StartTestAgr1() = delete;
    static StartMeasurement* getStart(Test* t_agr1);
};


#endif // AGR1_H
