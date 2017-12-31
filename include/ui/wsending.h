#ifndef _W_SENDING_H_
#define _W_SENDING_H_

#include <QWidget>

#include "network/authentication.h"

namespace Ui
{
    class WSending;
}

class QSqlTableModel;
class QDataWidgetMapper;

class Network;

class WSending : public QWidget
{
    Q_OBJECT

public:
    explicit WSending(QWidget *parent = 0);
    virtual ~WSending(void);

private:
    void setupModels(void);
    void setupHandlers(void);

    Ui::WSending *ui;

    Network *m_network;
    QSqlTableModel *m_model;
    QDataWidgetMapper *m_mapper;

    QString m_myEmail;
    QString m_mySignature;

private slots:
    void btnAuthenticateClick(void);
    void btnSendClick(void);
    void authenticationCoplete(bool success, OAuthToken token);
};

#endif // _W_SENDING_H_
