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
    setWindowTitle(QString("%1 \xA9 %2").arg(QCoreApplication::applicationName(),
                                             QCoreApplication::organizationName()));
}
