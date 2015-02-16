#include "ingest_dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.setWindowTitle("TvARP Ingest");
    w.show();

    return a.exec();
}
