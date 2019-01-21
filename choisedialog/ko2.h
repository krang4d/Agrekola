#ifndef KO2_H
#define KO2_H

#include <QWidget>
#include "globalvalue.h"
#include "startmeasurment.h"

namespace Ui {
class Ko2;
}

class Ko2 : public QWidget
{
    Q_OBJECT

public:
    explicit Ko2(QWidget *parent = 0);
    ~Ko2();

private:
    void calibrationDataCome(int n, double deta);
    void open();
    void close();

private slots:
    void on_pushButton_test1_clicked();
    void on_pushButton_test2_clicked();
    void on_pushButton_calib_clicked();

    void on_toolBox_currentChanged(int index);

    void on_radioButton_test1Single_toggled(bool checked);
    void on_radioButton_test2Single_toggled(bool checked);

    void on_checkBox_test1Ch1_toggled(bool checked);
    void on_checkBox_test1Ch2_toggled(bool checked);
    void on_checkBox_test1Ch3_toggled(bool checked);
    void on_checkBox_test1Ch4_toggled(bool checked);
    void on_checkBox_test2Ch1_toggled(bool checked);
    void on_checkBox_test2Ch2_toggled(bool checked);
    void on_checkBox_test2Ch3_toggled(bool checked);
    void on_checkBox_test2Ch4_toggled(bool checked);

    void on_lineEdit_test1Ch1_textChanged(const QString &arg1);
    void on_lineEdit_test1Ch3_textChanged(const QString &arg1);
    void on_lineEdit_test2Ch1_textChanged(const QString &arg1);
    void on_lineEdit_test2Ch3_textChanged(const QString &arg1);

public slots:
    void calibrationData1Come(double);
    void calibrationData2Come(double);
    void calibrationData3Come(double);
    void calibrationData4Come(double);

signals:
    void measurement(StartMeasurment*);
    void calibration(StartMeasurment*);

private:
    Ui::Ko2 *ui;
    SaveFiles file;
    QStringList param;

    TestKo2 t_ko2;
    CalibrationKo2 c_ko2;
};

class StartTestKo2 : public StartMeasurment
{
    Q_OBJECT
public:
    StartTestKo2() = delete;
    static StartMeasurment* getStart();
};


class StartCalibrationKo2 : public StartMeasurment
{
    Q_OBJECT
public:
    StartCalibrationKo2() = delete;
    static StartMeasurment* getStart();
};

#endif // KO2_H
