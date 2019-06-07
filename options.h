#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>
#include <QCloseEvent>
#include "itools.h"

namespace Ui {
class Options;
}

class Options : public QDialog
{
    Q_OBJECT

public:
    explicit Options(ITools *, QDialog *parent = nullptr);
    ~Options();

private slots:
    void on_pushButton_Next_clicked();

private:
    Ui::Options *ui;
    ITools *widget;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // OPTIONS_H
