#include <QApplication>

#include "database.h"
#include "ui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    /*
     * Core
     */

    QCoreApplication::setApplicationName(QObject::trUtf8("AutoMainSender"));
    QCoreApplication::setOrganizationName(QObject::trUtf8("Milos Zivlak"));
    QCoreApplication::setOrganizationDomain(QObject::trUtf8("http://zivlak.ddns.net"));

    /*
     * Database
     */

    Database::loadDatabase();

    /*
     * GUI
     */

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
