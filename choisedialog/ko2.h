#ifndef KO2_H
#define KO2_H

#include <QWidget>
#include "globalvalue.h"
#include "startmeasurement.h"
#include "ko_impl.h"

namespace Ui {
class Ko2;
}

class Ko2 : public QWidget, public Ko_impl
{
    Q_OBJECT

public:
    explicit Ko2(QWidget *parent = 0);
    void setTab(int);
    ~Ko2();

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

private slots:
    void on_pushButton_test1_clicked();
    void on_pushButton_test2_clicked();
    void on_pushButton_calib_clicked();

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

    void on_tabWidget_currentChanged(int index);

signals:
    void measurement(StartMeasurement*);
    void calibration(StartMeasurement*); 
    //void calibration_done();

private:
    Ui::Ko2 *ui;
    TestKo2 *t_ko2, *t_ko2_1, *t_ko2_2;
    CalibrationKo2 *c_ko2;
    Ko_impl::Mode_ID mode;

//    friend class StartTestKo2;
//    friend class StartCalibrationKo2;
};

class StartTestKo2 : public StartMeasurement
{
    Q_OBJECT
public:
    StartTestKo2() = delete;
    static StartMeasurement* getStart(TestKo2 *t_ko2, CalibrationKo2 *c_ko2);
};

class StartCalibrationKo2 : public StartMeasurement
{
    Q_OBJECT
public:
    StartCalibrationKo2() = delete;
    static StartMeasurement* getStart(TestKo2 *t_ko2, CalibrationKo2 *c_ko2);
};

#endif // KO2_H
