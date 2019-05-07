#ifndef KO4_H
#define KO4_H

#include <QWidget>
#include "savefiles.h"
#include "startmeasurement.h"
#include "ko_impl.h"

namespace Ui {
class Ko4;
}

class Ko4 : public QWidget, public Ko_impl
{
    Q_OBJECT

public:
    explicit Ko4(QWidget *parent = 0);
    void setTab(int);
    ~Ko4();

private:
    void calibrationDataCome(int n, double deta);
    void open(TestKo4* t_ko4, CalibrationKo4 *c_ko4);

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

    void on_radioButton_calibActivity1_toggled(bool checked);
    void on_radioButton_calibActivity2_toggled(bool checked);
    void on_radioButton_calibActivity3_toggled(bool checked);

    void on_radioButton_testActivity1_toggled(bool checked);
    void on_radioButton_testActivity2_toggled(bool checked);
    void on_radioButton_testActivity3_toggled(bool checked);

    void on_tabWidget_currentChanged(int index);
    void on_radioButton_test1Double_toggled(bool checked);
    void on_radioButton_test2Double_toggled(bool checked);

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

signals:
    void measurement(StartMeasurement*);
    void calibration(StartMeasurement*);

private:
    Ui::Ko4 *ui;
//    SaveFiles file;
//    QStringList param;

    TestKo4 *t_ko4;
    TestKo4 *t_ko4_1; //параметры тест
    TestKo4 *t_ko4_2; //параметры тест без калибровки
    CalibrationKo4 *c_ko4;
    CalibrationKo4_1 *c_ko4_1;  //параметры калибровка с активностью тромбина 1
    CalibrationKo4_2 *c_ko4_2;  //параметры калибровка с активностью тромбина 2
    CalibrationKo4_3 *c_ko4_3;  //параметры калибровка с активностью тромбина 3
    Ko_impl::Mode_ID mode;
};

class StartCalibrationKo4 : public StartMeasurement
{
    Q_OBJECT
public:
    StartCalibrationKo4() = delete;
    static StartMeasurement* getStart(TestKo4 *t_ko4, CalibrationKo4 *c_ko4);
};

class StartTestKo4 : public StartMeasurement
{
    Q_OBJECT
public:
    StartTestKo4() = delete;
    static StartMeasurement* getStart(TestKo4 *t_ko4, CalibrationKo4 *c_ko4);
};

#endif // KO4_H
