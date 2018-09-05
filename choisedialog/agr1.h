#ifndef AGR1_H
#define AGR1_H

#include <QWidget>
#include <QStringList>
#include "startmeasurment.h"

#include "savefiles.h"

namespace Ui {
class Agr1;
}

class Agr1 : public QWidget
{
    Q_OBJECT

public:
    explicit Agr1(QWidget *parent = 0);
    ~Agr1();

private slots:
    void on_startButton_clicked();
    void on_kolibrButton_clicked();

signals:
    void measurement(StartMeasurment*);
    void calibration();

private:
    Ui::Agr1 *ui;
    SaveFiles file;
    QStringList param;
};

#endif // AGR1_H
