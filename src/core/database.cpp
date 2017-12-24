#include "core/database.h"

#include <QDesktopServices>
#include <QSqlQuery>
#include <QVariant>
#include <QDir>

QSqlDatabase Database::loadDatabase(void)
{
    QString path = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
    QDir dir(path);
    if(!dir.exists())
        dir.mkpath(".");
    path += "/database.db";

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(path);
    database.open();
    return database;
}

QSqlDatabase Database::getDatabase(void)
{
    return QSqlDatabase::database();
}

bool Database::isSchemaExists(const QSqlDatabase &database)
{
    QString sql = "SELECT COUNT(*) FROM sqlite_master WHERE type='table'";
    QSqlQuery query(sql, database);

    if(query.exec() && query.next())
    {
        if(query.value(0).toInt() >= 4)
            return true;
    }

    return false;
}

bool Database::createSchema(const QSqlDatabase &database)
{
    QString sql = "CREATE TABLE IF NOT EXISTS `appeals` ("
                  "    `id`    INTEGER,"
                  "    `name`  TEXT,"
                  "    `male`  TEXT,"
                  "    `female`  TEXT,"
                  "    PRIMARY KEY(`id`)"
                  ");"
                  "CREATE TABLE IF NOT EXISTS `me` ("
                  "    `id`    INTEGER,"
                  "    `email` TEXT,"
                  "    `name`  TEXT,"
                  "    `surname`   TEXT,"
                  "    `signature` TEXT,"
                  "    `oauth_client_id` TEXT,"
                  "    `oauth_client_secret` TEXT,"
                  "    PRIMARY KEY(`id`)"
                  ");"
                  "CREATE TABLE IF NOT EXISTS `messages` ("
                  "    `id`    INTEGER,"
                  "    `message`   TEXT,"
                  "    PRIMARY KEY(`id`)"
                  ");"
                  "CREATE TABLE IF NOT EXISTS `peoples` ("
                  "    `id`    INTEGER,"
                  "    `email` TEXT,"
                  "    `name`  TEXT,"
                  "    `surname`   TEXT,"
                  "    `prefix`    TEXT,"
                  "    `appeal`    INTEGER,"
                  "    `sex`   INTEGER,"
                  "    `persisting`   INTEGER,"
                  "    PRIMARY KEY(`id`)"
                  ");"
                  "INSERT INTO `me` DEFAULT VALUES;";
    QSqlQuery query(database);
    QStringList sqls = sql.split(';');

    for(auto it = sqls.begin(); it != sqls.end(); it++)
    {
        if(it->trimmed().isEmpty())
            continue;
        if(!query.exec(*it))
            return false;
    }

    return true;
}
