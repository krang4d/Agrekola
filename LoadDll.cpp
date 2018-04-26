#include "LoadDll.h"

class NoLibraryFileDllError{};
class CantLoadDllError{};
//------------------------------------------------------------------------
// коструктор
//------------------------------------------------------------------------
TLoadDll::TLoadDll() // PCHAR
{
#ifdef QT
    if(!QLibrary::isLibrary(name)) throw NoLibraryFileDllError();
    hDll = new QLibrary(name);
    hDll->load();
    if(!hDll->isLoaded()) {throw CantLoadDllError();}
#else
    name = "Lusbapi.dll";
    hDll = ::LoadLibrary(name.c_str());
#endif
}
//------------------------------------------------------------------------
// деструктор
//------------------------------------------------------------------------
TLoadDll::~TLoadDll()
{
#ifdef QT
    if(hDll->isLoaded()) hDll->unload();
    delete hDll;
#else
	::FreeLibrary(hDll);
#endif
}
//------------------------------------------------------------------------
// получение адреса функции возвращающей указатель на интерфейс модуля
//------------------------------------------------------------------------
LPVOID WINAPI TLoadDll::CallCreateLInstance(void)
{
   if(hDll == NULL) return NULL;
#ifdef QT
    return (LPVOID)hDll->resolve("CreateLInstance");
#else
	return FARPROC(::GetProcAddress(hDll, "CreateLInstance"));
#endif
}
//------------------------------------------------------------------------
// получение адреса функции возвращающей версию DLL
//------------------------------------------------------------------------
LPVOID WINAPI TLoadDll::CallGetDllVersion(void)
{
    if(hDll == NULL) return NULL;
#ifdef QT
    return (LPVOID)hDll->resolve("GetDllVersion");
#else
	return FARPROC(::GetProcAddress(hDll, "GetDllVersion"));
#endif
}
//------------------------------------------------------------------------
// получение идентификатора библиотеки
//------------------------------------------------------------------------
#ifdef QT
QLibrary* TLoadDll::GetDllHinstance(void)
{
    return hDll;
}
#else
HINSTANCE WINAPI TLoadDll::GetDllHinstance(void)
{
	return hDll;
}
#endif
