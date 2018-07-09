#ifndef CHOISEDIALOG_H
#define CHOISEDIALOG_H

#include <QDialog>
#include <QThread>

//dialog include
#include "agr1.h"
#include "agr2.h"
#include "ko1.h"
#include "ko2.h"
#include "ko3.h"
#include "ko4.h"
#include "ko5.h"
#include "testkoagr.h"
#include "widget.h"
#include "useE154.h"

class MainWindow;

namespace Ui {
class ChoiseDialog;
}

class ChoiseDialog : public QDialog
{
    Q_OBJECT
    QThread workerThread;

public:
    explicit ChoiseDialog(useE154 *a, QDialog *parent = 0);
    int getTypeOfWidget() const;

    ~ChoiseDialog();

private slots:
    virtual void accept();
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
    useE154 *agrekola;
    Widget *test;
    MainWindow *mw;
    Agr1 *agr1; //Определение параметров агрегации
    Agr2 *agr2; //Определение активности фактора Виллебранда
    Ko1 *ko1;   //Время свертывания
    Ko2 *ko2;   //АЧТВ
    Ko3 *ko3;   //Фибриноген
    Ko4 *ko4;   //Тромбин
    Ko5 *ko5;   //Протромбиновый комплекс
};

#endif // CHOISEDIALOG_H
