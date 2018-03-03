#ifndef E154_H
#define E154_H

#include "windows.h"
#include <QLibrary>
#include <string.h>

typedef DWORD (WINAPI *pGetDllVersion)(void);
typedef LPVOID (WINAPI *pCreateInstance)(char *);

class E154
{
public:
    E154();
    ~E154();

    // получение адреса функции интерфейса модуля
    LPVOID WINAPI CallCreateLInstance(void);
    // получение адреса функции версии DLL
    LPVOID WINAPI CallGetDllVersion(void);
    // получение идентификатора библиотеки
    HINSTANCE WINAPI GetDllHinstance(void);

private:
    // идентификатор модуля DLL
    //HINSTANCE hDLL
    std::string name;
    QLibrary *hDll;
};

#endif // E154_H
