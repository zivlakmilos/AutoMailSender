#include "network/authentication.h"

#include <QUrl>
#include <QtNetwork>
#include <QDesktopServices>

Authentication::Authentication(QObject *parent)
    : QObject(parent)
{
}

Authentication::~Authentication(void)
{
}

bool Authentication::startAuthentication(const QString &clientId, const QString &clientSecret)
{
    m_clientId = clientId;
    m_clientSecret = clientSecret;

    QString strUrl = QString("https://accounts.google.com/o/oauth2/auth?"
                             "redirect_uri=urn:ietf:wg:oauth:2.0:oob&"
                             "response_type=code&"
                             "client_id=%1&"
                             "scope=https://mail.google.com/&"
                             "approval_prompt=force&"
                             "access_type=offline").arg(m_clientId);
    QUrl url(strUrl);
    return QDesktopServices::openUrl(url);
}

bool Authentication::exchangeCodeForToken(const QString &authCode)
{
    m_authCode = authCode;

    QUrl url;
    url.setScheme("https");
    url.setHost("www.googleapis.com");
    url.setPath("oauth2/v4/token");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrl body;
    body.addQueryItem("code", m_authCode);
    body.addQueryItem("client_id", m_clientId);
    body.addQueryItem("client_secret", m_clientSecret);
    body.addQueryItem("redirect_uri", "urn:ietf:wg:oauth:2.0:oob");
    body.addQueryItem("grant_type", "authorization_code");

    QNetworkAccessManager *client = new QNetworkAccessManager(this);
    connect(client, SIGNAL(finished(QNetworkReply*)), this, SLOT(test(QNetworkReply*)));
    client->post(request, body.encodedQuery());
}

void Authentication::test(QNetworkReply *reply)
{
    qDebug() << reply->readAll();
}
