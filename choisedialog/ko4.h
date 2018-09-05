#ifndef KO4_H
#define KO4_H

#include <QWidget>
#include "savefiles.h"
#include "startmeasurment.h"

namespace Ui {
class Ko4;
}

class Ko4 : public QWidget
{
    Q_OBJECT

public:
    explicit Ko4(QWidget *parent = 0);
    ~Ko4();

private slots:
    void on_startButton_clicked();
    void on_calibr1Button_clicked();

public slots:
    void calibration_data_come(double);

signals:
    void measurement(StartMeasurment*);
    void calibration();

private:
    Ui::Ko4 *ui;
    SaveFiles file;
    QStringList param;
};

#endif // KO4_H
