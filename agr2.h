#ifndef AGR2_H
#define AGR2_H

#include <QWidget>

namespace Ui {
class Agr2;
}

class Agr2 : public QWidget
{
    Q_OBJECT

public:
    explicit Agr2(QWidget *parent = 0);
    ~Agr2();

private slots:
    void on_pushButton_clicked();

signals:
    void measurement();

private:
    Ui::Agr2 *ui;
};

#endif // AGR2_H
