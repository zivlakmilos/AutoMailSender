#ifndef _AUTHENTICATION_H_
#define _AUTHENTICATION_H_

#include <QObject>

class QNetworkReply;

struct OAuthToken
{
    QString accessToken;
    QString tokenType;
    int expiresIn;
    QString refreshToken;
};

class Authentication : public QObject
{
    Q_OBJECT

public:
    explicit Authentication(QObject *parent = 0);
    virtual ~Authentication(void);

    bool startAuthentication(const QString &clientId, const QString &clientSecret);
    void exchangeCodeForToken(const QString &authCode);

private:
    QString m_clientId;
    QString m_clientSecret;
    QString m_authCode;

signals:
    void authenticationCompleted(bool success, const OAuthToken &token);

private slots:
    void responseReady(QNetworkReply *reply);
};

#endif // _AUTHENTICATION_H_
