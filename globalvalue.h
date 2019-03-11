#ifndef GLOBALVALUE_H
#define GLOBALVALUE_H

#include  "../XML/KoAgrXML/koagrxml.h"
#include "savefiles.h"

//Тип исследовани
enum Mode_ID {
    Level_ID = 0,   //Определение средненго значения
    Test_ID,        //Проверка
    TestAgr1_ID,    //Определение параметров агрегации
    TestAgr2_ID,    //Определение активности фактора Виллебранда
    TestKo1_ID,     //Время свертывания
    TestKo2_ID,     //АЧТВ
    TestKo3_ID,     //Фибриноген
    TestKo4_ID,     //Тромбин
    TestKo5_ID,     //Протромбиновый комплекс
    CalibAgr1_ID,
    CalibAgr2_ID,
    CalibKo1_ID,
    CalibKo2_ID,
    CalibKo3_ID,
    CalibKo4_ID,
    CalibKo5_ID,
};

//Состония
enum State_ID{
    Motor_ID,       //вкл.выкл моторов
    Laser_ID,       //вкл.выкл лазеров
    Ko_ID,          //измерение в режиме коаг
    Agr_ID,         //измерение в режиме агр
    Avg_ID,         //определение урвоня (БТП, ОТП и т.д.)
    Calc_ID,        //расчет параметров
    Incubation1_ID, //инкубация 1
    Incubation2_ID  //инкубация 2
};

//Каналы
enum Channel_ID {
    Channel1_ID     = 1,
    Channel2_ID     = 2,
    Channel3_ID     = 3,
    Channel4_ID     = 4,
    ChannelPP_ID    = 5,
    ChannelAll_ID   = 0
};

#endif // GLOBALVALUE_H
