#ifndef PCR_ANALYSER_MAINWINDOW_H
#define PCR_ANALYSER_MAINWINDOW_H
#include <QMainWindow>
#include "ts_info.h"

namespace Ui {
class PCR_Analyser_MainWindow;
}

class PCR_Analyser_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PCR_Analyser_MainWindow(QWidget *parent = 0);
    ~PCR_Analyser_MainWindow();

private slots:
    void on_Process_clicked();

private:
    Ui::PCR_Analyser_MainWindow *ui;
    TS_Info *process;
};

#endif // PCR_ANALYSER_MAINWINDOW_H
