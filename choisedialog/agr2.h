#ifndef AGR2_H
#define AGR2_H

#include <QWidget>
#include "kalibragr2.h"
#include "selectcalibrationagr1.h"
#include "selectinductor.h"
#include "savefiles.h"
#include "startmeasurement.h"

struct Error_Agr2_Type_ID
{
    QString err_msg;
    Error_Agr2_Type_ID(const QString &m) : err_msg(m) {}
};

namespace Ui {
class Agr2;
}

class Agr2 : public QWidget
{
    Q_OBJECT

public:
    explicit Agr2(QWidget *parent = 0);
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

public slots:
    void calibrationData1Come(double);
    void calibrationData2Come(double);
    void calibrationData3Come(double);
    void calibrationData4Come(double);

private:
    void calibrationDataCome(int n, double deta);
    void open();
    void save();

signals:
    void measurement(StartMeasurement *);
    void calibration(StartMeasurement *);

private:
    Ui::Agr2 *ui;
//    SaveFiles file;
//    QStringList param;

    TestAgr2 t_agr2;
    CalibrationAgr2 c_agr2;
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
