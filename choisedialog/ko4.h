#ifndef KO4_H
#define KO4_H

#include <QWidget>
#include "savefiles.h"

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

signals:
    void measurement();
    void calibration();

private:
    Ui::Ko4 *ui;
    QStringList param;
};

#endif // KO4_H
