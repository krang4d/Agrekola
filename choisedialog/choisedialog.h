#ifndef CHOISEDIALOG_H
#define CHOISEDIALOG_H

#include <QDialog>
#include <QTimer>

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
#include "mainwindow.h"
#include "useE154.h"
#include "viewplot.h"
#include "globalvalue.h"

class MainWindow;
typedef QMetaObject::Connection MetaObj;

namespace Ui {
class ChoiseDialog;
}

class ChoiseDialog : public QDialog
{
    Q_OBJECT
    Ui::ChoiseDialog *ui;
public:
    explicit ChoiseDialog(QDialog *parent = 0);
    int getTypeOfWidget() const;
    void CreateWidgetThread();
    void DeleteWidgetThread();
    ~ChoiseDialog();

    Agr1 *agr1;     //Определение параметров агрегации
    Agr2 *agr2;     //Определение активности фактора Виллебранда
    Ko1 *ko1;       //Время свертывания
    Ko2 *ko2;       //АЧТВ
    Ko3 *ko3;       //Фибриноген
    Ko4 *ko4;       //Тромбин
    Ko5 *ko5;       //Протромбиновый комплекс

    QMessageBox *end_dialog;
    QPrintDialog *printDialog;
    useE154 *agrekola;
    Widget *widget;

private slots:
    void on_exitButton_clicked();
    void on_testButton_clicked();

    void on_agr1Button_clicked();
    void on_agr2Button_clicked();
    void on_ko1Button_clicked();
    void on_ko2Button_clicked();
    void on_ko3Button_clicked();
    void on_ko4Button_clicked();
    void on_ko5Button_clicked();
    //void on_viewPlotsButton_clicked();

    void t_singeShotConntection(MetaObj *p, MetaObj *t1,MetaObj *t2, MetaObj *t3, MetaObj *t4, Ko_impl *ko);
    void c_singeShotConntection(MetaObj *p, MetaObj *t1, MetaObj *t2, MetaObj *t3, MetaObj *t4, Ko_impl *ko);
    void btp_singeShotConntection(MetaObj *btp1, MetaObj *btp2, MetaObj *btp3, MetaObj *btp4, Agr_impl *agr);
    void otp_singeShotConntection(MetaObj *otp1, MetaObj *otp2, MetaObj *otp3, MetaObj *otp4, Agr_impl *agr);

    void startMeasurement(StartMeasurement *);
    void calibration(StartMeasurement *);
};

#endif // CHOISEDIALOG_H
