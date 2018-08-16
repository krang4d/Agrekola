﻿#include "useE154.h"
#include <QFunctionPointer>
#include <QTime>

useE154::useE154(QThread *parent) :
    QThread(parent)
{
    pModule = OnlyOneE154::Instance().getModule();
	OpenDevice();
    initPorts();
    initADC();
}

useE154::~useE154(void)
{
    CloseDevice();
    delete[] pDestination;
    qDebug() << "~useE154()";
}

 double useE154::AdcSample(Channel ch)
{
    pModule->STOP_ADC();
    SHORT AdcSample;
    double AdcVolt;
    if(!pModule->ADC_SAMPLE(&AdcSample, (WORD)(ch  | (ADC_INPUT_RANGE_5000mV_E154 << 6)))) { throw Errore_E154("\n\n  ADC_SAMPLE(, 0) --> Bad\n"); }
    if(!pModule->ProcessOnePoint(AdcSample, &AdcVolt, (WORD)(ch  | (ADC_INPUT_RANGE_5000mV_E154 << 6)), TRUE, TRUE)) { throw Errore_E154("\n\n  PreocessOnePoint() --> Bad\n"); }
    pModule->STOP_ADC();
    return AdcVolt;
}

QVariantList useE154::AdcKADR()
{
    SHORT AdcBuffer[4];
    double volt[16];
    pModule->STOP_ADC();
    //pModule->GET_MODULE_DESCRIPTION(&ModuleDescription);
    // получим текущие параметры работы АЦП
    //if(!pModule->GET_ADC_PARS(&ap)) throw Errore_E154("GET_ADC_PARS() --> Bad\n");
    if(!pModule->ADC_KADR(AdcBuffer)) throw Errore_E154("ADC_KADR() --> Bad\n");
    if(!pModule->ProcessArray(AdcBuffer, volt, 0x4, TRUE, TRUE)) throw Errore_E154("ProcessArray() --> Bad\n");
    pModule->STOP_ADC();
    vec_data.clear();
    vec_data.push_back(volt[0]);
    vec_data.push_back(volt[1]);
    vec_data.push_back(volt[2]);
    vec_data.push_back(volt[3]);
    //sqDebug() << "ThreadID: " << QThread::currentThreadId() << " V0 = " << volt[0];
    QVariantList qvar;
    qvar.append(volt[0]);
    qvar.append(volt[1]);
    qvar.append(volt[2]);
    qvar.append(volt[3]);
    //emit value_come(qvar);
    return qvar;
}

QString useE154::AdcSynchro()
{
    DoubleData Destination = AdcSynchroDouble();
    int Size = Destination.size;
    QString readDataString;
    readDataString += QString("useE154::AdcSynchro() size:%1\n").arg(Size);
    readDataString += QString("Sample[0]=%1\n").arg(Destination.data[0]);
    readDataString += QString("Sample[%1]=%2").arg(Size-1).arg(Destination.data[Size-1]);
    for(int i=0; i<Size; i++)
    {
        vec_data.append(Destination.data[i]);
        readDataString += QString("№%1 val%2").arg(i).arg(vec_data[i]);
    }
    //if(!ReadBuffer) {delete[] ReadBuffer; ReadBuffer = NULL;}
return readDataString;
}
DoubleData useE154::AdcSynchroDouble()
{
    // кол-во получаемых отсчетов
    DWORD DataStep = 100;
    // выделим память под буфер
    SHORT *ReadBuffer = new SHORT[DataStep];
    pModule->STOP_ADC();
    if(!ReadBuffer) throw Errore_E154("Ошибка выделения памяти под буфер данных\n");

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

    if(!pDestination) {delete pDestination; pDestination = NULL;}
    pDestination = new double[Size];
    DoubleData data(pDestination, Size);
    SHORT *AdcData = IoReq.Buffer;
    if(!pModule->ProcessArray(AdcData, pDestination, Size, TRUE, TRUE)) throw Errore_E154("Ошибка преобразования кода АЦП ProcessArray()\n");
    if(!ReadBuffer) {delete[] ReadBuffer; ReadBuffer = NULL;}
    return data;
}

void useE154::initPorts()
{
    if(pModule->ENABLE_TTL_OUT(1)) pModule->TTL_OUT(0); else qDebug().noquote() << QString("Ошибка включения линий TTL");
}

void useE154::initADC()
{
    pModule->STOP_ADC();
    if(!pModule->GET_ADC_PARS(&ap)) qDebug().noquote() << QString("Ошибка получния параметров АЦП!\n");
    ap.ClkSource = INT_ADC_CLOCK_E154;                      // внутренний запуск АЦП
    ap.EnableClkOutput = ADC_CLOCK_TRANS_DISABLED_E154; 	// без трансляции тактовых импульсо АЦП
    ap.InputMode = NO_SYNC_E154;                            // без синхронизации ввода данных
    ap.ChannelsQuantity = 0x4;                              // кол-во активных каналов
    // формируем управляющую таблицу
    for(int i = 0x0; i < ap.ChannelsQuantity; i++)
        ap.ControlTable[i] = (WORD)(i | (ADC_INPUT_RANGE_5000mV_E154 << 0x6));
    ap.AdcRate = 100.0;                                     // частота работы АЦП в кГц
    ap.InterKadrDelay = 0.0;                                // межкадровая задержка в мс
    // передадим требуемые параметры работы АЦП в модуль
    if(!pModule->SET_ADC_PARS(&ap)) qDebug().noquote() << QString("Ошибка установки параметрв АЦП!\n");
    //return QString("initADC()");
}

