#ifndef AGR1_H
#define AGR1_H

#include <QWidget>

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

signals:
    void measurement();

private:
    Ui::Agr1 *ui;
};

#endif // AGR1_H
