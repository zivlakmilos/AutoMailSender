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

void Network::sendMail(const QString &email, const QString &subject, const QString &message)
{
    QString mime = "Content-Type: text/plain; charset=\"utf-8\"\n"
                   "MIME-Version: 1.0\n"
                   "Content-Transfer-Encoding: 8bit\n"
                   "To: nekicneko99@gmail.com\n"
                   "From: nekicneko99@gmail.com\n"
                   "Subject: naslov\n\n"
                   "Tekst poruke ide ovde";
    QString authorization = m_token.tokenType + " " + m_token.accessToken;
    QString mimeBase64 = base64Encode(mime);
    mimeBase64 = "Q29udGVudC1UeXBlOiB0ZXh0L3BsYWluOyBjaGFyc2V0PSJ1cy1hc2NpaSIKTUlNRS1WZXJzaW9uOiAxLjAKQ29udGVudC1UcmFuc2Zlci1FbmNvZGluZzogN2JpdAp0bzogbmVraWNuZWtvOTlAZ21haWwuY29tCmZyb206IG5la2ljbmVrbzk5QGdtYWlsLmNvbQpzdWJqZWN0OiBOYXNsb3YgcG9ydWtlCgpPdm8gamUgdGVrc3QgcG9ydWtl";
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
    connect(client, SIGNAL(finished(QNetworkReply*)), this, SLOT(responseReady(QNetworkReply*)));
    client->post(request, QString::fromStdString(body.dump()).toUtf8());
}

QString Network::base64Encode(const QString &data)
{
    QString result;

    QByteArray ba = data.toUtf8();
    result = ba.toBase64();

    return result;
}

void Network::responseReady(QNetworkReply *reply)
{
    qDebug() << reply->readAll();
}
