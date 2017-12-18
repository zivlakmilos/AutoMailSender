#include "mainwindow.h"

#include <QtGui>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
}

MainWindow::~MainWindow(void)
{
}

void MainWindow::setupUI(void)
{
    setWindowTitle(QString("%s %s %s").arg(QCoreApplication::applicationName()));
}
