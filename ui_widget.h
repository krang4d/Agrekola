/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <chartdir/realtimedemo.h>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QPushButton *AdcSample;
    QPushButton *AdcKadr;
    QPushButton *AdcSynchro;
    RealtimeDemo *plotRt;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(1027, 567);
        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 1011, 411));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        textEdit = new QTextEdit(layoutWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(14);
        textEdit->setFont(font);
        textEdit->setReadOnly(true);

        verticalLayout->addWidget(textEdit);

        AdcSample = new QPushButton(layoutWidget);
        AdcSample->setObjectName(QStringLiteral("AdcSample"));

        verticalLayout->addWidget(AdcSample);

        AdcKadr = new QPushButton(layoutWidget);
        AdcKadr->setObjectName(QStringLiteral("AdcKadr"));

        verticalLayout->addWidget(AdcKadr);

        AdcSynchro = new QPushButton(layoutWidget);
        AdcSynchro->setObjectName(QStringLiteral("AdcSynchro"));

        verticalLayout->addWidget(AdcSynchro);

        plotRt = new RealtimeDemo(Widget);
        plotRt->setObjectName(QStringLiteral("plotRt"));
        plotRt->setGeometry(QRect(19, 429, 991, 121));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        AdcSample->setText(QApplication::translate("Widget", "AdcSample", Q_NULLPTR));
        AdcKadr->setText(QApplication::translate("Widget", "AdcKadr", Q_NULLPTR));
        AdcSynchro->setText(QApplication::translate("Widget", "AdcSynchro", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
