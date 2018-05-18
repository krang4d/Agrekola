#ifndef LOADEMODULE_H
#define LOADEMODULE_H

#include <string>
#include "LoadDll.h"
#include "lib/Lusbapi.h"

struct Errore_E154
{
    std::string err_msg;
    Errore_E154(const std::string &m) : err_msg(m) {}
};

class LoadE154 : public LoadDll
{
public:
    LoadE154();
    virtual ~LoadE154();

    ILE154* GetAPI();
    std::string GetVersion();
    std::string GetUsbSpeed();
    std::string GetInformation();

protected:
    void IniAPI();
    void ReleaseAPI();
    void IniHandler();
    std::string OpenDevice();

private:
    HANDLE ModuleHandle;						// дескриптор устройства
    ILE154 *pModule;							// указатель на интерфейс модуля
    BYTE UsbSpeed;								// скорость работы шины USB
    PCHAR mname;
    MODULE_DESCRIPTION_E154 ModuleDescription;	// структура с полной информацией о модуле
};

#endif // LOADEMODULE_H
