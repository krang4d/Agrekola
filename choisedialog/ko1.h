#ifndef KO1_H
#define KO1_H

#include <QWidget>
#include "savefiles.h"

namespace Ui {
class Ko1;
}

class Ko1 : public QWidget
{
    Q_OBJECT

public:
    explicit Ko1(QWidget *parent = 0);
    ~Ko1();

private slots:
    void on_startButton_clicked();

signals:
    void measurement();

private:
    Ui::Ko1 *ui;
    QStringList param;
};

#endif // KO1_H
