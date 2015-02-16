#include "pcr_analyser_mainwindow.h"
#include "ui_pcr_analyser_mainwindow.h"
#include "QtCore"
PCR_Analyser_MainWindow::PCR_Analyser_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PCR_Analyser_MainWindow)
{
    ui->setupUi(this);
}

PCR_Analyser_MainWindow::~PCR_Analyser_MainWindow()
{
    delete ui;
}

void PCR_Analyser_MainWindow::on_Process_clicked()
{
    QString source_filename, output_filename;
    source_filename = ui->source->text();
    output_filename = ui->output->text();



    process = new TS_Info(this);
    QStringList info;
    info = process->process_file(source_filename).info;
    ui->listWidget->clear();
    ui->listWidget->addItems(info);
}
