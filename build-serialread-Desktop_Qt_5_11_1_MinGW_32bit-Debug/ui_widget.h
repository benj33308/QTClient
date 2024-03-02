/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "../../qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QCustomPlot *customPlot;
    QLabel *label;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_7;
    QPlainTextEdit *PNNftpt;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_8;
    QPlainTextEdit *SDNNpt;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_9;
    QPlainTextEdit *RMSSDpt;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QPlainTextEdit *featurePT;
    QWidget *layoutWidget4;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_5;
    QPlainTextEdit *NN50pt;
    QWidget *layoutWidget5;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_6;
    QPlainTextEdit *HRVpt;
    QWidget *layoutWidget6;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QComboBox *serialCB;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_3;
    QPushButton *startbt;
    QPushButton *stopbt;
    QPushButton *clearbt;
    QPushButton *savebt;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QPlainTextEdit *serialportPT;
    QPushButton *clear_temp_bt;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(1245, 680);
        customPlot = new QCustomPlot(Widget);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        customPlot->setGeometry(QRect(90, 40, 991, 341));
        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(92, 12, 136, 16));
        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(1110, 340, 91, 111));
        verticalLayout_4 = new QVBoxLayout(layoutWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout_4->addWidget(label_7);

        PNNftpt = new QPlainTextEdit(layoutWidget);
        PNNftpt->setObjectName(QStringLiteral("PNNftpt"));
        PNNftpt->setReadOnly(true);

        verticalLayout_4->addWidget(PNNftpt);

        layoutWidget1 = new QWidget(Widget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(1110, 450, 91, 111));
        verticalLayout_5 = new QVBoxLayout(layoutWidget1);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(layoutWidget1);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout_5->addWidget(label_8);

        SDNNpt = new QPlainTextEdit(layoutWidget1);
        SDNNpt->setObjectName(QStringLiteral("SDNNpt"));
        SDNNpt->setReadOnly(true);

        verticalLayout_5->addWidget(SDNNpt);

        layoutWidget2 = new QWidget(Widget);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(1110, 560, 91, 111));
        verticalLayout_6 = new QVBoxLayout(layoutWidget2);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(layoutWidget2);
        label_9->setObjectName(QStringLiteral("label_9"));

        verticalLayout_6->addWidget(label_9);

        RMSSDpt = new QPlainTextEdit(layoutWidget2);
        RMSSDpt->setObjectName(QStringLiteral("RMSSDpt"));
        RMSSDpt->setReadOnly(true);

        verticalLayout_6->addWidget(RMSSDpt);

        layoutWidget3 = new QWidget(Widget);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(1110, 10, 91, 111));
        verticalLayout_2 = new QVBoxLayout(layoutWidget3);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget3);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_2->addWidget(label_3);

        featurePT = new QPlainTextEdit(layoutWidget3);
        featurePT->setObjectName(QStringLiteral("featurePT"));
        featurePT->setReadOnly(true);

        verticalLayout_2->addWidget(featurePT);

        layoutWidget4 = new QWidget(Widget);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(1110, 120, 91, 111));
        verticalLayout_7 = new QVBoxLayout(layoutWidget4);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget4);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_7->addWidget(label_5);

        NN50pt = new QPlainTextEdit(layoutWidget4);
        NN50pt->setObjectName(QStringLiteral("NN50pt"));
        NN50pt->setReadOnly(true);

        verticalLayout_7->addWidget(NN50pt);

        layoutWidget5 = new QWidget(Widget);
        layoutWidget5->setObjectName(QStringLiteral("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(1110, 230, 91, 111));
        verticalLayout_8 = new QVBoxLayout(layoutWidget5);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget5);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_8->addWidget(label_6);

        HRVpt = new QPlainTextEdit(layoutWidget5);
        HRVpt->setObjectName(QStringLiteral("HRVpt"));
        HRVpt->setReadOnly(true);

        verticalLayout_8->addWidget(HRVpt);

        layoutWidget6 = new QWidget(Widget);
        layoutWidget6->setObjectName(QStringLiteral("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(90, 410, 545, 218));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget6);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        serialCB = new QComboBox(layoutWidget6);
        serialCB->setObjectName(QStringLiteral("serialCB"));

        horizontalLayout->addWidget(serialCB);

        label_2 = new QLabel(layoutWidget6);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);


        horizontalLayout_2->addLayout(horizontalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        startbt = new QPushButton(layoutWidget6);
        startbt->setObjectName(QStringLiteral("startbt"));

        verticalLayout_3->addWidget(startbt);

        stopbt = new QPushButton(layoutWidget6);
        stopbt->setObjectName(QStringLiteral("stopbt"));

        verticalLayout_3->addWidget(stopbt);

        clearbt = new QPushButton(layoutWidget6);
        clearbt->setObjectName(QStringLiteral("clearbt"));

        verticalLayout_3->addWidget(clearbt);

        savebt = new QPushButton(layoutWidget6);
        savebt->setObjectName(QStringLiteral("savebt"));

        verticalLayout_3->addWidget(savebt);


        horizontalLayout_2->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_4 = new QLabel(layoutWidget6);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        serialportPT = new QPlainTextEdit(layoutWidget6);
        serialportPT->setObjectName(QStringLiteral("serialportPT"));

        verticalLayout->addWidget(serialportPT);


        horizontalLayout_2->addLayout(verticalLayout);

        clear_temp_bt = new QPushButton(Widget);
        clear_temp_bt->setObjectName(QStringLiteral("clear_temp_bt"));
        clear_temp_bt->setGeometry(QRect(740, 510, 93, 28));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        label->setText(QApplication::translate("Widget", "Electrocardiogram", nullptr));
        label_7->setText(QApplication::translate("Widget", "PNN50", nullptr));
        label_8->setText(QApplication::translate("Widget", "SDNN", nullptr));
        label_9->setText(QApplication::translate("Widget", "RMSSD", nullptr));
        label_3->setText(QApplication::translate("Widget", "HeartRate", nullptr));
        label_5->setText(QApplication::translate("Widget", "NN50", nullptr));
        label_6->setText(QApplication::translate("Widget", "HRV", nullptr));
        label_2->setText(QApplication::translate("Widget", "Serialport", nullptr));
        startbt->setText(QApplication::translate("Widget", "Start", nullptr));
        stopbt->setText(QApplication::translate("Widget", "Stop", nullptr));
        clearbt->setText(QApplication::translate("Widget", "Clear", nullptr));
        savebt->setText(QApplication::translate("Widget", "Datasave", nullptr));
        label_4->setText(QApplication::translate("Widget", "Serialreceive", nullptr));
        clear_temp_bt->setText(QApplication::translate("Widget", "Clear temp", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
