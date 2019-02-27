#ifndef GLOBALVALUE_H
#define GLOBALVALUE_H

#include  "../XML/KoAgrXML/koagrxml.h"
#include "savefiles.h"
#include <QVector>

enum Mode_ID {
    Test_ID = 0,
    TestAgr1_ID,
    TestAgr2_ID,
    TestKo1_ID,
    TestKo2_ID,
    TestKo3_ID,
    TestKo4_ID,
    TestKo5_ID,
    Level_ID,
    CalibAgr1_ID,
    CalibAgr2_ID,
    CalibKo1_ID,
    CalibKo2_ID,
    CalibKo3_ID,
    CalibKo4_ID,
    CalibKo5_ID,
    BTPTestAgr1_ID,
    BTPCalibAgr1_ID,
    OTPTestAgr1_ID,
    OTPCalibAgr1_ID,
    BTPTestAgr2_ID,
    BTPCalibAgr2_ID,
    OTPCalibAgr2_ID,
    Incubation1_ID,
    Incubation2_ID
};

enum Channel_ID {
    Channel1_ID     = 1,
    Channel2_ID     = 2,
    Channel3_ID     = 3,
    Channel4_ID     = 4,
    ChannelPP_ID    = 5,
    ChannelAll_ID   = 0
};
//enum State_ID {
//    Level_ID,
//    Incubation_ID
//};


//enum Calibr_ID { CalibrAgr1_ID  = 0,
//                 CalibrAgr2_ID,
//                 CalibrKo1_ID,
//                 CalibrKo2_ID,
//                 CalibrKo3_ID,
//                 CalibrKo4_ID,
//                 CalibrKo5_ID
//               };


#endif // GLOBALVALUE_H
