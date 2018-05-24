#ifndef KO5_H
#define KO5_H

#include <QWidget>

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
    void on_pushButton_clicked();

signals:
    void measurement();

private:
    Ui::Ko5 *ui;
};

#endif // KO5_H
