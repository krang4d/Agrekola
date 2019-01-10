#ifndef GLOBALVALUE_H
#define GLOBALVALUE_H

#include  "../XML/KoAgrXML/koagrxml.h"
#include "savefiles.h"

enum Mode_ID { Test_ID = 0,
               TestAgr1_ID,
               TestAgr2_ID,
               TestKo1_ID,
               TestKo2_ID,
               TestKo3_ID,
               TestKo4_ID,
               TestKo5_ID,
               Level_ID
             };
enum Calibr_ID { CalibrAgr1_ID  = 0,
                 CalibrAgr2_ID,
                 CalibrKo1_ID,
                 CalibrKo2_ID,
                 CalibrKo3_ID,
                 CalibrKo4_ID,
                 CalibrKo5_ID
               };

#endif // GLOBALVALUE_H
