#ifndef KO_IMPL_H
#define KO_IMPL_H

class QString;
class QDate;
class QTime;

class Ko_impl
{
public:

//    //Тип исследовани
//    enum Mode_ID {
//        Level_ID = 0,   //Определение средненго значения
//        //Test_ID,        //Проверка
//        TestAgr1_ID,    //Определение параметров агрегации
//        TestAgr2_ID,    //Определение активности фактора Виллебранда
//        TestKo1_ID,     //Время свертывания
//        TestKo2_ID,     //АЧТВ
//        TestKo3_ID,     //Фибриноген
//        TestKo4_ID,     //Тромбин
//        TestKo5_ID,     //Протромбиновый комплекс
//        CalibAgr1_ID,
//        CalibAgr2_ID,
//        CalibKo1_ID,
//        CalibKo2_ID,
//        CalibKo3_ID,
//        CalibKo4_ID,
//        CalibKo5_ID,
//    };

//    //Каналы
//    enum Channel_ID {
//        Channel1_ID     = 1,
//        Channel2_ID     = 2,
//        Channel3_ID     = 3,
//        Channel4_ID     = 4,
//        ChannelPP_ID    = 5,
//        ChannelAll_ID   = 0
//    };

    enum SaveTo {
        Test_ID,
        Calib_ID
    };

    virtual void open() = 0;
    virtual void close() = 0;
    virtual void setDate(QDate , SaveTo) = 0;
    virtual void setTime(QTime, SaveTo) = 0;

    virtual QString t_print() = 0;
    virtual void setT1(double, int = 0) = 0;
    virtual void setT2(double, int = 0) = 0;
    virtual void setT3(double, int = 0) = 0;
    virtual void setT4(double, int = 0) = 0;

    virtual void setT1_2(double, int = 0) = 0;
    virtual void setT3_4(double, int = 0) = 0;

    virtual QString c_print() = 0;
    virtual void calibrationData1Come(double, int = 0) = 0;
    virtual void calibrationData2Come(double, int = 0) = 0;
    virtual void calibrationData3Come(double, int = 0) = 0;
    virtual void calibrationData4Come(double, int = 0) = 0;

    virtual void calibrationData1_2Come(double, int = 0) = 0;
    virtual void calibrationData2_4Come(double, int = 0) = 0;

//    virtual Mode_ID getModeID() const = 0 ;
//    virtual bool isSingle() = 0;
//    virtual bool isChannel(Channel_ID = ChannelAll_ID) = 0;
//    virtual QString getNum(const int ch) = 0;
//    virtual double getTimeWrite() = 0;
//    virtual double getTimeIncube(int = 1) = 0;
};

#endif // KO_IMPL_H
