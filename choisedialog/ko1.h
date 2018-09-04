#ifndef KO1_H
#define KO1_H

#include <QWidget>
#include "savefiles.h"
#include "startmeasurment.h"

namespace Ui {
class Ko1;
}

class Ko1 : public QWidget
{
    Q_OBJECT

public:
    explicit Ko1(QWidget *parent = 0);
    ~Ko1();

private slots:

signals:
    void measurement(StartMeasurment*);

private:
    Ui::Ko1 *ui;
    SaveFiles file;
    QStringList param;
    StartMeasurment *startPar;
};

#endif // KO1_H
