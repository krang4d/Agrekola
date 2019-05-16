#include "startmeasurement.h"
#include "ui_startmeasurement.h"

#include <QMessageBox>
#include <QString>

StartMeasurement::StartMeasurement(Test *t, Calibration *c, QDialog *parent) :
    test(t), calib(c),
    QDialog(parent)
{
    setModal(true);
    single = true;
    channel_1 = false;
    channel_2 = false;
    channel_3 = false;
    channel_4 = false;
    num_1 = "";
    num_2 = "";
    num_3 = "";
    num_4 = "";
    time = 0;
    time_incube = 0;
}

StartMeasurement::~StartMeasurement()
{
}

bool StartMeasurement::isChannel(Channel_ID ch)
{
    switch (ch) {
//    case ChannelAll_ID:
//        return channel_1 || channel_2 ||channel_3 || channel_4;
//        break;
    case Channel1_ID:
        return channel_1;
        break;
    case Channel2_ID:
        return channel_2;
        break;
    case Channel3_ID:
        return channel_3;
        break;
    case Channel4_ID:
        return channel_4;
        break;
    default:
        return channel_1 || channel_2 ||channel_3 || channel_4;
    }
}

void StartMeasurement::setChannels(bool ch1, bool ch2, bool ch3, bool ch4)
{
//    num = 0;
//    if(ch1) num++;
//    if(ch2) num++;
//    if(ch3) num++;
//    if(ch4) num++;
    channel_1 = ch1;
    channel_2 = ch2;
    channel_3 = ch3;
    channel_4 = ch4;
}

void StartMeasurement::setProbe(bool is_single)
{
    single = is_single;
}

bool StartMeasurement::isSingle()
{
    return single;
}

QString StartMeasurement::getNum(const int ch)
{
    switch ( ch ) {
    case 1:
        return num_1;
        break;
    case 2:
        return num_2;
        break;
    case 3:
        return num_3;
        break;
    case 4:
        return num_4;
        break;
    default:
        return 0;
    }
}

void StartMeasurement::setNum(const int ch, const QString num)
{
    switch ( ch ) {
    case 1:
        num_1 = num;
        break;
    case 2:
        num_2 = num;
        break;
    case 3:
        num_3 = num;
        break;
    case 4:
        num_4 = num;
        break;
    default:
        return;
    }
}

double StartMeasurement::getTimeWrite()
{
    return time;
}

void StartMeasurement::setTimeWrite(double s)
{
    time = s;
}

double StartMeasurement::getTimeIncube(int i)
{
    if(i == 1)
        return time_incube;
    else return time_incube_2;
}

double StartMeasurement::setTimeIncube(int incube_number, double time_s)
{
    if(incube_number == 1)
        time_incube = time_s;
    else time_incube_2 = time_s;
}

//QString StartMeasurement::getStringStatus()
//{
//    QString msg;
//    if(isSingle()) {
//        if (isChannel(Channel1_ID)) {
//            msg += QString("№1 %1 ").arg(getNum(1));
//        }
//        else {
//            msg += QString(" ");
//        }

//        if (isChannel(Channel2_ID)) {
//            msg += QString("№2 %1 ").arg(getNum(2));
//        }
//        else {
//            msg += QString(" ");
//        }

//        if (isChannel(Channel3_ID)) {
//            msg += QString("№3 %1 ").arg(getNum(3));
//        }
//        else {
//            msg += QString(" ");
//        }

//        if (isChannel(Channel4_ID)) {
//            msg += QString("№4 %1 ").arg(getNum(4));
//        }
//        else {
//            msg += QString(" ");
//        }
////        //---->> магические числа для времени инкубации 2
////        if(getMode() == 1 && getMode() == 2) {
////            msg = QString("Начало сбора данных, одиночные пробы (t = %1c, %2)")
////                    .arg(startWin->getTime()).arg(msg);
////        }
//        msg = QString("Одиночные пробы %2, Время записи %1c")
//                .arg(getTimeWrite()).arg(msg);
//    }
//    else {
//        if (isChannel(Channel1_ID)) {
//            msg += QString("№1, 2: %1 ").arg(getNum(1));
//        }
//        else {
//            msg += QString(" ");
//        }

//        if (isChannel(Channel3_ID)) {
//            msg += QString("№3, 4: %1 ").arg(getNum(3));
//        }
//        else {
//            msg += QString(" ");
//        }
//        msg = QString("Парные пробы %2, Время записи %1c")
//                .arg(getTimeWrite()).arg(msg);
//    }
//    return msg;
//}

double StartMeasurement::getOtp_time() const
{
    return otp_time;
}

void StartMeasurement::setOtp_time(double value)
{
    otp_time = value;
}

Calibration *StartMeasurement::getCalib() const
{
    return calib;
}

void StartMeasurement::setCalib(Calibration *value)
{
    calib = value;
}

Test *StartMeasurement::getTest() const
{
    return test;
}

void StartMeasurement::setTest(Test *value)
{
    test = value;
}

double StartMeasurement::getBtp_time() const
{
    return btp_time;
}

void StartMeasurement::setBtp_time(double value)
{
    btp_time = value;
}

Mode_ID StartMeasurement::getModeID() const
{
    return modeID;
}

void StartMeasurement::setModeID(const Mode_ID &value)
{
    modeID = value;
}

