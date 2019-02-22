#ifndef KO4_H
#define KO4_H

#include <QWidget>
#include "savefiles.h"
#include "startmeasurement.h"

namespace Ui {
class Ko4;
}

class Ko4 : public QWidget
{
    Q_OBJECT

public:
    explicit Ko4(QWidget *parent = 0);
    ~Ko4();

private:
    void calibrationDataCome(int n, double deta);
    void open(CalibrationKo4 *c_ko4);
    void save();

private slots:
    void on_pushButton_test1_clicked();
    void on_pushButton_test2_clicked();
    void on_pushButton_calib_clicked();

    void on_radioButton_test1Single_toggled(bool checked);
    void on_checkBox_test1Ch1_toggled(bool checked);
    void on_checkBox_test1Ch2_toggled(bool checked);
    void on_checkBox_test1Ch3_toggled(bool checked);
    void on_checkBox_test1Ch4_toggled(bool checked);
    void on_lineEdit_test1Ch1_textChanged(const QString &arg1);
    void on_lineEdit_test1Ch3_textChanged(const QString &arg1);

    void on_radioButton_test2Single_toggled(bool checked);
    void on_checkBox_test2Ch1_toggled(bool checked);
    void on_checkBox_test2Ch2_toggled(bool checked);
    void on_checkBox_test2Ch3_toggled(bool checked);
    void on_checkBox_test2Ch4_toggled(bool checked);
    void on_lineEdit_test2Ch1_textChanged(const QString &arg1);
    void on_lineEdit_test2Ch3_textChanged(const QString &arg1);

    void on_radioButton_calibTrombine1_toggled(bool checked);
    void on_radioButton_calibTrombine2_toggled(bool checked);
    void on_radioButton_calibTrombine3_toggled(bool checked);

public slots:
    void calibrationData1Come(double);
    void calibrationData2Come(double);
    void calibrationData3Come(double);
    void calibrationData4Come(double);

signals:
    void measurement(StartMeasurement*);
    void calibration(StartMeasurement*);

private:
    Ui::Ko4 *ui;
//    SaveFiles file;
//    QStringList param;

    TestKo4 t_ko4;
    CalibrationKo4* c_ko4;
    CalibrationKo4_1* c_ko4_1;
    CalibrationKo4_2* c_ko4_2;
    CalibrationKo4_3* c_ko4_3;
};

class StartCalibrationKo4 : public StartMeasurement
{
    Q_OBJECT
public:
    StartCalibrationKo4() = delete;
    static StartMeasurement* getStart(Calibration* t_ko4);
};

class StartTestKo4 : public StartMeasurement
{
    Q_OBJECT
public:
    StartTestKo4() = delete;
    static StartMeasurement* getStart(Test* c_ko4);
};

#endif // KO4_H
