#ifndef KALIBRAGR2_H
#define KALIBRAGR2_H

#include <QWidget>

namespace Ui {
class KalibrAgr2;
}

class KalibrAgr2 : public QWidget
{
    Q_OBJECT

public:
    explicit KalibrAgr2(QWidget *parent = 0);
    ~KalibrAgr2();

private:
    Ui::KalibrAgr2 *ui;

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // KALIBRAGR2_H
