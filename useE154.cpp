//#include "StdAfx.h"
#include "useE154.h"

useE154::useE154(void) : AdcRate(100), InputRangeIndex(ADC_INPUT_RANGE_5000mV_E154)
{
    pLoadDll = new TLoadDll();
    if(!pLoadDll) throw Errore_E154("Ошибка загрузи библиотеки Dll Load_Dll()!");
	initAPIInstance();
	initModuleHandler();
	OpenDevice();
}

useE154::~useE154(void)
{
	ReleaseAPIInstance();
}
//typedef DWORD (WINAPI *pGetDllVersion)(void);
//typedef LPVOID (WINAPI *pCreateInstance)(char *);

void useE154::initAPIInstance()
{
    pCreateInstance CreateInstance = (pCreateInstance)pLoadDll->CallCreateLInstance();
    if(!CreateInstance) throw Errore_E154("Ошибка выделения памяти в функции SetAPIInstance()!");
    pModule = static_cast<ILE154 *>(CreateInstance("e154"));
    if(!pModule) throw Errore_E154("Ошибка выделения памяти для интерфейса CreateInstance(\"e154\")!");
}

void useE154::initModuleHandler()
{
    ModuleHandle = pModule->GetModuleHandle();
    if(ModuleHandle == INVALID_HANDLE_VALUE) Errore_E154("GetModuleHandle() --> Bad\n");
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
    if(pLoadDll) { delete pLoadDll; pLoadDll = NULL; }
    // если нужно - аварийно завершаем программу
    //if(AbortionFlag) exit(0x1);
}

string useE154::GetVertion(void)
{
	pGetDllVersion GetDllVersion = (pGetDllVersion)pLoadDll->CallGetDllVersion();
    if(!GetDllVersion) throw Errore_E154("Ошибка выделения памяти в функции Get_Version()!");
//sprintf(String, " Lusbapi.dll Version Error!!!\n   Current: %1u.%1u. Required: %1u.%1u",
//						DllVersion >> 0x10, DllVersion & 0xFFFF,
//						CURRENT_VERSION_LUSBAPI >> 0x10, CURRENT_VERSION_LUSBAPI & 0xFFFF);
	DllVersion = GetDllVersion();
    return "Lusbapi.dll v" + std::to_string(DllVersion >> 0x10) + "," + std::to_string(DllVersion & 0xFFFF) + "\r\n";
}

string useE154::OpenDevice()
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
    return "Устройство 'E-154' открыто в виртуальном слоте №" + std::to_string(i) + ".\n\r" ;
	//user_msg.Format(_T("%sУстройство 'E-154' обнаружено.\n\r"), user_msg);
}
	/*****************************************************/
string useE154::GetUsbSpeed()
{
    if(!pModule->GetUsbSpeed(&UsbSpeed)) Errore_E154("Не удалось получить скорость работы интерфейса USB!"); //получаем скорость работы шины USB
    string speed;
    if(UsbSpeed)
    {
        speed = "High-Speed Mode (480 Mbit/s)";
    } else speed = "Full-Speed Mode (12 Mbit/s)";
    return "USB is in " + speed + ".\n\r";
}

string useE154::GetUserMessages() const
{
    return user_msg.back();
}

// получим информацию из ППЗУ модуля
//if(!pModule->GET_MODULE_DESCRIPTION(&ModuleDescription)) Errore_E154("Не удалось получить дискриптор модуля!");
