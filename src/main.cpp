#include <QApplication>

#include "ui/mainwindow.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName(QObject::trUtf8("AutoMainSender"));
    QCoreApplication::setOrganizationName(QObject::trUtf8("Milos Zivlak"));
    QCoreApplication::setOrganizationDomain(QObject::trUtf8("http://zivlak.ddns.net"));

    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
