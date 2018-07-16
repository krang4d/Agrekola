#include "savefiles.h"
#include <QDateTime>
#include <QDebug>

SaveFiles::SaveFiles(QObject *parent) : QObject(parent)
{
    setupFiles();
}

SaveFiles::~SaveFiles()
{
    file_setting.flush();
    file_setting.close();
    file_user.flush();
    file_user.close();
}

QString SaveFiles::writeData(QStringList dt)
{
    //создаем файл данных
    //имя файла формируется из текущей даты + число запуска программы в этот день
    QDateTime d = QDateTime::currentDateTime();
    static int i(0);
    for(;;)
    {
        QString name = QString("%1_%2.txt").arg(d.toString("yyyyMMdd")).arg(i);
        if(!QFile::exists(name)){
            file_data.setFileName(name);
            if(!file_data.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)) qWarning() << "data file is't opened";
            out_data.setDevice(&file_data);
            break;
        }
        i++;
    }
    foreach (QString var, dt) {
        out_data << var;
    }

    QString str = QString("Данные записаны в файл %1/%2").arg(QDir::currentPath()).arg(file_data.fileName());
    out_data.flush();
    file_data.close();
    return str;
}

void SaveFiles::writeUserMsg(QString msg)
{
    out_user << msg << "\n";
}

void SaveFiles::setupFiles()
{
    QDir dir;
    QString path = QDir::homePath();
    dir.cd(path); //переходим в папку home
    if(!dir.cd("Agrekola4k"))
    {
        if(dir.mkdir("Agrekola4k")) dir.cd("Agrekola4k");
        QDir::setCurrent(dir.path());
        qDebug() << "mkdir(Agrekola4k)";
    }
    else QDir::setCurrent(dir.path());
    //открываем файл сообщений
    file_user.setFileName("user.txt");
    if(!file_user.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)) qWarning() << "user file is't opened";
    out_user.setDevice(&file_user);

    if(!dir.cd("settings"))
    {
        if(dir.mkdir("settings")) dir.cd("settings");
        QDir::setCurrent(dir.path());
        qDebug() << "mkdir(settings)";
    }
    else QDir::setCurrent(dir.path());
    //открываем файл настроек
    file_setting.setFileName("setting.txt");
    if(!file_setting.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)) qWarning() << "setting file is't opened";
    out_settings.setDevice(&file_setting);

    if(!dir.cd("../data"))
    {
        if(dir.mkdir("../data")) dir.cd("../data");
        QDir::setCurrent(dir.path());
        qDebug() << "mkdir(data)";
    }
    else QDir::setCurrent(dir.path());
}
