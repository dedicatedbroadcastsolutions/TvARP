/********************************************************************************
** Form generated from reading UI file 'configure_eas.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGURE_EAS_H
#define UI_CONFIGURE_EAS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_configure_eas
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_19;
    QLabel *label_14;
    QLabel *label_13;
    QComboBox *comboBox;
    QLabel *label_11;
    QLabel *label_12;
    QComboBox *comboBox_3;
    QComboBox *comboBox_2;
    QSpinBox *spinBox_3;
    QLabel *label_5;
    QLabel *label_10;
    QLabel *label_6;
    QSpinBox *spinBox_5;
    QLabel *label_15;
    QLabel *label_7;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_3;
    QSpinBox *spinBox;
    QSpinBox *spinBox_4;
    QLabel *label_9;
    QSpinBox *spinBox_2;
    QLabel *label_8;
    QLabel *label_4;
    QSpinBox *spinBox_7;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_16;
    QComboBox *comboBox_4;
    QLabel *label_17;
    QSpinBox *spinBox_6;
    QLabel *label_18;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *configure_eas)
    {
        if (configure_eas->objectName().isEmpty())
            configure_eas->setObjectName(QStringLiteral("configure_eas"));
        configure_eas->resize(444, 300);
        verticalLayout = new QVBoxLayout(configure_eas);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(configure_eas);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_19 = new QLabel(groupBox);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout->addWidget(label_19, 5, 0, 1, 1);

        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout->addWidget(label_14, 3, 8, 1, 1);

        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout->addWidget(label_13, 3, 3, 1, 1);

        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout->addWidget(comboBox, 3, 2, 1, 1);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout->addWidget(label_11, 3, 0, 1, 1);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout->addWidget(label_12, 3, 4, 1, 1);

        comboBox_3 = new QComboBox(groupBox);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));

        gridLayout->addWidget(comboBox_3, 2, 6, 1, 3);

        comboBox_2 = new QComboBox(groupBox);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        gridLayout->addWidget(comboBox_2, 3, 5, 1, 3);

        spinBox_3 = new QSpinBox(groupBox);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setMaximum(19390);
        spinBox_3->setValue(692);

        gridLayout->addWidget(spinBox_3, 2, 2, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 2, 0, 1, 2);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 1, 7, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 2, 3, 1, 1);

        spinBox_5 = new QSpinBox(groupBox);
        spinBox_5->setObjectName(QStringLiteral("spinBox_5"));
        spinBox_5->setMinimum(32);
        spinBox_5->setMaximum(3840);
        spinBox_5->setValue(68);
        spinBox_5->setDisplayIntegerBase(16);

        gridLayout->addWidget(spinBox_5, 1, 5, 1, 2);

        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout->addWidget(label_15, 2, 4, 1, 2);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 0, 4, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 3, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 2);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 2);

        spinBox = new QSpinBox(groupBox);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMaximum(19000);
        spinBox->setValue(500);

        gridLayout->addWidget(spinBox, 0, 2, 1, 1);

        spinBox_4 = new QSpinBox(groupBox);
        spinBox_4->setObjectName(QStringLiteral("spinBox_4"));
        spinBox_4->setMinimum(16);
        spinBox_4->setMaximum(7936);
        spinBox_4->setValue(64);
        spinBox_4->setDisplayIntegerBase(16);

        gridLayout->addWidget(spinBox_4, 0, 5, 1, 2);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 0, 7, 1, 1);

        spinBox_2 = new QSpinBox(groupBox);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setMaximum(10000);
        spinBox_2->setValue(192);

        gridLayout->addWidget(spinBox_2, 1, 2, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 1, 4, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 3, 1, 1);

        spinBox_7 = new QSpinBox(groupBox);
        spinBox_7->setObjectName(QStringLiteral("spinBox_7"));
        spinBox_7->setMinimum(1024);
        spinBox_7->setMaximum(65535);
        spinBox_7->setValue(1234);

        gridLayout->addWidget(spinBox_7, 5, 2, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(configure_eas);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout_2->addWidget(label_16, 0, 0, 1, 1);

        comboBox_4 = new QComboBox(groupBox_2);
        comboBox_4->setObjectName(QStringLiteral("comboBox_4"));

        gridLayout_2->addWidget(comboBox_4, 0, 1, 1, 1);

        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout_2->addWidget(label_17, 0, 2, 1, 1);

        spinBox_6 = new QSpinBox(groupBox_2);
        spinBox_6->setObjectName(QStringLiteral("spinBox_6"));
        spinBox_6->setMinimum(1);

        gridLayout_2->addWidget(spinBox_6, 0, 3, 1, 1);

        label_18 = new QLabel(groupBox_2);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout_2->addWidget(label_18, 0, 4, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        buttonBox = new QDialogButtonBox(configure_eas);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(configure_eas);
        QObject::connect(buttonBox, SIGNAL(accepted()), configure_eas, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), configure_eas, SLOT(reject()));

        QMetaObject::connectSlotsByName(configure_eas);
    } // setupUi

    void retranslateUi(QDialog *configure_eas)
    {
        configure_eas->setWindowTitle(QApplication::translate("configure_eas", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("configure_eas", "Stream Settings", 0));
        label_19->setText(QApplication::translate("configure_eas", "Local Port", 0));
        label_14->setText(QApplication::translate("configure_eas", "pixels", 0));
        label_13->setText(QApplication::translate("configure_eas", "fps", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("configure_eas", "29.97", 0)
        );
        label_11->setText(QApplication::translate("configure_eas", "Frame Rate", 0));
        label_12->setText(QApplication::translate("configure_eas", "Resolution", 0));
        comboBox_3->clear();
        comboBox_3->insertItems(0, QStringList()
         << QApplication::translate("configure_eas", "mpeg2video", 0)
        );
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("configure_eas", "704x480", 0)
         << QApplication::translate("configure_eas", "1920x1080", 0)
        );
        label_5->setText(QApplication::translate("configure_eas", "Mux Bit Rate:", 0));
        label_10->setText(QApplication::translate("configure_eas", "hex", 0));
        label_6->setText(QApplication::translate("configure_eas", "kbps", 0));
        label_15->setText(QApplication::translate("configure_eas", "Video Compression", 0));
        label_7->setText(QApplication::translate("configure_eas", "PMT PID", 0));
        label_2->setText(QApplication::translate("configure_eas", "kbps", 0));
        label->setText(QApplication::translate("configure_eas", "Video Bit Rate:", 0));
        label_3->setText(QApplication::translate("configure_eas", "Audio Bit Rate:", 0));
        label_9->setText(QApplication::translate("configure_eas", "hex", 0));
        label_8->setText(QApplication::translate("configure_eas", "Video PID", 0));
        label_4->setText(QApplication::translate("configure_eas", "kbps", 0));
        groupBox_2->setTitle(QApplication::translate("configure_eas", "EAS Detection Settings", 0));
        label_16->setText(QApplication::translate("configure_eas", "Ring Detection Port", 0));
        comboBox_4->clear();
        comboBox_4->insertItems(0, QStringList()
         << QApplication::translate("configure_eas", "Com6", 0)
         << QApplication::translate("configure_eas", "Mux1", 0)
        );
        label_17->setText(QApplication::translate("configure_eas", "Ring check every:", 0));
        label_18->setText(QApplication::translate("configure_eas", "ms", 0));
    } // retranslateUi

};

namespace Ui {
    class configure_eas: public Ui_configure_eas {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGURE_EAS_H
