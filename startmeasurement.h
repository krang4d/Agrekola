#ifndef STARTMEASUREMENT_H
#define STARTMEASUREMENT_H

#include <QDialog>
#include <QString>
#include <QCheckBox>
#include <QMessageBox>
#include "savefiles.h"
#include "globalvalue.h"
#include  "../XML/KoAgrXML/koagrxml.h"

class StartMeasurement : public QDialog
{
    Q_OBJECT

public:
    StartMeasurement(Test *t, Calibration *c, QDialog *parent = nullptr);
    ~StartMeasurement();

    bool isSingle();
    bool isChannel(Channel_ID);
    void setChannels(bool ch1, bool ch2, bool ch3, bool ch4);

    Mode_ID getModeID() const;
    void setModeID(const Mode_ID &value);

    void setProbe(bool is_single = true);

    QString getNum(const int ch);
    void setNum(const int ch, const QString num);

    double getTimeWrite();
    void setTimeWrite(double s);

    double getTimeIncube(int = 1);
    double setTimeIncube(int incube_number, double time_s);

//    QString getStringStatus();

//    int num;

    double getBtp_time() const;
    void setBtp_time(double value);

    double getOtp_time() const;
    void setOtp_time(double value);

    Calibration *getCalib() const;
    void setCalib(Calibration *value);

    Test *getTest() const;
    void setTest(Test *value);

public slots:
    //    inline void setCheckState2(int i) {
    //        //QMessageBox::information(0, "StartMeasurment", QString("setCheckState2(%1)").arg(i));
//        if(i == 0)
//            channel_2 = false;
//        else channel_2 = true;
//    }
//    inline void setCheckState4(int i) {
//        if(i == 0)
//            channel_4 = false;
//        else channel_4 = true;
//    }
//    //  void on_pushButton_cancel_clicked();

signals:
    void startMeasurment(StartMeasurement*);

private:
    bool single;       //пробы одиночные?
    bool channel_1, channel_2, channel_3, channel_4;
    QString num_1, num_2, num_3, num_4;
    double time;                        //время записи
    double time_incube, time_incube_2, btp_time, otp_time;  //время инкубации
    Mode_ID modeID;

    Calibration *calib;
    Test *test;
};

#endif // STARTMEASUREMENT_H
