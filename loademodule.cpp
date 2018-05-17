#include "loademodule.h"

#define MaxVirtualSoltsQuantity 127

class LoadE154_Error{};

LoadE154::LoadE154()
{
    IniAPI();
    OpenDevice();
}

LoadE154::~LoadE154()
{
    ReleaseAPI();
}

ILE154 *LoadE154::GetAPI()
{
    return pModule;
}

void LoadE154::IniAPI()
{
    pCreateInstance CreateInstance = (pCreateInstance)CallCreateLInstance();
    if(!CreateInstance) throw LoadE154_Error{};
    pModule = static_cast<ILE154 *>(CreateInstance("e154"));
    if(!pModule) throw LoadE154_Error{};
}

void LoadE154::ReleaseAPI() //(char *ErrorString, bool AbortionFlag)
{	// подчищаем интерфейс модуля
    if(pModule)
    {
        // освободим интерфейс модуля
        if(!pModule->ReleaseLInstance()) throw LoadE154_Error{};
        //else printf(" ReleaseLInstance() --> OK\n");
        // обнулим указатель на интерфейс модуля
        pModule = NULL;
    }
}

std::string LoadE154::GetVersion(void)
{
    pGetDllVersion GetDllVersion = (pGetDllVersion)CallGetDllVersion();
    if(!GetDllVersion) throw LoadE154_Error{};
//sprintf(String, " Lusbapi.dll Version Error!!!\n   Current: %1u.%1u. Required: %1u.%1u",
//						DllVersion >> 0x10, DllVersion & 0xFFFF,
//						CURRENT_VERSION_LUSBAPI >> 0x10, CURRENT_VERSION_LUSBAPI & 0xFFFF);
    DWORD DllVersion = GetDllVersion();
    return "Lusbapi.dll version is v" + std::to_string(DllVersion >> 0x10) + "." + std::to_string(DllVersion & 0xFFFF) + "\n";
}

std::string LoadE154::OpenDevice()
{
    WORD i;
    // попробуем обнаружить модуль E-154 в первых 256 виртуальных слотах
    for(i = 0x0; i < MaxVirtualSoltsQuantity; i++) if(pModule->OpenLDevice(i)) break;
    // что-нибудь обнаружили?
    if(i == MaxVirtualSoltsQuantity) throw LoadE154_Error{}; //AbortProgram(" Can't find any module E-154 in first 127 virtual slots!\n");
                                                                                                    //else printf(" OpenLDevice(%u) --> OK\n", i);
    // прочитаем название модуля в обнаруженном виртуальном слоте
    mname = new char[8];
    if(!pModule->GetModuleName(mname)) throw LoadE154_Error{};
    delete[] mname;
    // проверим, что это 'E-154'b
    if(strcmp(mname, "E154")) throw LoadE154_Error{};
    return "Устройство 'E-154' открыто в виртуальном слоте №" + std::to_string(i) + ".\n\r" ;
    //user_msg.Format(_T("%sУстройство 'E-154' обнаружено.\n\r"), user_msg);
}

std::string LoadE154::GetUsbSpeed()
{
    if(!pModule->GetUsbSpeed(&UsbSpeed)) LoadE154_Error{};//Errore_E154("Не удалось получить скорость работы интерфейса USB!"); //получаем скорость работы шины USB
    std::string speed;
    if(UsbSpeed)
    {
        speed = "High-Speed Mode (480 Mbit/s)";
    } else speed = "Full-Speed Mode (12 Mbit/s)";
    return "USB is in " + speed + ".\n\r";
}

std::string LoadE154::GetInformation()
{
    std::string str;
    int *bs = new int[16];
    bs =  (int*)ModuleDescription.Module.SerialNumber;
     // получим информацию из ППЗУ модуля
    if(!pModule->GET_MODULE_DESCRIPTION(&ModuleDescription)) LoadE154_Error{};//Errore_E154("Не удалось получить дискриптор модуля!");
    // отобразим параметры модуля на экране монитора
/*    str = " \r\n\r\n" + " Module E-154 (S/N " + std::to_string(ModuleDescription.Module.SerialNumber) + ") is ready ... \r\n" +
                 " Module Info:\n" +
                 " Module  Revision   is " + std::to_string(ModuleDescription.Module.Revision) + " \r\n" +
                 " AVR Driver Version is " + std::to_string(ModuleDescription.Mcu.Version.Version) +
                 "(" + std::to_string(ModuleDescription.Mcu.Version.Date) + ")"\+ "\r\n" +
                 "   Adc parameters:\r\n" +
  */             "     Input Range  = " + std::to_string(ADC_INPUT_RANGES_E154[ADC_INPUT_RANGE_5000mV_E154]) + "Volt\r\n";
    str = "     Input Range  = " + std::to_string(ADC_INPUT_RANGES_E154[ADC_INPUT_RANGE_5000mV_E154]) + "Volt\r\n" +
          " \r\n\r\n" + " Module E-154 (S/N " + (char)ModuleDescription.Module.SerialNumber[0] + ") is ready ... \r\n";
    return str;
}
