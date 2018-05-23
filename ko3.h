#ifndef KO3_H
#define KO3_H

#include <QWidget>

namespace Ui {
class Ko3;
}

class Ko3 : public QWidget
{
    Q_OBJECT

public:
    explicit Ko3(QWidget *parent = 0);
    ~Ko3();

private:
    Ui::Ko3 *ui;
};

#endif // KO3_H
