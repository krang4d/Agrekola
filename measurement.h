#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <QWidget>
#include <QTimer>
#include <QString>
#include <QDateTime>
#include <QList>
#include <QListView>

namespace Ui {
class Measurement;
}

class Measurement : public QWidget
{
    Q_OBJECT

public:
    explicit Measurement(QWidget *parent = 0);
    ~Measurement();
    void setUserMessage(QString);

public slots:
    void updatetime();
    void getData();

private:
    Ui::Measurement *ui;
    QTimer *timer;
    QDateTime dt;
    QList<QString> list_usrmsg;
};

#endif // MEASUREMENT_H
