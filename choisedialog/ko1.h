#ifndef KO1_H
#define KO1_H

#include <QWidget>
#include "savefiles.h"
#include "startmeasurment.h"
#include "globalvalue.h"

namespace Ui {
class Ko1;
}

class Ko1 : public QWidget
{
    Q_OBJECT

public:
    explicit Ko1(QWidget *parent = 0);
    ~Ko1();

private slots:
    void on_pushButton_clicked();
    void on_checkBox_ch1_stateChanged(int arg1);
    void on_checkBox_ch2_stateChanged(int arg1);
    void on_checkBox_ch3_stateChanged(int arg1);
    void on_checkBox_ch4_stateChanged(int arg1);

    void on_radioButton_single_toggled(bool checked);

    void on_radioButton_double_toggled(bool checked);

signals:
    void measurement(StartMeasurment*);

private:
    Ui::Ko1 *ui;
    //SaveFiles file;
    //QStringList param;
    //StartMeasurment *startPar;
    TestKo1 t_ko1;
};

class StartTestKo1 : public StartMeasurment
{
    Q_OBJECT
public:
    StartTestKo1() = delete;
    static StartMeasurment* getStart();
};

class StartCalibrationKo1 : public StartMeasurment
{
    Q_OBJECT
public:
    StartCalibrationKo1() = delete;
    static StartMeasurment* getStart();
};

#endif // KO1_H
