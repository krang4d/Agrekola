//---------------------------------------------------------------------------
#ifndef __LoadDllH
#define __LoadDllH
//---------------------------------------------------------------------------
#define QT

#include <windows.h>
#include <winioctl.h>
#include <string>
    #ifdef QT
        #include <QLibrary>
    #endif
typedef DWORD (WINAPI *pGetDllVersion)(void);
typedef LPVOID (WINAPI *pCreateInstance)(PCHAR const);
class TLoadDll
{
	public:
		// коструктор
        TLoadDll();
		// деструктор
		~TLoadDll();
		// получение адреса функции интерфейса модуля
		LPVOID WINAPI CallCreateLInstance(void);
		// получение адреса функции версии DLL
		LPVOID WINAPI CallGetDllVersion(void);
		// получение идентификатора библиотеки
#ifdef QT
        QLibrary* GetDllHinstance(void);
#else
		HINSTANCE WINAPI GetDllHinstance(void);
#endif
	private:
		// идентификатор модуля DLL
    #ifdef QT
            QLibrary *hDll;
            const char *name = "Lusbapi.dll";
    #else
            HINSTANCE hDll;
            std::string name;
    #endif
};
#endif
