#ifndef SAVEFILES_H
#define SAVEFILES_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

#include <QDateTime>
#include <QDebug>
#include <QFileDialog>
#include <QRegExp>
#include <QStringList>
#include <progresstimerbar.h>

class SaveFiles : public QObject
{
    Q_OBJECT
public:
    explicit SaveFiles(QObject *parent = 0);
    ~SaveFiles();
    static QString writeData(QStringList, ProgressTimerBar *bar = NULL);
    static QString openData(QWidget*, QList<double>&, QList<double>&, QList<double>&, QList<double>&, QList<double>&, QStringList&);
    void writeUserMsg(QString);

    void openAgr1(QStringList &param);
    void openAgr2(QStringList &param);
    void openKo1(QStringList &param);
    void openKo2(QStringList &param);
    void openKo3(QStringList &param);
    void openKo4(QStringList &param);
    void openKo5(QStringList &param);
    void openStartWin(QStringList &param);

    void saveAgr1(QStringList param);
    void saveAgr2(QStringList param);
    void saveKo1(QStringList param);
    void saveKo2(QStringList param);
    void saveKo3(QStringList param);
    void saveKo4(QStringList param);
    void saveKo5(QStringList param);
    void saveStartWin(QStringList param);

signals:

public slots:

protected:
    void setupFiles();
    void openParams(QString name, QStringList &param);
    void saveParams(QString name, QStringList param);
    QFile file_setting;
    QTextStream stream_setting;
    QDir dataDir, settingDir;
};

class OnlyOneFile
{
public:
    QFile file_user, file_data;
    QTextStream stream_user, stream_data;
    static OnlyOneFile& Instance()
    {
            static OnlyOneFile theSingleInstance;
            return theSingleInstance;
    }

private:
    OnlyOneFile() {
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
        file_user.setFileName("user.txt");
        if(!file_user.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text))
                qDebug() << "user file is't opened";
        stream_user.setDevice(&file_user);
    }
    OnlyOneFile(const OnlyOneFile& root) = delete;
    OnlyOneFile& operator=(const OnlyOneFile&) = delete;
};

#endif // SAVEFILES_H
