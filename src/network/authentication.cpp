#include "network/authentication.h"

#include <QUrl>
#include <QtNetwork>
#include <QDesktopServices>

#include "json.hpp"

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
                             "scope=https://mail.google.com/+"
                                   "https://www.googleapis.com/auth/gmail.modify+"
                                   "https://www.googleapis.com/auth/gmail.compose+"
                                   "https://www.googleapis.com/auth/gmail.send&"
                             "approval_prompt=force&"
                             "access_type=offline").arg(m_clientId);
    QUrl url(strUrl);
    return QDesktopServices::openUrl(url);
}

void Authentication::exchangeCodeForToken(const QString &authCode)
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
    connect(client, SIGNAL(finished(QNetworkReply*)), this, SLOT(responseReady(QNetworkReply*)));
    client->post(request, body.encodedQuery());
}

void Authentication::responseReady(QNetworkReply *reply)
{
    QString response = reply->readAll();
    nlohmann::json json = nlohmann::json::parse(response.toStdString());
    OAuthToken token;

    try {
        token.accessToken = QString::fromStdString(json.at("access_token"));
        token.expiresIn = json.at("expires_in");
        token.refreshToken = QString::fromStdString(json.at("refresh_token"));
        token.tokenType = QString::fromStdString(json.at("token_type"));
        emit authenticationCompleted(true, token);
    } catch(...) {
        emit authenticationCompleted(false, token);
    }
}
