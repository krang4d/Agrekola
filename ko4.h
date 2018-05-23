#ifndef KO4_H
#define KO4_H

#include <QWidget>

namespace Ui {
class Ko4;
}

class Ko4 : public QWidget
{
    Q_OBJECT

public:
    explicit Ko4(QWidget *parent = 0);
    ~Ko4();

private:
    Ui::Ko4 *ui;
};

#endif // KO4_H
