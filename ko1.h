#ifndef KO1_H
#define KO1_H

#include <QWidget>

namespace Ui {
class Ko1;
}

class Ko1 : public QWidget
{
    Q_OBJECT

public:
    explicit Ko1(QWidget *parent = 0);
    ~Ko1();

private:
    Ui::Ko1 *ui;
};

#endif // KO1_H
