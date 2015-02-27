/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *Select_Com_Port;
    QAction *actionExit;
    QAction *actionLive_Controls;
    QAction *actionStart_Minimized;
    QAction *actionSchedule_Program;
    QAction *actionConfigure_EAS_Settings;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QSpinBox *crossbar_pin;
    QLabel *label_5;
    QComboBox *eas_audio_device;
    QPushButton *test_eas;
    QPushButton *config_eas;
    QComboBox *eas_video_device;
    QPushButton *restart_eas;
    QPushButton *get_input_devices;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label_4;
    QSpinBox *eas_stream_port;
    QLineEdit *eas_stream_address;
    QComboBox *eas_comport;
    QLabel *label_18;
    QRadioButton *crossbar_enable;
    QRadioButton *show_vmon;
    QRadioButton *stream_file;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_7;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget;
    QLabel *label_20;
    QTextBrowser *eas_detect;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QTextBrowser *encoder_display;
    QLabel *label;
    QLabel *label_7;
    QLabel *label_6;
    QTextEdit *mux_log_display;
    QTextBrowser *stream_status_display;
    QWidget *tab_3;
    QGridLayout *gridLayout_9;
    QTextEdit *mux_log_display_2;
    QLabel *label_19;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_7;
    QLabel *label_14;
    QLabel *label_15;
    QComboBox *mux_out_port;
    QLineEdit *mux_ctrl_addr;
    QSpinBox *mux_ctrl_port;
    QLabel *label_13;
    QLabel *label_12;
    QLabel *label_16;
    QComboBox *mux_debug_comport;
    QPushButton *update_mux_settings;
    QPushButton *restore_mux_defaults;
    QPushButton *set_mux_defaults;
    QRadioButton *mux_advanced;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_10;
    QRadioButton *ch1;
    QRadioButton *ch2;
    QRadioButton *ch3;
    QRadioButton *ch4;
    QRadioButton *ch5;
    QRadioButton *ch6;
    QRadioButton *ch7;
    QRadioButton *ch8;
    QPushButton *send_eas_config;
    QPushButton *revert_eas_config;
    QComboBox *comboBox;
    QPushButton *ad_insert;
    QPushButton *ad_return_to_network;
    QWidget *tab_5;
    QFormLayout *formLayout;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_6;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton_2;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QSpinBox *spinBox_2;
    QLineEdit *lineEdit_2;
    QLabel *label_8;
    QSpinBox *spinBox_3;
    QWidget *tab_6;
    QGridLayout *gridLayout_8;
    QLabel *label_17;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QMenu *menuFil;
    QMenu *menuSettings;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(980, 494);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/run.svg"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        Select_Com_Port = new QAction(MainWindow);
        Select_Com_Port->setObjectName(QStringLiteral("Select_Com_Port"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionLive_Controls = new QAction(MainWindow);
        actionLive_Controls->setObjectName(QStringLiteral("actionLive_Controls"));
        actionLive_Controls->setEnabled(false);
        actionStart_Minimized = new QAction(MainWindow);
        actionStart_Minimized->setObjectName(QStringLiteral("actionStart_Minimized"));
        actionStart_Minimized->setCheckable(true);
        actionStart_Minimized->setShortcutContext(Qt::WindowShortcut);
        actionSchedule_Program = new QAction(MainWindow);
        actionSchedule_Program->setObjectName(QStringLiteral("actionSchedule_Program"));
        actionSchedule_Program->setEnabled(false);
        actionConfigure_EAS_Settings = new QAction(MainWindow);
        actionConfigure_EAS_Settings->setObjectName(QStringLiteral("actionConfigure_EAS_Settings"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideNone);
        tabWidget->setDocumentMode(false);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_4 = new QGridLayout(tab_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        crossbar_pin = new QSpinBox(groupBox);
        crossbar_pin->setObjectName(QStringLiteral("crossbar_pin"));
        crossbar_pin->setValue(1);

        gridLayout_3->addWidget(crossbar_pin, 1, 6, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_3->addWidget(label_5, 0, 4, 1, 1);

        eas_audio_device = new QComboBox(groupBox);
        eas_audio_device->setObjectName(QStringLiteral("eas_audio_device"));
        eas_audio_device->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(eas_audio_device->sizePolicy().hasHeightForWidth());
        eas_audio_device->setSizePolicy(sizePolicy);
        eas_audio_device->setMinimumSize(QSize(0, 0));
        eas_audio_device->setEditable(true);

        gridLayout_3->addWidget(eas_audio_device, 1, 4, 1, 1);

        test_eas = new QPushButton(groupBox);
        test_eas->setObjectName(QStringLiteral("test_eas"));
        test_eas->setEnabled(true);
        test_eas->setCheckable(true);

        gridLayout_3->addWidget(test_eas, 0, 8, 1, 1);

        config_eas = new QPushButton(groupBox);
        config_eas->setObjectName(QStringLiteral("config_eas"));
        config_eas->setEnabled(false);

        gridLayout_3->addWidget(config_eas, 1, 7, 1, 1);

        eas_video_device = new QComboBox(groupBox);
        eas_video_device->setObjectName(QStringLiteral("eas_video_device"));
        eas_video_device->setEnabled(true);
        sizePolicy.setHeightForWidth(eas_video_device->sizePolicy().hasHeightForWidth());
        eas_video_device->setSizePolicy(sizePolicy);
        eas_video_device->setMinimumSize(QSize(0, 0));
        eas_video_device->setEditable(true);

        gridLayout_3->addWidget(eas_video_device, 1, 3, 1, 1);

        restart_eas = new QPushButton(groupBox);
        restart_eas->setObjectName(QStringLiteral("restart_eas"));
        restart_eas->setEnabled(true);

        gridLayout_3->addWidget(restart_eas, 1, 8, 1, 1);

        get_input_devices = new QPushButton(groupBox);
        get_input_devices->setObjectName(QStringLiteral("get_input_devices"));
        get_input_devices->setEnabled(false);

        gridLayout_3->addWidget(get_input_devices, 0, 7, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_3->addWidget(label_3, 0, 2, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_3->addWidget(label_2, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_3->addWidget(label_4, 0, 3, 1, 1);

        eas_stream_port = new QSpinBox(groupBox);
        eas_stream_port->setObjectName(QStringLiteral("eas_stream_port"));
        eas_stream_port->setEnabled(true);
        eas_stream_port->setMaximumSize(QSize(75, 16777215));
        eas_stream_port->setMinimum(1024);
        eas_stream_port->setMaximum(49151);
        eas_stream_port->setValue(1234);

        gridLayout_3->addWidget(eas_stream_port, 1, 2, 1, 1);

        eas_stream_address = new QLineEdit(groupBox);
        eas_stream_address->setObjectName(QStringLiteral("eas_stream_address"));
        eas_stream_address->setEnabled(true);
        eas_stream_address->setMinimumSize(QSize(100, 0));
        eas_stream_address->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_3->addWidget(eas_stream_address, 1, 1, 1, 1);

        eas_comport = new QComboBox(groupBox);
        eas_comport->setObjectName(QStringLiteral("eas_comport"));
        eas_comport->setEditable(true);

        gridLayout_3->addWidget(eas_comport, 1, 0, 1, 1);

        label_18 = new QLabel(groupBox);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout_3->addWidget(label_18, 0, 0, 1, 1);

        crossbar_enable = new QRadioButton(groupBox);
        crossbar_enable->setObjectName(QStringLiteral("crossbar_enable"));
        crossbar_enable->setEnabled(true);
        crossbar_enable->setChecked(true);
        crossbar_enable->setAutoExclusive(false);

        gridLayout_3->addWidget(crossbar_enable, 1, 5, 1, 1);

        show_vmon = new QRadioButton(groupBox);
        show_vmon->setObjectName(QStringLiteral("show_vmon"));
        show_vmon->setAutoExclusive(false);

        gridLayout_3->addWidget(show_vmon, 0, 5, 1, 1);

        stream_file = new QRadioButton(groupBox);
        stream_file->setObjectName(QStringLiteral("stream_file"));
        stream_file->setChecked(true);
        stream_file->setAutoExclusive(false);

        gridLayout_3->addWidget(stream_file, 0, 6, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox_3 = new QGroupBox(tab_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(250, 0));
        groupBox_3->setMaximumSize(QSize(176, 16777215));
        verticalLayout = new QVBoxLayout(groupBox_3);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox_7 = new QGroupBox(groupBox_3);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_7->sizePolicy().hasHeightForWidth());
        groupBox_7->setSizePolicy(sizePolicy1);
        groupBox_7->setMinimumSize(QSize(0, 0));
        groupBox_7->setAlignment(Qt::AlignCenter);
        groupBox_7->setFlat(false);
        horizontalLayout_2 = new QHBoxLayout(groupBox_7);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(groupBox_7);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setEnabled(false);
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy2);
        widget->setMinimumSize(QSize(176, 120));
        widget->setMaximumSize(QSize(176, 120));
        widget->setAutoFillBackground(false);
        widget->setStyleSheet(QStringLiteral("background-color: rgb(50,50, 50);"));

        horizontalLayout_2->addWidget(widget);


        verticalLayout->addWidget(groupBox_7);

        label_20 = new QLabel(groupBox_3);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout->addWidget(label_20);

        eas_detect = new QTextBrowser(groupBox_3);
        eas_detect->setObjectName(QStringLiteral("eas_detect"));
        eas_detect->setMinimumSize(QSize(0, 0));
        eas_detect->setMaximumSize(QSize(16777215, 16777215));
        eas_detect->setBaseSize(QSize(0, 0));

        verticalLayout->addWidget(eas_detect);


        horizontalLayout->addWidget(groupBox_3);

        groupBox_2 = new QGroupBox(tab_2);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(500, 0));
        groupBox_2->setAlignment(Qt::AlignCenter);
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(0);
        gridLayout->setVerticalSpacing(2);
        gridLayout->setContentsMargins(-1, 0, 5, 5);
        encoder_display = new QTextBrowser(groupBox_2);
        encoder_display->setObjectName(QStringLiteral("encoder_display"));
        encoder_display->setEnabled(true);

        gridLayout->addWidget(encoder_display, 3, 0, 1, 1);

        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 4, 0, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 0, 0, 1, 1);

        mux_log_display = new QTextEdit(groupBox_2);
        mux_log_display->setObjectName(QStringLiteral("mux_log_display"));
        mux_log_display->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        mux_log_display->setAutoFormatting(QTextEdit::AutoAll);
        mux_log_display->setReadOnly(true);
        mux_log_display->setAcceptRichText(true);
        mux_log_display->setTextInteractionFlags(Qt::NoTextInteraction);

        gridLayout->addWidget(mux_log_display, 1, 0, 1, 1);

        stream_status_display = new QTextBrowser(groupBox_2);
        stream_status_display->setObjectName(QStringLiteral("stream_status_display"));
        stream_status_display->setEnabled(true);
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(stream_status_display->sizePolicy().hasHeightForWidth());
        stream_status_display->setSizePolicy(sizePolicy3);
        stream_status_display->setMinimumSize(QSize(0, 0));
        stream_status_display->setMaximumSize(QSize(16777215, 16777215));
        stream_status_display->setBaseSize(QSize(176, 0));

        gridLayout->addWidget(stream_status_display, 5, 0, 1, 1);


        horizontalLayout->addWidget(groupBox_2);


        verticalLayout_2->addLayout(horizontalLayout);


        gridLayout_4->addLayout(verticalLayout_2, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        gridLayout_9 = new QGridLayout(tab_3);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        mux_log_display_2 = new QTextEdit(tab_3);
        mux_log_display_2->setObjectName(QStringLiteral("mux_log_display_2"));
        mux_log_display_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        mux_log_display_2->setAutoFormatting(QTextEdit::AutoAll);
        mux_log_display_2->setReadOnly(true);
        mux_log_display_2->setAcceptRichText(true);
        mux_log_display_2->setTextInteractionFlags(Qt::NoTextInteraction);

        gridLayout_9->addWidget(mux_log_display_2, 5, 0, 1, 2);

        label_19 = new QLabel(tab_3);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout_9->addWidget(label_19, 4, 0, 1, 2);

        groupBox_5 = new QGroupBox(tab_3);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        gridLayout_7 = new QGridLayout(groupBox_5);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        label_14 = new QLabel(groupBox_5);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_7->addWidget(label_14, 3, 0, 1, 1);

        label_15 = new QLabel(groupBox_5);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout_7->addWidget(label_15, 3, 2, 1, 2);

        mux_out_port = new QComboBox(groupBox_5);
        mux_out_port->setObjectName(QStringLiteral("mux_out_port"));

        gridLayout_7->addWidget(mux_out_port, 3, 1, 1, 1);

        mux_ctrl_addr = new QLineEdit(groupBox_5);
        mux_ctrl_addr->setObjectName(QStringLiteral("mux_ctrl_addr"));
        mux_ctrl_addr->setMaximumSize(QSize(190, 16777215));

        gridLayout_7->addWidget(mux_ctrl_addr, 2, 0, 1, 3);

        mux_ctrl_port = new QSpinBox(groupBox_5);
        mux_ctrl_port->setObjectName(QStringLiteral("mux_ctrl_port"));
        mux_ctrl_port->setMaximumSize(QSize(75, 16777215));
        mux_ctrl_port->setMinimum(1024);
        mux_ctrl_port->setMaximum(49151);
        mux_ctrl_port->setValue(17729);

        gridLayout_7->addWidget(mux_ctrl_port, 2, 3, 1, 1);

        label_13 = new QLabel(groupBox_5);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_7->addWidget(label_13, 1, 0, 1, 3);

        label_12 = new QLabel(groupBox_5);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_7->addWidget(label_12, 1, 3, 1, 1);

        label_16 = new QLabel(groupBox_5);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout_7->addWidget(label_16, 4, 0, 1, 1);

        mux_debug_comport = new QComboBox(groupBox_5);
        mux_debug_comport->setObjectName(QStringLiteral("mux_debug_comport"));
        mux_debug_comport->setEditable(true);

        gridLayout_7->addWidget(mux_debug_comport, 4, 1, 1, 1);

        update_mux_settings = new QPushButton(groupBox_5);
        update_mux_settings->setObjectName(QStringLiteral("update_mux_settings"));

        gridLayout_7->addWidget(update_mux_settings, 5, 3, 1, 1);

        restore_mux_defaults = new QPushButton(groupBox_5);
        restore_mux_defaults->setObjectName(QStringLiteral("restore_mux_defaults"));

        gridLayout_7->addWidget(restore_mux_defaults, 0, 3, 1, 1);

        set_mux_defaults = new QPushButton(groupBox_5);
        set_mux_defaults->setObjectName(QStringLiteral("set_mux_defaults"));
        set_mux_defaults->setEnabled(false);

        gridLayout_7->addWidget(set_mux_defaults, 0, 1, 1, 1);

        mux_advanced = new QRadioButton(groupBox_5);
        mux_advanced->setObjectName(QStringLiteral("mux_advanced"));

        gridLayout_7->addWidget(mux_advanced, 0, 0, 1, 1);


        gridLayout_9->addWidget(groupBox_5, 2, 0, 2, 1);

        groupBox_6 = new QGroupBox(tab_3);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        gridLayout_10 = new QGridLayout(groupBox_6);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        ch1 = new QRadioButton(groupBox_6);
        ch1->setObjectName(QStringLiteral("ch1"));
        ch1->setChecked(true);
        ch1->setAutoExclusive(false);

        gridLayout_10->addWidget(ch1, 0, 0, 1, 2);

        ch2 = new QRadioButton(groupBox_6);
        ch2->setObjectName(QStringLiteral("ch2"));
        ch2->setChecked(true);
        ch2->setAutoExclusive(false);

        gridLayout_10->addWidget(ch2, 0, 2, 1, 1);

        ch3 = new QRadioButton(groupBox_6);
        ch3->setObjectName(QStringLiteral("ch3"));
        ch3->setChecked(true);
        ch3->setAutoExclusive(false);

        gridLayout_10->addWidget(ch3, 0, 3, 1, 1);

        ch4 = new QRadioButton(groupBox_6);
        ch4->setObjectName(QStringLiteral("ch4"));
        ch4->setChecked(true);
        ch4->setAutoExclusive(false);

        gridLayout_10->addWidget(ch4, 0, 4, 1, 1);

        ch5 = new QRadioButton(groupBox_6);
        ch5->setObjectName(QStringLiteral("ch5"));
        ch5->setChecked(true);
        ch5->setAutoExclusive(false);

        gridLayout_10->addWidget(ch5, 1, 0, 1, 1);

        ch6 = new QRadioButton(groupBox_6);
        ch6->setObjectName(QStringLiteral("ch6"));
        ch6->setChecked(true);
        ch6->setAutoExclusive(false);

        gridLayout_10->addWidget(ch6, 1, 2, 1, 1);

        ch7 = new QRadioButton(groupBox_6);
        ch7->setObjectName(QStringLiteral("ch7"));
        ch7->setChecked(true);
        ch7->setAutoExclusive(false);

        gridLayout_10->addWidget(ch7, 1, 3, 1, 1);

        ch8 = new QRadioButton(groupBox_6);
        ch8->setObjectName(QStringLiteral("ch8"));
        ch8->setChecked(false);
        ch8->setAutoExclusive(false);

        gridLayout_10->addWidget(ch8, 1, 4, 1, 1);

        send_eas_config = new QPushButton(groupBox_6);
        send_eas_config->setObjectName(QStringLiteral("send_eas_config"));

        gridLayout_10->addWidget(send_eas_config, 2, 0, 1, 3);

        revert_eas_config = new QPushButton(groupBox_6);
        revert_eas_config->setObjectName(QStringLiteral("revert_eas_config"));

        gridLayout_10->addWidget(revert_eas_config, 2, 3, 1, 2);

        comboBox = new QComboBox(groupBox_6);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout_10->addWidget(comboBox, 3, 0, 1, 1);

        ad_insert = new QPushButton(groupBox_6);
        ad_insert->setObjectName(QStringLiteral("ad_insert"));

        gridLayout_10->addWidget(ad_insert, 3, 1, 1, 2);

        ad_return_to_network = new QPushButton(groupBox_6);
        ad_return_to_network->setObjectName(QStringLiteral("ad_return_to_network"));

        gridLayout_10->addWidget(ad_return_to_network, 3, 3, 1, 2);


        gridLayout_9->addWidget(groupBox_6, 2, 1, 2, 1);

        tabWidget->addTab(tab_3, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        formLayout = new QFormLayout(tab_5);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        groupBox_4 = new QGroupBox(tab_5);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setEnabled(false);
        gridLayout_6 = new QGridLayout(groupBox_4);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        lineEdit_3 = new QLineEdit(groupBox_4);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        gridLayout_6->addWidget(lineEdit_3, 4, 0, 1, 3);

        pushButton_2 = new QPushButton(groupBox_4);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout_6->addWidget(pushButton_2, 5, 2, 1, 2);

        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_6->addWidget(label_9, 3, 0, 1, 2);

        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_6->addWidget(label_10, 0, 1, 1, 2);

        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_6->addWidget(label_11, 0, 3, 1, 1);

        spinBox_2 = new QSpinBox(groupBox_4);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setMinimum(2);
        spinBox_2->setMaximum(50);
        spinBox_2->setValue(33);

        gridLayout_6->addWidget(spinBox_2, 2, 1, 1, 2);

        lineEdit_2 = new QLineEdit(groupBox_4);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout_6->addWidget(lineEdit_2, 2, 0, 1, 1);

        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_6->addWidget(label_8, 0, 0, 1, 1);

        spinBox_3 = new QSpinBox(groupBox_4);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setMinimum(1);
        spinBox_3->setValue(7);

        gridLayout_6->addWidget(spinBox_3, 2, 3, 1, 1);


        formLayout->setWidget(0, QFormLayout::LabelRole, groupBox_4);

        tabWidget->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        gridLayout_8 = new QGridLayout(tab_6);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        label_17 = new QLabel(tab_6);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout_8->addWidget(label_17, 0, 0, 1, 1);

        textEdit = new QTextEdit(tab_6);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setEnabled(false);

        gridLayout_8->addWidget(textEdit, 1, 0, 1, 1);

        tabWidget->addTab(tab_6, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 980, 18));
        menuFil = new QMenu(menuBar);
        menuFil->setObjectName(QStringLiteral("menuFil"));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QStringLiteral("menuSettings"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFil->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menuFil->addSeparator();
        menuFil->addSeparator();
        menuFil->addAction(actionExit);
        menuSettings->addAction(Select_Com_Port);
        menuSettings->addAction(actionStart_Minimized);
        menuSettings->addAction(actionConfigure_EAS_Settings);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "TVARP - TV Automation Recording and Playback", 0));
        Select_Com_Port->setText(QApplication::translate("MainWindow", "Select Com Port", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionLive_Controls->setText(QApplication::translate("MainWindow", "Live Controls", 0));
#ifndef QT_NO_TOOLTIP
        actionLive_Controls->setToolTip(QApplication::translate("MainWindow", "Live Controls", 0));
#endif // QT_NO_TOOLTIP
        actionStart_Minimized->setText(QApplication::translate("MainWindow", "Start in Tray", 0));
        actionSchedule_Program->setText(QApplication::translate("MainWindow", "Schedule Program", 0));
#ifndef QT_NO_TOOLTIP
        actionSchedule_Program->setToolTip(QApplication::translate("MainWindow", "Schedule Program", 0));
#endif // QT_NO_TOOLTIP
        actionConfigure_EAS_Settings->setText(QApplication::translate("MainWindow", "Configure EAS Settings", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Schedule", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "EAS Configuration", 0));
        label_5->setText(QApplication::translate("MainWindow", "Audio Input Device", 0));
        eas_audio_device->clear();
        eas_audio_device->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "USB Audio Device", 0)
         << QApplication::translate("MainWindow", "Line (USB EMP Audio Device)", 0)
         << QApplication::translate("MainWindow", "Line (2- USB EMP Audio Device)", 0)
        );
        test_eas->setText(QApplication::translate("MainWindow", "Test EAS Stream", 0));
        config_eas->setText(QApplication::translate("MainWindow", "Detailed Config", 0));
        eas_video_device->clear();
        eas_video_device->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "USB 2861 Device", 0)
         << QApplication::translate("MainWindow", "WDM 2861 Capture", 0)
        );
        restart_eas->setText(QApplication::translate("MainWindow", "Restart EAS Engine", 0));
        get_input_devices->setText(QApplication::translate("MainWindow", "Detect Input Devices", 0));
        label_3->setText(QApplication::translate("MainWindow", "Port:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Output Address:", 0));
        label_4->setText(QApplication::translate("MainWindow", "Video Input Device", 0));
        eas_stream_address->setInputMask(QApplication::translate("MainWindow", "000.000.000.000;_", 0));
        eas_stream_address->setText(QApplication::translate("MainWindow", "239.000.000.220", 0));
        eas_comport->clear();
        eas_comport->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "COM6", 0)
        );
        label_18->setText(QApplication::translate("MainWindow", "EAS Ring Detect", 0));
        crossbar_enable->setText(QApplication::translate("MainWindow", "Crossbar Pin", 0));
        show_vmon->setText(QApplication::translate("MainWindow", "Show Video Monitor", 0));
        stream_file->setText(QApplication::translate("MainWindow", "Stream File", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Input Preview", 0));
        groupBox_7->setTitle(QString());
        label_20->setText(QApplication::translate("MainWindow", "Ring Detect Status", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Output", 0));
        label->setText(QApplication::translate("MainWindow", "Encoder Output", 0));
        label_7->setText(QApplication::translate("MainWindow", "TvARP Status", 0));
        label_6->setText(QApplication::translate("MainWindow", "Mux Output", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "EAS", 0));
        label_19->setText(QApplication::translate("MainWindow", "Mux Output", 0));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Settings", 0));
        label_14->setText(QApplication::translate("MainWindow", "Use Mux Output:", 0));
        label_15->setText(QApplication::translate("MainWindow", "For EAS Alerts", 0));
        mux_out_port->clear();
        mux_out_port->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "ASI-1", 0)
         << QApplication::translate("MainWindow", "ASI-2", 0)
         << QApplication::translate("MainWindow", "SMPTE", 0)
         << QApplication::translate("MainWindow", "No Output", 0)
         << QApplication::translate("MainWindow", "IP-1", 0)
         << QApplication::translate("MainWindow", "IP-2", 0)
         << QApplication::translate("MainWindow", "IP-3", 0)
         << QApplication::translate("MainWindow", "IP-4", 0)
        );
        mux_ctrl_addr->setInputMask(QApplication::translate("MainWindow", "000.000.000.000;_", 0));
        mux_ctrl_addr->setText(QApplication::translate("MainWindow", "192.168.000.150", 0));
        label_13->setText(QApplication::translate("MainWindow", "Mux Control Address", 0));
        label_12->setText(QApplication::translate("MainWindow", "Port:", 0));
        label_16->setText(QApplication::translate("MainWindow", "Mux Debug on:", 0));
        mux_debug_comport->clear();
        mux_debug_comport->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "com3", 0)
        );
        update_mux_settings->setText(QApplication::translate("MainWindow", "Save Changes", 0));
        restore_mux_defaults->setText(QApplication::translate("MainWindow", "Restore Defaults", 0));
        set_mux_defaults->setText(QApplication::translate("MainWindow", "Set Defaults", 0));
        mux_advanced->setText(QApplication::translate("MainWindow", "Advanced Mode", 0));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "GroupBox", 0));
        ch1->setText(QApplication::translate("MainWindow", "3ABN English", 0));
        ch2->setText(QApplication::translate("MainWindow", "Proclaim", 0));
        ch3->setText(QApplication::translate("MainWindow", "Dare to Dream", 0));
        ch4->setText(QApplication::translate("MainWindow", "Latino", 0));
        ch5->setText(QApplication::translate("MainWindow", "3ABN RD", 0));
        ch6->setText(QApplication::translate("MainWindow", "3ABN RL", 0));
        ch7->setText(QApplication::translate("MainWindow", "Radio 74", 0));
        ch8->setText(QApplication::translate("MainWindow", "Test Channel 8", 0));
        send_eas_config->setText(QApplication::translate("MainWindow", "Send EAS Config Start", 0));
        revert_eas_config->setText(QApplication::translate("MainWindow", "Send EAS Config End", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "3ABN English", 0)
         << QApplication::translate("MainWindow", "Proclaim", 0)
         << QApplication::translate("MainWindow", "Dare to Dream", 0)
         << QApplication::translate("MainWindow", "Latino", 0)
         << QApplication::translate("MainWindow", "3ABN Radio", 0)
         << QApplication::translate("MainWindow", "Latino Radio", 0)
         << QApplication::translate("MainWindow", "Radio 74", 0)
         << QApplication::translate("MainWindow", "Test Ch 8", 0)
        );
        ad_insert->setText(QApplication::translate("MainWindow", "Ad Splice Insert", 0));
        ad_return_to_network->setText(QApplication::translate("MainWindow", "Ad Splice Return to Network", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Mux Setup", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "ID and Log Config", 0));
        lineEdit_3->setText(QApplication::translate("MainWindow", "wallawalla@3abn.org", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Save Changes", 0));
        label_9->setText(QApplication::translate("MainWindow", "Log Email", 0));
        label_10->setText(QApplication::translate("MainWindow", "Channel", 0));
        label_11->setText(QApplication::translate("MainWindow", "# Sub Chs", 0));
        lineEdit_2->setText(QApplication::translate("MainWindow", "K33EJ", 0));
        label_8->setText(QApplication::translate("MainWindow", "Station ID", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("MainWindow", "Station ID Setup", 0));
        label_17->setText(QApplication::translate("MainWindow", "3-PlayLocal.exe", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("MainWindow", "3- Play Local", 0));
        menuFil->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuSettings->setTitle(QApplication::translate("MainWindow", "Settings", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
