#include "useE154.h"

useE154::useE154(QWidget *parent) :
    QWidget(parent)
{
    pLoadDll = new TLoadDll();
    if(!pLoadDll) throw Errore_E154("Ошибка загрузи библиотеки Dll Load_Dll()!");
    initAPIInstance();
	initModuleHandler();
	OpenDevice();
    initPorts();
    initADC();
}

useE154::~useE154(void)
{
    CloseDevice();
    delete[] pDestination;
	ReleaseAPIInstance();
    if(pLoadDll) { delete pLoadDll; pLoadDll = NULL; }
}

 double useE154::AdcSample(channel ch)
{
    pModule->STOP_ADC();
    SHORT AdcSample;
    double AdcVolt;
    if(!pModule->ADC_SAMPLE(&AdcSample, (WORD)(ch  | (ADC_INPUT_RANGE_5000mV_E154 << 6)))) { throw Errore_E154("\n\n  ADC_SAMPLE(, 0) --> Bad\n");}
    if(!pModule->ProcessOnePoint(AdcSample, &AdcVolt, (WORD)(ch  | (ADC_INPUT_RANGE_5000mV_E154 << 6)), TRUE, TRUE)) { throw Errore_E154("\n\n  PreocessOnePoint() --> Bad\n"); }
    pModule->STOP_ADC();
    return AdcVolt;
}

QVector<double> useE154::AdcKADR()
{
    SHORT AdcBuffer[4];
    double volt[16];
    pModule->STOP_ADC();
    pModule->GET_MODULE_DESCRIPTION(&ModuleDescription);
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
    return vec_data;
//    emit ValueCome(&AdcSampleList);
}

