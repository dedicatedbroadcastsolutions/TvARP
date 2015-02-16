#include "pcr_analyser_mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PCR_Analyser_MainWindow w;
    w.show();

    return a.exec();
}
