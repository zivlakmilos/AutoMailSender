#include "network/network.h"

#include <QtNetwork>

#include "json.hpp"

Network::Network(OAuthToken token, QObject *parent)
    : QObject(parent),
      m_token(token)
{
}

Network::~Network(void)
{
}

void Network::sendEmail(const QString &fromEamil, const QString &toEmail, const QString &subject, const QString &message)
{
    QString mime = "Content-Type: text/plain; charset=\"utf-8\"\r\n"
                   "MIME-Version: 1.0\r\n"
                   "Content-Transfer-Encoding: 8bit\r\n"
                   "To: " + toEmail + "\r\n"
                   "From: " + fromEamil + "\r\n"
                   "Subject: " + subject + "\r\n\r\n" +
                   message;
    QString authorization = m_token.tokenType + " " + m_token.accessToken;
    QString mimeBase64 = base64Encode(mime);
    mimeBase64.replace('+', '-');
    mimeBase64.replace('/', '_');

    QUrl url;
    url.setScheme("https");
    url.setHost("www.googleapis.com");
    url.setPath("gmail/v1/users/me/messages/send");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", authorization.toUtf8());

    nlohmann::json body = {
        { "raw", mimeBase64.toStdString() }
    };

    QNetworkAccessManager *client = new QNetworkAccessManager(this);
    connect(client, SIGNAL(finished(QNetworkReply*)), this, SLOT(sendEmailResponse(QNetworkReply*)));
    client->post(request, QString::fromStdString(body.dump()).toUtf8());
}

QString Network::base64Encode(const QString &data) const
{
    QString result;

    QByteArray ba = data.toUtf8();
    result = ba.toBase64();

    return result;
}

void Network::sendEmailResponse(QNetworkReply *reply)
{
    qDebug() << reply->readAll();
}
