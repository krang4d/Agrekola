#ifndef AGR1_H
#define AGR1_H

#include <QWidget>
#include <QStringList>
#include "startmeasurment.h"
#include "savefiles.h"

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
    void measurement(StartMeasurment*);
    void calibration(StartMeasurment*);

private:
    Ui::Agr1 *ui;
    SaveFiles file;
    QStringList param;

    TestAgr1 t_agr1;
    CalibrationAgr1 c_agr1;
};

class StartCalibrationAgr1 : public StartMeasurment
{
    Q_OBJECT
public:
    StartCalibrationAgr1() = delete;
    static StartMeasurment *getStart();
    static StartMeasurment *getBTP100();
    static StartMeasurment *getOTP0();
};

#endif // AGR1_H
