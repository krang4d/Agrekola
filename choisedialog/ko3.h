#ifndef KO3_H
#define KO3_H

#include <QWidget>
#include "savefiles.h"
#include "startmeasurment.h"

namespace Ui {
class Ko3;
}

class Ko3 : public QWidget
{
    Q_OBJECT

public:
    explicit Ko3(QWidget *parent = 0);
    ~Ko3();

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
    void calibrationData1Come(double);
    void calibrationData2Come(double);
    void calibrationData3Come(double);
    void calibrationData4Come(double);

signals:
    void measurement(StartMeasurment *);
    void calibration(StartMeasurment *);

private:
    Ui::Ko3 *ui;
//    SaveFiles file;
//    QStringList param;

    TestKo3 t_ko3;
    CalibrationKo3 c_ko3;
};

class StartTestKo3 : public StartMeasurment
{
    Q_OBJECT
public:
    StartTestKo3() = delete;
    static StartMeasurment* getStart();
};

class StartCalibrationKo3 : public StartMeasurment
{
    Q_OBJECT
public:
    StartCalibrationKo3() = delete;
    static StartMeasurment* getStart();
};

#endif // KO3_H
