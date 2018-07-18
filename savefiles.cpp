#include "savefiles.h"
#include <QDateTime>
#include <QDebug>
#include <QFileDialog>
#include <QRegExp>

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

QString SaveFiles::openData(QWidget *parent, QList<double> &v1, QList<double> &v2, QList<double> &v3, QList<double> &v4, QList<double> &t, QStringList &param)
{   
    //очищаем контейнеры
    v1.clear();
    v2.clear();
    v3.clear();
    v4.clear();
    t.clear();
    param.clear();
    //запускаем диалог и открыаем нужный файл
    QDir dir;
    dir.cd(QDir::homePath());
    dir.cd("Agrekola4k/data");
    QString fileName = QFileDialog::getOpenFileName(parent , tr("Выберите файл с данными"), dir.path(), tr("Text files (*.txt)"));
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "data file is't opened";
        return "";
    }
    //инициализируем регулярных выражения
    const QString v1pattern("(V1#[0-9]{1,8})");
    const QString v2pattern("(V2#[0-9]{1,8})");
    const QString v3pattern("(V3#[0-9]{1,8})");
    const QString v4pattern("(V4#[0-9]{1,8})");
    const QString tpattern("(t#[0-9]{1,8})");
    const QString tipattern("(ti#[0-9]{1,8})");
    const QString ppattern("(p#[0-9]{1,8})");
    const QString datapattern("(^[0-9]{1,})\\t(-?[0-9]\\.[0-9]{2,})\\t(-?[0-9]\\.[0-9]{2,})\\t(-?[0-9]\\.[0-9]{2,})\\t(-?[0-9]\\.[0-9]{2,})\\t([0-9]{1,}\\.?[0-9]{0,3})");
    QRegExp rx;
    rx.setPatternSyntax(QRegExp::RegExp);
    //считываем параметры с помощью регулярных выражений
    QString firstline = file.readLine();

    rx.setPattern(v1pattern);
    rx.indexIn(firstline);
    param << rx.cap(1);

    rx.setPattern(v2pattern);
    rx.indexIn(firstline);
    param << rx.cap(1);

    rx.setPattern(v3pattern);
    rx.indexIn(firstline);
    param << rx.cap(1);

    rx.setPattern(v4pattern);
    rx.indexIn(firstline);
    param << rx.cap(1);

    rx.setPattern(tpattern);
    rx.indexIn(firstline);
    param << rx.cap(1);

    rx.setPattern(tipattern);
    rx.indexIn(firstline);
    param << rx.cap(1);

    rx.setPattern(ppattern);
    rx.indexIn(firstline);
    param << rx.cap(1);

    //считываем строки и получаем с помощью регулярного выражения все значения
    rx.setPattern(datapattern);
    //int i = 0;
    while(!file.atEnd())
    {
        //qDebug() << "pos" << file.pos();
        QString line = file.readLine();
        rx.indexIn(line);
        //qDebug() << line;
        //if(i==0)  {i++; continue;}
        v1.push_back(rx.cap(2).toDouble());
        v2.push_back(rx.cap(3).toDouble());
        v3.push_back(rx.cap(4).toDouble());
        v4.push_back(rx.cap(5).toDouble());
        t.push_back(rx.cap(6).toDouble());
    }
    double t1 = t.first();
    for(int i = 0; i < t.size(); ++i) {
        t[i] -= t1;
    }
    qDebug() << fileName;
    file.close();
    return fileName;
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
