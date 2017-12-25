#include "ui/wsending.h"

#include <QtGui>

#include "ui_wsending.h"
#include "network/authentication.h"

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
}

void WSending::btnAuthenticateClick(void)
{
    Authentication *tmp = new Authentication(this);
    tmp->startAuthentication("826844513947-5d83tgsbu435f5bl59hd0r2omu4vto3r.apps.googleusercontent.com", "6g4_pILrsBZbkZVTu8V2nfCx");
    QString authCode = QInputDialog::getText(this, QCoreApplication::applicationName(),
                                             trUtf8("OAuth code:"));
    tmp->exchangeCodeForToken(authCode);
}
