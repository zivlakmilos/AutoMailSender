#include "core/parser.h"

#include <QRegExp>

QString Parser::parseMessage(const QString &message, const QMap<QString, QString> &mapping, bool persisting)
{
    QString result = message;

    for(auto it = mapping.begin(); it != mapping.end(); it++)
    {
        result = result.replace(it.key(), it.value());
    }

    if(persisting)
    {
        result = result.remove(QRegExp("(\\{no_persisting\\}).*(\\{/no_persisting\\})"));
        result = result.remove(QRegExp("(\\{persisting\\})"));
        result = result.remove(QRegExp("(\\{/persisting\\})"));
    } else
    {
        result = result.remove(QRegExp("(\\{persisting\\}).*(\\{/persisting\\})"));
        result = result.remove(QRegExp("(\\{no_persisting\\})"));
        result = result.remove(QRegExp("(\\{/no_persisting\\})"));
    }

    return result;
}
