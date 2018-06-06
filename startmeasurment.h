#ifndef STARTMEASURMENT_H
#define STARTMEASURMENT_H

#include <QWidget>

namespace Ui {
class StartMeasurment;
}

class StartMeasurment : public QWidget
{
    Q_OBJECT

public:
    explicit StartMeasurment(QWidget *parent = 0);
    ~StartMeasurment();

private slots:
    void on_checkBox_ch1_stateChanged(int arg1);

    void on_checkBox_ch2_stateChanged(int arg1);

    void on_checkBox_ch3_stateChanged(int arg1);

    void on_checkBox_ch4_stateChanged(int arg1);

    void on_pushButton_next_clicked();

private:
    Ui::StartMeasurment *ui;
};

#endif // STARTMEASURMENT_H
