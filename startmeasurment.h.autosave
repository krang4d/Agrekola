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

    bool isSingle();
    bool isChannel_1();
    bool isChannel_2();
    bool isChannel_3();
    bool isChannel_4();

    QString getNum_1();
    QString getNum_2();
    QString getNum_3();
    QString getNum_4();

    double getFreq();
    int getTime();

private slots:
    void on_checkBox_ch1_stateChanged(int arg1);
    void on_checkBox_ch2_stateChanged(int arg1);
    void on_checkBox_ch3_stateChanged(int arg1);
    void on_checkBox_ch4_stateChanged(int arg1);
    void on_pushButton_next_clicked();
    void on_radioButton_single_toggled(bool checked);

signals:
    startMeasurment();

private:
    bool single;       //пробы одиночные?
    bool channel_1;
    bool channel_2;
    bool channel_3;
    bool channel_4;
    QString num_1;
    QString num_2;
    QString num_3;
    QString num_4;
    double freq;        //интервал между точками
    int time;           //время записи

    Ui::StartMeasurment *ui;
};

#endif // STARTMEASURMENT_H
