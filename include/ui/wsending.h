#ifndef _W_SENDING_H_
#define _W_SENDING_H_

#include <QWidget>

#include "network/authentication.h"

namespace Ui
{
    class WSending;
}

class Network;

class WSending : public QWidget
{
    Q_OBJECT

public:
    explicit WSending(QWidget *parent = 0);
    virtual ~WSending(void);

private:
    void setupHandlers(void);

    Ui::WSending *ui;

    Network *m_network;

private slots:
    void btnAuthenticateClick(void);
    void btnSendClick(void);
    void authenticationCoplete(bool success, OAuthToken token);
};

#endif // _W_SENDING_H_
