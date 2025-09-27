/********************************************************************************
** Form generated from reading UI file 'polinom_builder.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POLINOM_BUILDER_H
#define UI_POLINOM_BUILDER_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include "mylineedit.h"
#include "plot.h"

QT_BEGIN_NAMESPACE

class Ui_Polinom_builder
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QLabel *label_7;
    QLabel *label_4;
    QGridLayout *gridLayout;
    QLabel *label;
    MyLineEdit *lineEditX;
    QLabel *label_2;
    MyLineEdit *lineEditY;
    QLabel *label_8;
    QComboBox *comboBox;
    QLabel *label_6;
    QLineEdit *lineEdit;
    QPushButton *resultButton;
    QPushButton *plotGraph;
    QPushButton *clearButton;
    QPushButton *saveButton;
    QPushButton *loadButton;
    QPushButton *polinomButton;
    Plot *plot;
    QChartView *chartView;
    QLabel *label_5;
    QTableWidget *tableWidget;
    QPushButton *applyButton;
    QPushButton *closeButton;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Polinom_builder)
    {
        if (Polinom_builder->objectName().isEmpty())
            Polinom_builder->setObjectName("Polinom_builder");
        Polinom_builder->resize(1753, 818);
        centralwidget = new QWidget(Polinom_builder);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");

        gridLayout_2->addWidget(label_7, 0, 1, 1, 1);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        gridLayout_2->addWidget(label_4, 0, 2, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEditX = new MyLineEdit(centralwidget);
        lineEditX->setObjectName("lineEditX");

        gridLayout->addWidget(lineEditX, 0, 1, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEditY = new MyLineEdit(centralwidget);
        lineEditY->setObjectName("lineEditY");

        gridLayout->addWidget(lineEditY, 1, 1, 1, 1);

        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");

        gridLayout->addWidget(label_8, 2, 0, 1, 1);

        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName("comboBox");

        gridLayout->addWidget(comboBox, 2, 1, 1, 1);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);
        label_6->setMinimumSize(QSize(200, 0));

        gridLayout->addWidget(label_6, 3, 0, 1, 1);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");

        gridLayout->addWidget(lineEdit, 3, 1, 1, 1);

        resultButton = new QPushButton(centralwidget);
        resultButton->setObjectName("resultButton");

        gridLayout->addWidget(resultButton, 4, 1, 1, 1);

        plotGraph = new QPushButton(centralwidget);
        plotGraph->setObjectName("plotGraph");

        gridLayout->addWidget(plotGraph, 5, 1, 1, 1);

        clearButton = new QPushButton(centralwidget);
        clearButton->setObjectName("clearButton");

        gridLayout->addWidget(clearButton, 6, 1, 1, 1);

        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName("saveButton");

        gridLayout->addWidget(saveButton, 7, 1, 1, 1);

        loadButton = new QPushButton(centralwidget);
        loadButton->setObjectName("loadButton");

        gridLayout->addWidget(loadButton, 8, 1, 1, 1);

        polinomButton = new QPushButton(centralwidget);
        polinomButton->setObjectName("polinomButton");

        gridLayout->addWidget(polinomButton, 9, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);

        plot = new Plot(centralwidget);
        plot->setObjectName("plot");
        plot->setMinimumSize(QSize(700, 0));

        gridLayout_2->addWidget(plot, 1, 1, 3, 1);

        chartView = new QChartView(centralwidget);
        chartView->setObjectName("chartView");
        chartView->setMinimumSize(QSize(400, 0));

        gridLayout_2->addWidget(chartView, 1, 2, 3, 3);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);
        label_5->setMinimumSize(QSize(0, 100));
        label_5->setMaximumSize(QSize(16777215, 100));
        label_5->setWordWrap(true);

        gridLayout_2->addWidget(label_5, 2, 0, 1, 1);

        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName("tableWidget");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(tableWidget, 3, 0, 1, 1);

        applyButton = new QPushButton(centralwidget);
        applyButton->setObjectName("applyButton");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(applyButton->sizePolicy().hasHeightForWidth());
        applyButton->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(applyButton, 4, 3, 1, 1);

        closeButton = new QPushButton(centralwidget);
        closeButton->setObjectName("closeButton");
        sizePolicy3.setHeightForWidth(closeButton->sizePolicy().hasHeightForWidth());
        closeButton->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(closeButton, 4, 4, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 4, 2, 1, 1);

        Polinom_builder->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Polinom_builder);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1753, 30));
        Polinom_builder->setMenuBar(menubar);
        statusbar = new QStatusBar(Polinom_builder);
        statusbar->setObjectName("statusbar");
        statusbar->setEnabled(false);
        Polinom_builder->setStatusBar(statusbar);

        retranslateUi(Polinom_builder);

        QMetaObject::connectSlotsByName(Polinom_builder);
    } // setupUi

    void retranslateUi(QMainWindow *Polinom_builder)
    {
        Polinom_builder->setWindowTitle(QCoreApplication::translate("Polinom_builder", "Polinom_builder", nullptr));
        label_3->setText(QCoreApplication::translate("Polinom_builder", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700;\">\320\230\321\201\321\205\320\276\320\264\320\275\321\213\320\265 \320\264\320\260\320\275\320\275\321\213\320\265</span></p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("Polinom_builder", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700;\">\320\220\320\277\321\200\320\276\320\272\321\201\320\270\320\274\320\270\321\200\320\276\320\262\320\260\320\275\320\275\321\213\320\271 \320\263\321\200\320\260\321\204\320\270\320\272</span></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("Polinom_builder", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700;\">\320\237\320\276\320\273\321\203\321\207\320\265\320\275\320\275\321\213\320\271 \320\263\321\200\320\260\321\204\320\270\320\272</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("Polinom_builder", "\320\222\321\200\320\265\320\274\321\217", nullptr));
        label_2->setText(QCoreApplication::translate("Polinom_builder", "\320\243\321\200\320\276\320\262\320\265\320\275\321\214", nullptr));
        label_8->setText(QCoreApplication::translate("Polinom_builder", "\320\222\321\213\320\261\320\276\321\200 \320\262\320\262\320\276\320\264\320\260 \321\201\321\202\320\265\320\277\320\265\320\275\320\270 \320\260\320\277\320\277\321\200\320\276\320\272\321\201\320\270\320\274\320\260\321\206\320\270\320\270", nullptr));
        label_6->setText(QCoreApplication::translate("Polinom_builder", "\320\241\321\202\320\265\320\277\320\265\320\275\321\214 \320\260\320\277\320\277\321\200\320\276\320\272\321\201\320\270\320\274\320\260\321\206\320\270\320\270", nullptr));
        lineEdit->setText(QCoreApplication::translate("Polinom_builder", "2", nullptr));
        resultButton->setText(QCoreApplication::translate("Polinom_builder", "\320\240\320\260\321\201\321\207\320\265\321\202 \320\272\320\276\321\215\321\204\321\204\320\270\321\206\320\270\320\265\320\275\321\202\320\276\320\262", nullptr));
        plotGraph->setText(QCoreApplication::translate("Polinom_builder", "\320\237\320\276\321\201\321\202\321\200\320\276\320\270\321\202\321\214 \320\263\321\200\320\260\321\204\320\270\320\272", nullptr));
        clearButton->setText(QCoreApplication::translate("Polinom_builder", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\263\321\200\320\260\321\204\320\270\320\272", nullptr));
        saveButton->setText(QCoreApplication::translate("Polinom_builder", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\263\321\200\320\260\321\204\320\270\320\272", nullptr));
        loadButton->setText(QCoreApplication::translate("Polinom_builder", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\263\321\200\320\260\321\204\320\270\320\272", nullptr));
        polinomButton->setText(QCoreApplication::translate("Polinom_builder", "\320\220\320\277\321\200\320\276\320\272\321\201\320\270\320\274\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\263\321\200\320\260\321\204\320\270\320\272", nullptr));
        label_5->setText(QCoreApplication::translate("Polinom_builder", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700;\">\320\240\320\260\321\201\321\201\321\207\320\270\321\202\320\260\320\275\320\275\321\213\320\265 \320\272\320\276\321\215\321\204\321\204\320\270\321\206\320\270\320\265\320\275\321\202\321\213<br>\320\260\320\277\320\277\321\200\320\276\320\272\321\201\320\270\320\274\320\260\321\206\320\270\320\270</span></p></body></html>", nullptr));
        applyButton->setText(QCoreApplication::translate("Polinom_builder", "\320\236\320\272", nullptr));
        closeButton->setText(QCoreApplication::translate("Polinom_builder", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Polinom_builder: public Ui_Polinom_builder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POLINOM_BUILDER_H