std::string useE154::AdcSynchro()
{
    DoubleData Destination = AdcSynchroDouble();
    int Size = Destination.size;
    std::string readDataString;
    readDataString += "useE154::AdcSynchro() size:" + std::to_string(Size) + "\n";
    readDataString += "Sample[0]= " + std::to_string(Destination.data[0]) + "\n";
    readDataString += "Sample[" + std::to_string(Size-1) + "]" + std::to_string(Destination.data[Size-1]) + "\n";
    for(int i=0; i<Size; i++)
    {
        vec_data.append(Destination.data[i]);
        std::string str = std::to_string(vec_data[i]);
        readDataString += "№" + std::to_string(i) + "val:" + str + "\t";
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

    if(!pDestination) {delete pDestination; pDestination = NULL;}
    pDestination = new double[Size];
    DoubleData data(pDestination, Size);
    SHORT *AdcData = IoReq.Buffer;
    if(!pModule->ProcessArray(AdcData, pDestination, Size, TRUE, TRUE)) throw Errore_E154("Ошибка преобразования кода АЦП ProcessArray()\n");
    if(!ReadBuffer) {delete[] ReadBuffer; ReadBuffer = NULL;}
    return data;
}

//typedef LPVOID (WINAPI *pCreateInstance)(char *);
void useE154::initAPIInstance()
{
    char name[] = "e154";
    pCreateInstance CreateInstance = (pCreateInstance)pLoadDll->CallCreateLInstance();
    if(!CreateInstance) throw Errore_E154("Ошибка выделения памяти в функции SetAPIInstance()!");
    pModule = static_cast<ILE154 *>(CreateInstance(name));
    //pModule = static_cast<ILE154 *>(CreateInstance(const_cast<char*>("e154")));
    if(!pModule) throw Errore_E154("Ошибка выделения памяти для интерфейса CreateInstance(\"e154\")!");
}

void useE154::initModuleHandler()
{
    ModuleHandle = pModule->GetModuleHandle();
    if(ModuleHandle == INVALID_HANDLE_VALUE) Errore_E154("GetModuleHandle() --> Bad\n");
}

//typedef DWORD (WINAPI *pGetDllVersion)(void);
QString useE154::GetVersion(void)
{
    pGetDllVersion GetDllVersion = (pGetDllVersion)pLoadDll->CallGetDllVersion();
    if(!GetDllVersion) throw Errore_E154("Ошибка выделения памяти в функции Get_Version()!");
//sprintf(String, " Lusbapi.dll Version Error!!!\n   Current: %1u.%1u. Required: %1u.%1u",
//						DllVersion >> 0x10, DllVersion & 0xFFFF,
//						CURRENT_VERSION_LUSBAPI >> 0x10, CURRENT_VERSION_LUSBAPI & 0xFFFF);
    DWORD DllVersion = GetDllVersion();
    return QString("Lusbapi.dll version is v%1.%2").arg(DllVersion >> 0x10).arg(DllVersion & 0xFFFF);
}

void useE154::initPorts()
{
    if(pModule->ENABLE_TTL_OUT(1)) pModule->TTL_OUT(0); else throw Errore_E154("Ошибка включения линий TTL");
}

QString useE154::initADC()
{
    pModule->STOP_ADC();
    if(!pModule->GET_ADC_PARS(&ap)) throw Errore_E154("Ошибка получния параметров АЦП!\n");
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
    if(!pModule->SET_ADC_PARS(&ap)) throw Errore_E154("Ошибка установки параметрв АЦП!\n");

    return QString("initADC()");
}

void useE154::ReleaseAPIInstance() //(char *ErrorString, bool AbortionFlag)
{	// подчищаем интерфейс модуля
    if(pModule)
    {
        // освободим интерфейс модуля
        if(!pModule->ReleaseLInstance()) throw Errore_E154("Ошибка при освобождении интерфейса ReleaseLInstance()!");
        //else printf(" ReleaseLInstance() --> OK\n");
        // обнулим указатель на интерфейс модуля
        pModule = NULL;
    }
    // освободим библиотеку
    //if(pLoadDll) { delete pLoadDll; pLoadDll = NULL; }
    // если нужно - аварийно завершаем программу
    //if(AbortionFlag) exit(0x1);
}

void useE154::OpenDevice()
{
	WORD i;
	// попробуем обнаружить модуль E-154 в первых 256 виртуальных слотах
	for(i = 0x0; i < MaxVirtualSoltsQuantity; i++) if(pModule->OpenLDevice(i)) break;
	// что-нибудь обнаружили?
    if(i == MaxVirtualSoltsQuantity) throw Errore_E154("Ненайдено ни одного устройства E-154!"); //AbortProgram(" Can't find any module E-154 in first 127 virtual slots!\n");
																									//else printf(" OpenLDevice(%u) --> OK\n", i);
	// прочитаем название модуля в обнаруженном виртуальном слоте
    if(!pModule->GetModuleName(ModuleName)) Errore_E154("Не удалось получить название подключенного модуля!");

	// проверим, что это 'E-154'
    if(strcmp(ModuleName, "E154")) Errore_E154("Устройство 'E-154' успешно открыто.");
    //return "Устройство 'E-154' открыто в виртуальном слоте №" + std::to_string(i) + ".\n\r" ;
}

void useE154::CloseDevice()
{
    pModule->CloseLDevice();
}

QString useE154::GetUsbSpeed()
{
    if(!pModule->GetUsbSpeed(&UsbSpeed)) Errore_E154("Не удалось получить скорость работы интерфейса USB!"); //получаем скорость работы шины USB
    QString speed;
    if(UsbSpeed)
    {
        speed = "High-Speed Mode (480 Mbit/s)";
    } else speed = "Full-Speed Mode (12 Mbit/s)";
    return QString("USB is in %1").arg(speed);
}

QString useE154::GetInformation()
{
    //string str;
    char name[25], serial[16];
    if(!pModule->GET_MODULE_DESCRIPTION(&ModuleDescription)) throw Errore_E154("Не удалось получить дискриптор модуля!");
    strcpy(serial, (char*)ModuleDescription.Module.SerialNumber);
    // получим информацию из ППЗУ модуля
    return QString("Модуль E-154 (S/N %1 готов").arg(serial);
}

void useE154::SetChannel(channel ch, int pos)
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

bool useE154::GetStatusTD()
{
    pModule->TTL_IN(&TtlIN); if(TtlIN & (1<<0)) return TRUE; else return FALSE;
}

