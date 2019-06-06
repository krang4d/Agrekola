#ifndef GLOBALVALUE_H
#define GLOBALVALUE_H

//#include  "../XML/KoAgrXML/koagrxml.h"
#include "savefiles.h"

//Тип исследовани
enum Mode_ID {
    Level_ID = 0,   //Определение средненго значения
//    Test_ID,        //Проверка
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
    CalibKo5_ID
};

//Каналы
enum Channel_ID {
    Channel1_ID     = 1,
    Channel2_ID     = 2,
    Channel3_ID     = 3,
    Channel4_ID     = 4,
    ChannelPP_ID    = 5
};

#endif // GLOBALVALUE_H
