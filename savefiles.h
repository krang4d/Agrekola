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

class SaveFiles : public QObject
{
    Q_OBJECT
public:
    explicit SaveFiles(QObject *parent = 0);
    ~SaveFiles();
    QString writeData(QStringList);
    static QString openData(QWidget*, QList<double>&, QList<double>&, QList<double>&, QList<double>&, QList<double>&, QStringList&);
    void writeUserMsg(QString);

    void openAgr1(QStringList &param);
    void openAgr2(QStringList &param);
    void openKo1(QStringList &param);
    void openKo2(QStringList &param);
    void openKo3(QStringList &param);
    void openKo4(QStringList &param);
    void openKo5(QStringList &param);

    void saveAgr1(QStringList param);
    void saveAgr2(QStringList param);
    void saveKo1(QStringList param);
    void saveKo2(QStringList param);
    void saveKo3(QStringList param);
    void saveKo4(QStringList param);
    void saveKo5(QStringList param);

signals:

public slots:

protected:
    void setupFiles();
    void openParams(QString name, QStringList &param);
    void saveParams(QString name, QStringList param);
    QFile file_setting, file_user, file_data;
    QTextStream stream_settings ,stream_user, stream_data;
    QDir dataDir, settingDir, userDir;
};

#endif // SAVEFILES_H
