#ifndef LOADEMODULE_H
#define LOADEMODULE_H

#include <string>
#include "LoadDll.h"
#include "lib/Lusbapi.h"

class LoadE154 : public LoadDll
{
public:
    LoadE154();
    virtual ~LoadE154();

    ILE154* GetAPI();
    std::string GetVersion();


protected:
    void IniAPI();
    void ReleaseAPI();
    void IniHandler();
    std::string OpenDevice();

private:
    HANDLE ModuleHandle;						// дескриптор устройства
    ILE154 *pModule;							// указатель на интерфейс модуля
    PCHAR mname;
};

#endif // LOADEMODULE_H
