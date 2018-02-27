#include "e154.h"

//typedef DWORD WINAPI (*GetVer)();

class Error{};

E154::E154()
{
    hDll = new QLibrary(name);
    if(!hDll->isLoaded()) {throw Error();}
}

LPVOID E154::CallCreateLInstance()
{
    if(hDll == NULL) return NULL;
    return (LPVOID)hDll->resolve("CreateLInstance");
}

LPVOID E154::CallGetDllVersion()
{
    if(hDll == NULL) return NULL;
    return (LPVOID)hDll->resolve("GetDllVersion");
}

HINSTANCE E154::GetDllHinstance()
{
    return (HINSTANCE)hDll;
}
