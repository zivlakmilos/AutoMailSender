#ifndef _H_PARSER_H_
#define _H_PARSER_H_

#include <QMap>
#include <QString>

namespace Parser
{
    QString parseMessage(const QString &message, const QMap<QString, QString> &mapping, bool persisting);
}

#endif // _H_PARSER_H_
