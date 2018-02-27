#include "widget.h"
#include <QApplication>
#include <QLibrary>
#include "windows.h"
#include <DLL\Include\Lusbapi.h>

//// идентификатор файла
//HANDLE hFile;
//DWORD FileBytesWritten;

// версия библиотеки
DWORD DllVersion;
// указатель на интерфейс модуля
ILE154 *pModule;
// дескриптор устройства
HANDLE ModuleHandle;
// название модуля
char ModuleName[7];
// скорость работы шины USB
BYTE UsbSpeed;
// структура с полной информацией о модуле
MODULE_DESCRIPTION_E154 ModuleDescription;
// структура параметров работы АЦП модуля
ADC_PARS_E154 ap;
// структура с параметрами запроса на ввод/вывод данных
IO_REQUEST_LUSBAPI IoReq;

// кол-во получаемых отсчетов
DWORD DataStep = 256*1024;
// буфер данных
SHORT *ReadBuffer;

//QLibrary LCardLib("Lusbapi");
typedef DWORD WINAPI (*GetVer)();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget *w = new Widget();
    w->show();
    w->setText("Module E-154\n");
    w->setText("Console example for ADC Synchro Stream \n");
    //GetVer myGetDllVersion = (GetVer)LCardLib.resolve("GetDllVersion");
    GetVer myGetDllVersion = (GetVer)QLibrary::resolve("LUSBAPI", "GetDllVersion");
    if(!myGetDllVersion)
    {
        w->setText("Lusbapi.dll Version --> OK\n");
    }
    else w->setText("Lusbapi.dll Version Error!!!\n");

    if((DllVersion = myGetDllVersion()) != CURRENT_VERSION_LUSBAPI)
    {
         w->setText("Lusbapi.dll Version Error!!!\n");
    }
    else w->setText(" Lusbapi.dll Version --> OK\n");
    return a.exec();
}
