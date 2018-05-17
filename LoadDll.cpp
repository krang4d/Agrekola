#include "LoadDll.h"

class NoLibraryFileDllError{};
class CantLoadDllError{};
//------------------------------------------------------------------------
// коструктор
//------------------------------------------------------------------------
LoadDll::LoadDll() // PCHAR
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
LoadDll::~LoadDll()
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
LPVOID WINAPI LoadDll::CallCreateLInstance(void)
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
LPVOID WINAPI LoadDll::CallGetDllVersion(void)
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
QLibrary* LoadDll::GetDllHinstance(void)
{
    return hDll;
}
#else
HINSTANCE WINAPI LoadDll::GetDllHinstance(void)
{
	return hDll;
}
#endif
