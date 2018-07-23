#ifndef KO3_H
#define KO3_H

#include <QWidget>
#include "savefiles.h"

namespace Ui {
class Ko3;
}

class Ko3 : public QWidget
{
    Q_OBJECT

public:
    explicit Ko3(QWidget *parent = 0);
    ~Ko3();

private slots:
    void on_startButton_clicked();
    void on_calibr1Button_clicked();

signals:
    void measurement();
    void calibration();

private:
    Ui::Ko3 *ui;
    SaveFiles file;
    QStringList param;
};

#endif // KO3_H
