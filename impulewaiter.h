#ifndef IMPULEWAITER_H
#define IMPULEWAITER_H

#include <QWidget>
#include <QDialog>
#include <QTimer>

namespace Ui {
class ImpuleWaiter;
}

class ImpuleWaiter : public QDialog
{
    Q_OBJECT

public:
    explicit ImpuleWaiter(QWidget *parent = 0);
    void startWait();
    void addWaiter(int n);
    ~ImpuleWaiter();

private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void loopslot();

public slots:
    void has_pulse_1();
    void has_pulse_2();
    void has_pulse_3();
    void has_pulse_4();


signals:
    press_1();
    press_2();
    press_3();
    press_4();
    alldone();

private:
    Ui::ImpuleWaiter *ui;
    QTimer loop;
    int count;
};

#endif // IMPULEWAITER_H
