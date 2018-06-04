#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cw = new Widget;
    ch = new ChoiseDialog;
    m = new Measurement;
    vg = new ViewGraph(this);
    setCentralWidget(m);
}

MainWindow::~MainWindow()
{
    delete vg;
    delete ui;
}
