#include "ui/mainwindow.h"

#include <QtGui>

#include "ui_mainwindow.h"
#include "core/database.h"
#include "ui/dcoredata.h"
#include "ui/dappeals.h"
#include "ui/wpeoples.h"
#include "ui/wmessages.h"
#include "ui/wsending.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    setupDatabase();
    setupUI();
    setupHandlers();
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
    wCentral->addTab(new WMessages(this), trUtf8("Messages"));
    wCentral->addTab(new WSending(this), trUtf8("Sending"));
    setCentralWidget(wCentral);
}

void MainWindow::setupHandlers(void)
{
    connect(ui->actionCoreData, SIGNAL(triggered(bool)),
            this, SLOT(changeCoreData()));
    connect(ui->actionAppels, SIGNAL(triggered(bool)),
            this, SLOT(changeAppealData()));
}

void MainWindow::setupDatabase(void)
{
    QSqlDatabase db = Database::getDatabase();
    if(!Database::isSchemaExists(db))
    {
        if(Database::createSchema(db))
        {
            changeCoreData();
        } else
        {
            QMessageBox::critical(this, QCoreApplication::applicationName(),
                                  trUtf8("Error while create database schema!"));
            qApp->exit();
        }
    }
}

void MainWindow::changeCoreData(void)
{
    DCoreData *dCoreData = new DCoreData(this);
    dCoreData->exec();
}

void MainWindow::changeAppealData(void)
{
    DAppeals *dAppeals = new DAppeals(this);
    dAppeals->exec();
}
