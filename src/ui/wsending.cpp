#include "ui/wsending.h"

#include <QtGui>

#include "ui_wsending.h"
#include "network/authentication.h"
#include "network/network.h"

WSending::WSending(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::WSending)
{
    ui->setupUi(this);
    setupHandlers();
}

WSending::~WSending(void)
{
    if(ui)
        delete ui;
}

void WSending::setupHandlers(void)
{
    connect(ui->btnAuthenticate, SIGNAL(clicked(bool)),
            this, SLOT(btnAuthenticateClick()));
    connect(ui->btnSend, SIGNAL(clicked(bool)),
            this, SLOT(btnSendClick()));
}

void WSending::btnAuthenticateClick(void)
{
    Authentication *auth = new Authentication(this);
    auth->startAuthentication("826844513947-5d83tgsbu435f5bl59hd0r2omu4vto3r.apps.googleusercontent.com", "6g4_pILrsBZbkZVTu8V2nfCx");
    QString authCode = QInputDialog::getText(this, QCoreApplication::applicationName(),
                                             trUtf8("OAuth code:"));
    connect(auth, SIGNAL(authenticationCompleted(bool,OAuthToken)),
            this, SLOT(authenticationCoplete(bool,OAuthToken)));
    auth->exchangeCodeForToken(authCode);
}

void WSending::btnSendClick(void)
{
    m_network->sendMail("adf", "adf", "adfadfadfdd");
}

void WSending::authenticationCoplete(bool success, OAuthToken token)
{
    if(!success)
        return;

    m_network = new Network(token, this);
    ui->gbMessage->setEnabled(true);
}
