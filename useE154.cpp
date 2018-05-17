//#include "StdAfx.h"
#include "useE154.h"


// кол-во получаемых отсчетов
DWORD DataStep = 256*1024;
// буфер данных
SHORT *ReadBuffer;

UseE154::UseE154(QWidget *parent) : AdcRate(100), InputRangeIndex(ADC_INPUT_RANGE_5000mV_E154)
{
    eModule = new LoadE154();
    pModule = eModule->GetAPI();
    if(!pModule) throw Errore_E154("Ошибка загрузи библиотеки Dll Load_Dll()!");
    //OpenDevice();
    IniPorts();
    IniADC();
}

UseE154::~UseE154(void)
{
    delete eModule;
}
//typedef DWORD (WINAPI *pGetDllVersion)(void);
//typedef LPVOID (WINAPI *pCreateInstance)(char *);
double UseE154::AdcSample(){
    SHORT AdcSample;
    double AdcVolt;
    if(!pModule->ADC_SAMPLE(&AdcSample, (WORD)(0x00  | (InputRangeIndex << 6)))) { throw Errore_E154("\n\n  ADC_SAMPLE(, 0) --> Bad\n");}
    if(!pModule->ProcessOnePoint(AdcSample, &AdcVolt, (WORD)(0x00  | (InputRangeIndex << 6)), TRUE, TRUE))
       { throw Errore_E154("\n\n  PreocessOnePoint() --> Bad\n"); }
    //emit ValueCome(AdcVolt);
    return AdcVolt;
}

void UseE154::AdcKADR()
{
    SHORT AdcBuffer[4];
    pModule->STOP_ADC();
    pModule->GET_MODULE_DESCRIPTION(&ModuleDescription);
    // получим текущие параметры работы АЦП
    if(!pModule->GET_ADC_PARS(&ap)) throw Errore_E154("GET_ADC_PARS() --> Bad\n");
    if(!pModule->ADC_KADR(AdcBuffer)) throw Errore_E154("ADC_KADR() --> Bad\n");
    if(!pModule->ProcessArray(AdcBuffer, volts_array, 4, TRUE, TRUE)) throw Errore_E154("ProcessArray() --> Bad\n");
    emit ValueCome();
}

void UseE154::AdcSynchro()
{
    pModule->STOP_ADC();
    // выделим память под буфер
    ReadBuffer = new SHORT[DataStep];
    if(!ReadBuffer) throw Errore_E154("Ошибка выделения памяти под буфер фанных\n");

    // формируем структуру IoReq
    IoReq.Buffer = ReadBuffer;					// буфер данных
    IoReq.NumberOfWordsToPass = DataStep;       // кол-во собираемых данных
    IoReq.NumberOfWordsPassed = 0x0;
    IoReq.Overlapped = NULL;					// синхронный вариант запроса
    IoReq.TimeOut = DataStep/ap.AdcRate + 1000;	// таймаут синхронного сбора данных

    pModule->GET_MODULE_DESCRIPTION(&ModuleDescription);
    if(!pModule->START_ADC()) throw Errore_E154("Ошибка при запуске АЦП AdcSynchro()!\n");
    if(!pModule->ReadData(&IoReq)) throw Errore_E154("Ошибка при чтении данных AdcSynchro()!\n");
    DWORD Size = IoReq.NumberOfWordsPassed;
    double Destination[Size];
    SHORT *AdcData = IoReq.Buffer;
    if(!pModule->ProcessArray(AdcData, Destination, Size, TRUE, TRUE)) throw Errore_E154("Ошибка преобразования кода АЦП ProcessArray()\n");
}

void UseE154::IniPorts()
{
    if(pModule->ENABLE_TTL_OUT(1)) pModule->TTL_OUT(0); else throw Errore_E154("Ошибка включения линий TTL");
}

std::string UseE154::IniADC()
{
    pModule->STOP_ADC();
    if(!pModule->GET_ADC_PARS(&ap)) throw Errore_E154("Ошибка получния параметров АЦП!\n");
    ap.ClkSource = INT_ADC_CLOCK_E154;                      // внутренний запуск АЦП
    ap.EnableClkOutput = ADC_CLOCK_TRANS_DISABLED_E154; 	// без трансляции тактовых импульсо АЦП
    ap.InputMode = NO_SYNC_E154;                            // без синхронизации ввода данных
    ap.ChannelsQuantity = 0x4;                // кол-во активных каналов
    // формируем управляющую таблицу
    for(int i = 0x0; i < ap.ChannelsQuantity; i++) ap.ControlTable[i] = (WORD)(i | (ADC_INPUT_RANGE_5000mV_E154 << 0x6));
    ap.AdcRate = 100.0;								// частота работы АЦП в кГц
    ap.InterKadrDelay = 0.0;							// межкадровая задержка в мс
    // передадим требуемые параметры работы АЦП в модуль
    if(!pModule->SET_ADC_PARS(&ap)) throw Errore_E154("Ошибка установки параметрв АЦП!\n");
    return std::string("initADC()/n");
}

void UseE154::SetChannel(channel ch, int pos)
{
    if(pos == ON){
    switch(ch){
            case CH1: { TtlOut |= (1<<0); pModule->TTL_OUT(TtlOut); break; }
            case CH2: { TtlOut |= (1<<1); pModule->TTL_OUT(TtlOut); break; }
            case CH3: { TtlOut |= (1<<2); pModule->TTL_OUT(TtlOut); break; }
            case CH4: { TtlOut |= (1<<3); pModule->TTL_OUT(TtlOut); break; }
            case  PP: { TtlOut |= (1<<4); pModule->TTL_OUT(TtlOut); break; }
            case   L: { TtlOut |= (1<<5); pModule->TTL_OUT(TtlOut); break; }
                default: throw Errore_E154("Неправильно выбран TTL канал");
     }
    }
    else{
     switch(ch){
            case CH1: { TtlOut &= ~(1<<0); pModule->TTL_OUT(TtlOut); break; }
            case CH2: { TtlOut &= ~(1<<1); pModule->TTL_OUT(TtlOut); break; }
            case CH3: { TtlOut &= ~(1<<2); pModule->TTL_OUT(TtlOut); break; }
            case CH4: { TtlOut &= ~(1<<3); pModule->TTL_OUT(TtlOut); break; }
            case  PP: { TtlOut &= ~(1<<4); pModule->TTL_OUT(TtlOut); break; }
            case   L: { TtlOut &= ~(1<<5); pModule->TTL_OUT(TtlOut); break; }
                default: throw Errore_E154("Неправильно выбран TTL канал");
        }
    }
}

bool UseE154::GetStatusTD()
{
    pModule->TTL_IN(&TtlIN); if(TtlIN & (1<<0)) return TRUE; else return FALSE;
}

string UseE154::GetUserMessages() const
{
    return user_msg.back();
}
