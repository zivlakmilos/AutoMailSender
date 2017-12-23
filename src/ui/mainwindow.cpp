#include "ui/mainwindow.h"

#include <QtGui>

#include "ui_mainwindow.h"
#include "database.h"
#include "ui/dcoredata.h"
#include "ui/wpeoples.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    setupDatabase();
    setupUI();
}

MainWindow::~MainWindow(void)
{
    if(ui)
        delete ui;
}

void MainWindow::setupUI(void)
{
    ui->setupUi(this);
    setWindowTitle(QString("%1 \xA9 %2").arg(QCoreApplication::applicationName(),
                                             QCoreApplication::organizationName()));

    QTabWidget *wCentral = new QTabWidget(this);
    wCentral->addTab(new WPeoples(this), trUtf8("Peoples"));
    setCentralWidget(wCentral);
}

void MainWindow::setupDatabase(void)
{
    QSqlDatabase db = Database::getDatabase();
    if(!Database::isSchemaExists(db))
    {
        if(Database::createSchema(db))
        {
            DCoreData *dCoreData = new DCoreData(this);
            dCoreData->exec();
        } else
        {
            QMessageBox::critical(this, QCoreApplication::applicationName(),
                                  trUtf8("Error while create database schema!"));
            qApp->exit();
        }
    }
}
