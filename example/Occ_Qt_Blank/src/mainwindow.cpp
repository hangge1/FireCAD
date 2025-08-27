#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    setWindowIcon(QIcon(":/icons/resource/QtVtkOcct.ico"));
}

MainWindow::~MainWindow()
{}

