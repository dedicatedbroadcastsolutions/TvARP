/********************************************************************************
** Form generated from reading UI file 'ingest_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INGEST_DIALOG_H
#define UI_INGEST_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *fromLineEdit;
    QPushButton *fileOpenButton;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *toLineEdit;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *startButton;
    QSpacerItem *horizontalSpacer_2;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout_7;
    QLabel *transcodingStatusLabel;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *playInputButton;
    QPushButton *playOutputButton;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(720, 406);
        gridLayout = new QGridLayout(Dialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(Dialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        fromLineEdit = new QLineEdit(Dialog);
        fromLineEdit->setObjectName(QStringLiteral("fromLineEdit"));

        horizontalLayout->addWidget(fromLineEdit);


        horizontalLayout_4->addLayout(horizontalLayout);

        fileOpenButton = new QPushButton(Dialog);
        fileOpenButton->setObjectName(QStringLiteral("fileOpenButton"));

        horizontalLayout_4->addWidget(fileOpenButton);


        gridLayout->addLayout(horizontalLayout_4, 0, 0, 1, 2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        toLineEdit = new QLineEdit(Dialog);
        toLineEdit->setObjectName(QStringLiteral("toLineEdit"));

        horizontalLayout_2->addWidget(toLineEdit);


        horizontalLayout_5->addLayout(horizontalLayout_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout_5, 1, 0, 1, 2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        startButton = new QPushButton(Dialog);
        startButton->setObjectName(QStringLiteral("startButton"));

        horizontalLayout_6->addWidget(startButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout_6, 2, 0, 1, 1);

        textEdit = new QTextEdit(Dialog);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        gridLayout->addWidget(textEdit, 3, 0, 1, 2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        transcodingStatusLabel = new QLabel(Dialog);
        transcodingStatusLabel->setObjectName(QStringLiteral("transcodingStatusLabel"));

        horizontalLayout_7->addWidget(transcodingStatusLabel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout_7, 4, 0, 1, 2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        playInputButton = new QPushButton(Dialog);
        playInputButton->setObjectName(QStringLiteral("playInputButton"));

        horizontalLayout_3->addWidget(playInputButton);

        playOutputButton = new QPushButton(Dialog);
        playOutputButton->setObjectName(QStringLiteral("playOutputButton"));

        horizontalLayout_3->addWidget(playOutputButton);


        gridLayout->addLayout(horizontalLayout_3, 5, 0, 1, 2);

        horizontalSpacer_4 = new QSpacerItem(298, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 6, 0, 1, 1);

        pushButton = new QPushButton(Dialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 6, 1, 1, 1);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(fromLineEdit);
        label_2->setBuddy(toLineEdit);
#endif // QT_NO_SHORTCUT

        retranslateUi(Dialog);
        QObject::connect(pushButton, SIGNAL(clicked()), Dialog, SLOT(close()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        label->setText(QApplication::translate("Dialog", "From:", 0));
        fromLineEdit->setText(QApplication::translate("Dialog", "Video/ew050812-004403SD-h264lb.mov", 0));
        fileOpenButton->setText(QApplication::translate("Dialog", "Browse...", 0));
        label_2->setText(QApplication::translate("Dialog", "To:", 0));
        toLineEdit->setText(QApplication::translate("Dialog", "Video/encode_test.ts", 0));
        startButton->setText(QApplication::translate("Dialog", "Convert", 0));
        transcodingStatusLabel->setText(QApplication::translate("Dialog", "Transcoding Status:", 0));
        playInputButton->setText(QApplication::translate("Dialog", "Play Input", 0));
        playOutputButton->setText(QApplication::translate("Dialog", "Play Output", 0));
        pushButton->setText(QApplication::translate("Dialog", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INGEST_DIALOG_H
