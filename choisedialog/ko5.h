#ifndef KO5_H
#define KO5_H

#include <QWidget>
#include "savefiles.h"
#include "startmeasurment.h"

namespace Ui {
class Ko5;
}

class Ko5 : public QWidget
{
    Q_OBJECT

public:
    explicit Ko5(QWidget *parent = 0);
    ~Ko5();

private slots:
    void on_startButton_clicked();
    void on_calibr1Button_clicked();

signals:
    void measurement(StartMeasurment*);
    void calibration();

private:
    Ui::Ko5 *ui;
    SaveFiles file;
    QStringList param;
};

#endif // KO5_H
