#ifndef SAVEFILES_H
#define SAVEFILES_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

class SaveFiles : public QObject
{
    Q_OBJECT
public:
    explicit SaveFiles(QObject *parent = 0);
    ~SaveFiles();
    QString writeData(QStringList);
    static QString openData(QWidget*, QList<double>&, QList<double>&, QList<double>&, QList<double>&, QList<double>&, QStringList&);
    void writeUserMsg(QString);

signals:

public slots:

protected:
    void setupFiles();
    QFile file_setting, file_user, file_data;
    QTextStream out_settings ,out_user, out_data;
};

#endif // SAVEFILES_H
