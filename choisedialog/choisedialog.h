#ifndef CHOISEDIALOG_H
#define CHOISEDIALOG_H

#include <QDialog>

//dialog include
#include "agr1.h"
#include "agr2.h"
#include "ko1.h"
#include "ko2.h"
#include "ko3.h"
#include "ko4.h"
#include "ko5.h"
#include "testkoagr.h"

class MainWindow;

namespace Ui {
class ChoiseDialog;
}

class ChoiseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChoiseDialog(QWidget *parent = 0);
    int getTypeOfWidget() const;

    ~ChoiseDialog();

private slots:
    virtual void accept() override;
    void on_agr1Button_clicked();
    void on_agr2Button_clicked();
    void on_ko1Button_clicked();
    void on_ko2Button_clicked();
    void on_ko3Button_clicked();
    void on_ko4Button_clicked();
    void on_ko5Button_clicked();
    void on_testButton_clicked();
    void calibration();

private:

    Ui::ChoiseDialog *ui;
    TestKoAgr *test;

    MainWindow *mw;
    Agr1 *agr1;
    Agr2 *agr2;
    Ko1 *ko1;
    Ko2 *ko2;
    Ko3 *ko3;
    Ko4 *ko4;
    Ko5 *ko5;
};

#endif // CHOISEDIALOG_H
