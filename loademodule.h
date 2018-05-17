#ifndef LOADEMODULE_H
#define LOADEMODULE_H

#include <string>
#include "LoadDll.h"
#include "Lusbapi.h"

class LoadEModule : public TLoadDll
{
public:
    LoadEModule();
    virtual ~LoadEModule();
    ILE154* GetEModuleAPI();
    std::string GetVersion();

protected:
    void InitAPIInstance();
    //void InitModuleHandler();
    void ReleaseAPIInstance();
    std::string OpenDevice();

private:
    PCHAR ModuleName = "e154";
    ILE154 *pModule;							// указатель на интерфейс модуля
};

#endif // LOADEMODULE_H
