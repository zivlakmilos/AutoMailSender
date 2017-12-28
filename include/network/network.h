#ifndef _NETWORK_H_
#define _NETWORK_H_

#include "network/authentication.h"

class Network : QObject
{
    Q_OBJECT

public:
    Network(OAuthToken token, QObject *parent = 0);
    ~Network(void);

    void sendMail(const QString &email, const QString &subject, const QString &message);

private:
    QString base64Encode(const QString &data);

    OAuthToken m_token;

private slots:
    void responseReady(QNetworkReply *reply);
};

#endif // _NETWORK_H_
