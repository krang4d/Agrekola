#ifndef KO2_H
#define KO2_H

#include <QWidget>
#include "savefiles.h"
#include "startmeasurment.h"

namespace Ui {
class Ko2;
}

class Ko2 : public QWidget
{
    Q_OBJECT

public:
    explicit Ko2(QWidget *parent = 0);
    ~Ko2();

private slots:
    void on_calibr1Button_clicked();

signals:
    void measurement(StartMeasurment*);
    void calibration();

public slots:
    void calibration_data_come(double);

private:
    Ui::Ko2 *ui;
    SaveFiles file;
    QStringList param;
};

#endif // KO2_H
