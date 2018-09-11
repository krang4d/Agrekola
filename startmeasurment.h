#ifndef STARTMEASURMENT_H
#define STARTMEASURMENT_H

#include <QDialog>
#include <QString>
#include "savefiles.h"

namespace Ui {
class StartMeasurment;
}

class StartMeasurment : public QDialog
{
    Q_OBJECT

public:
    explicit StartMeasurment(QDialog *parent = 0);
    StartMeasurment(int = 0, QDialog *parent = 0);
    ~StartMeasurment();

    bool isCancel();
    bool isSingle();
    bool isChannel(int = 0);
    setChannels(bool ch1, bool ch2, bool ch3, bool ch4);

    void setMode(int, bool single = 1);

    QString getNum(const int ch);
    void setNum(const int ch, const QString num);

    int getTime();
    void setTime(int);

    int getTimeIncube(int = 1);
    void setTimeIncube(int i, int ts);

    QString getStringStatus();

    void saveData();
    void openData();

public slots:
    void on_checkBox_ch1_stateChanged(int arg1);
    void on_checkBox_ch2_stateChanged(int arg1);
    void on_checkBox_ch3_stateChanged(int arg1);
    void on_checkBox_ch4_stateChanged(int arg1);
    void on_radioButton_single_toggled(bool checked);
    void on_pushButton_next_clicked();
//  void on_pushButton_cancel_clicked();

signals:
    startMeasurment(StartMeasurment*);

private:
    Ui::StartMeasurment *ui;
    SaveFiles file;
    QStringList param;
    bool cancel;
    bool single;       //пробы одиночные?
    bool channel_1, channel_2, channel_3, channel_4;
    QString num_1, num_2, num_3, num_4;
    int time;           //время записи
    int time_incube, time_incube_2; //время инкубации
};

#endif // STARTMEASURMENT_H
