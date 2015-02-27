/********************************************************************************
** Form generated from reading UI file 'pcr_analyser_mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PCR_ANALYSER_MAINWINDOW_H
#define UI_PCR_ANALYSER_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PCR_Analyser_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QPushButton *Process;
    QLabel *label;
    QLineEdit *source;
    QLabel *label_2;
    QLineEdit *output;
    QListWidget *listWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PCR_Analyser_MainWindow)
    {
        if (PCR_Analyser_MainWindow->objectName().isEmpty())
            PCR_Analyser_MainWindow->setObjectName(QStringLiteral("PCR_Analyser_MainWindow"));
        PCR_Analyser_MainWindow->resize(793, 517);
        centralWidget = new QWidget(PCR_Analyser_MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMaximumSize(QSize(150, 16777215));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        Process = new QPushButton(groupBox);
        Process->setObjectName(QStringLiteral("Process"));

        verticalLayout->addWidget(Process);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        source = new QLineEdit(groupBox);
        source->setObjectName(QStringLiteral("source"));

        verticalLayout->addWidget(source);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setEnabled(false);

        verticalLayout->addWidget(label_2);

        output = new QLineEdit(groupBox);
        output->setObjectName(QStringLiteral("output"));
        output->setEnabled(false);

        verticalLayout->addWidget(output);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        gridLayout->addWidget(listWidget, 0, 1, 1, 1);

        PCR_Analyser_MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PCR_Analyser_MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 793, 18));
        PCR_Analyser_MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PCR_Analyser_MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        PCR_Analyser_MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PCR_Analyser_MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        PCR_Analyser_MainWindow->setStatusBar(statusBar);

        retranslateUi(PCR_Analyser_MainWindow);

        QMetaObject::connectSlotsByName(PCR_Analyser_MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PCR_Analyser_MainWindow)
    {
        PCR_Analyser_MainWindow->setWindowTitle(QApplication::translate("PCR_Analyser_MainWindow", "PCR_Analyser_MainWindow", 0));
        groupBox->setTitle(QApplication::translate("PCR_Analyser_MainWindow", "GroupBox", 0));
        Process->setText(QApplication::translate("PCR_Analyser_MainWindow", "Process", 0));
        label->setText(QApplication::translate("PCR_Analyser_MainWindow", "Source File", 0));
        source->setText(QApplication::translate("PCR_Analyser_MainWindow", "C:\\Users\\Zach\\Development\\build-ffmpeg-Desktop_Qt_5_3_MinGW_32bit-Debug\\encode_test.ts", 0));
        label_2->setText(QApplication::translate("PCR_Analyser_MainWindow", "Output File", 0));
        output->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PCR_Analyser_MainWindow: public Ui_PCR_Analyser_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PCR_ANALYSER_MAINWINDOW_H
