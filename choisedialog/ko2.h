#ifndef KO2_H
#define KO2_H

#include <QWidget>

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
    void on_startButton_clicked();
    void on_calibr1Button_clicked();
    void on_calibr2Button_clicked();

signals:
    void measurement();
    void calibration();

private:
    Ui::Ko2 *ui;
};

#endif // KO2_H