void useE154::funThread()
{
    while(!thread_stop){
        static QTime time(QTime::currentTime());
        static double lastPointKey = 0;
        double key = time.elapsed()/1000.0; // time elapsed since start in seconds
        if(key - lastPointKey > 1) {
        emit update_termo(GetStatusTD());
        lastPointKey = key;
        }
        emit value_come(AdcKADR());
        QThread::currentThread()->msleep(10);
    }
}

void useE154::onMixCh1(bool b)
{
    SetChannel(CH1, b);
}

void useE154::onMixCh2(bool b)
{
    SetChannel(CH2, b);
}

void useE154::onMixCh3(bool b)
{
    SetChannel(CH3, b);
}

void useE154::onMixCh4(bool b)
{
    SetChannel(CH4, b);
}

void useE154::onMixPP(bool b)
{
    SetChannel(PP, b);
}

void useE154::onLaser(bool b)
{
    SetChannel(L, b);
}

void useE154::stopThread()
{
    thread_stop = true;
    qDebug() << "Call stopThread(), thread id: " << QThread::currentThreadId();
}

int useE154::OpenDevice()
{
    char ModuleName[7];							// название модуля
    int i;
	// попробуем обнаружить модуль E-154 в первых 256 виртуальных слотах
    for(i = 0; i < MaxVirtualSoltsQuantity; i++) if(pModule->OpenLDevice(i)) break;
	// что-нибудь обнаружили?
    if(i == MaxVirtualSoltsQuantity) throw Errore_E154("Устройство E-154 не подключено к ПК!");

    if(!pModule->GetModuleName(ModuleName)) throw Errore_E154("Не удалось получить имя подключенного модуля!");

	// проверим, что это 'E-154'
    if(strcmp(ModuleName, "E154")) {
        throw Errore_E154("Модуль не E154!");
        return 1;
    }
    qDebug().noquote() << QString("Module E-154' is opened in virtual slot %1").arg(i).toLatin1();
    return 0;
}

void useE154::CloseDevice()
{
    pModule->CloseLDevice();
    qDebug() << "Module 'E-154' is closed";
}

QString useE154::GetUsbSpeed()
{
    BYTE UsbSpeed;								// скорость работы шины USB
    if(!pModule->GetUsbSpeed(&UsbSpeed)) qDebug().noquote() << QString("Не удалось получить скорость работы интерфейса USB!"); //получаем скорость работы шины USB
//    QString speed;
//    if(UsbSpeed)
//    {
//        speed = "High-Speed Mode (480 Mbit/s)";
//    } else speed = "Full-Speed Mode (12 Mbit/s)";
//    return QString("USB в режиме работы %1").arg(speed);
    return [](BYTE x){return x ? "High-Speed Mode (480 Mbit/s)" : "Full-Speed Mode (12 Mbit/s)";}(UsbSpeed);
}

QString useE154::GetInformation()
{
    char name[25], serial[16];
    if(!pModule->GET_MODULE_DESCRIPTION(&ModuleDescription)) qDebug().noquote() << QString("Не удалось получить дискриптор модуля!");
    strcpy(serial, (char*)ModuleDescription.Module.SerialNumber);
    strcpy(name, (char*)ModuleDescription.Module.DeviceName);
    // получим информацию из ППЗУ модуля
    return QString(tr("Подключен модуль %1 (S/N %2)\n%3\n%4")
                   .arg(name).arg(serial).arg(GetUsbSpeed()).arg(OnlyOneE154::Instance().GetVersion()));
}

void useE154::SetChannel(Channel ch, int pos)
{
    if(pos == ON) {
        switch(ch) {
            case CH1: { TtlOut |= (1<<0); pModule->TTL_OUT(TtlOut); break; }
            case CH2: { TtlOut |= (1<<1); pModule->TTL_OUT(TtlOut); break; }
            case CH3: { TtlOut |= (1<<2); pModule->TTL_OUT(TtlOut); break; }
            case CH4: { TtlOut |= (1<<3); pModule->TTL_OUT(TtlOut); break; }
            case  PP: { TtlOut |= (1<<4); pModule->TTL_OUT(TtlOut); break; }
            case   L: { TtlOut |= (1<<5); pModule->TTL_OUT(TtlOut); break; }
                default:    qDebug().noquote() << QString("Неправильно выбран TTL канал");
        }
    }
    else{
        switch(ch) {
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

bool useE154::GetStatusTD()
{
    pModule->TTL_IN(&TtlIN); if(TtlIN & (1<<0)) return TRUE; else return FALSE;
}

