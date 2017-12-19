#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <QSqlDatabase>

namespace Database
{
    QSqlDatabase loadDatabase(void);
    QSqlDatabase getDatabase(void);
    bool isSchemaExists(const QSqlDatabase &database);
    bool createSchema(const QSqlDatabase &database);
}

#endif // _DATABASE_H_
