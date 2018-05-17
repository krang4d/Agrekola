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
    //if(!pModule->GetModuleName(mname)) throw LoadE154_Error{};

    // проверим, что это 'E-154'b
    //if(strcmp(mname, "E154")) throw LoadE154_Error{};
    return "Устройство 'E-154' открыто в виртуальном слоте №" + std::to_string(i) + ".\n\r" ;
    //user_msg.Format(_T("%sУстройство 'E-154' обнаружено.\n\r"), user_msg);
}
