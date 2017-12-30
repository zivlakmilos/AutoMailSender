#include "ui/wsending.h"

#include <QtGui>
#include <QSqlTableModel>
#include <QSqlQuery>

#include "ui_wsending.h"
#include "core/database.h"
#include "network/authentication.h"
#include "network/network.h"

WSending::WSending(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::WSending)
{
    ui->setupUi(this);
    setupModels();
    setupHandlers();
}

WSending::~WSending(void)
{
    if(ui)
        delete ui;
}

void WSending::setupModels(void)
{
    QSqlDatabase db = Database::getDatabase();
    m_model = new QSqlTableModel(this, db);
    m_model->setTable("messages");
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    int indexId = m_model->fieldIndex("id");
    int indexSubject = m_model->fieldIndex("subject");
    int indexMessage = m_model->fieldIndex("message");

    m_model->setHeaderData(indexSubject, Qt::Horizontal, "Subject");

    ui->tblMessages->setModel(m_model);
    ui->tblMessages->setColumnHidden(indexId, true);
    ui->tblMessages->setColumnHidden(indexMessage, true);

    QDataWidgetMapper *modelMapper = new QDataWidgetMapper(this);
    modelMapper->setModel(m_model);
    modelMapper->addMapping(ui->txtMessage, indexMessage);
    connect(ui->tblMessages->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            modelMapper, SLOT(setCurrentModelIndex(QModelIndex)));

    m_model->select();
    ui->tblMessages->setCurrentIndex(m_model->index(0, 0));
    modelMapper->toFirst();
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
    QSqlDatabase db = Database::getDatabase();
    QSqlQuery query(db);
    QString strQuery = "SELECT"
                       "    id,"
                       "    email,"
                       "    name,"
                       "    surname,"
                       "    signature,"
                       "    oauth_client_id,"
                       "    oauth_client_secret "
                       "FROM me";

    if(query.exec(strQuery) && query.next())
    {
        QString email = query.value(1).toString();
        QString name = query.value(2).toString();
        QString surname = query.value(3).toString();
        QString oAuthClientId = query.value(5).toString();
        QString oAuthClientSecret = query.value(6).toString();

        m_myEmail = name + " " + surname + " <" + email + ">";

        Authentication *auth = new Authentication(this);
        auth->startAuthentication(oAuthClientId, oAuthClientSecret);
        QString authCode = QInputDialog::getText(this, QCoreApplication::applicationName(),
                                                 trUtf8("OAuth code (copy paste from web browser):"));
        connect(auth, SIGNAL(authenticationCompleted(bool,OAuthToken)),
                this, SLOT(authenticationCoplete(bool,OAuthToken)));
        auth->exchangeCodeForToken(authCode);
    }
}

void WSending::btnSendClick(void)
{
    QSqlDatabase db = Database::getDatabase();
    QSqlQuery query(db);
    QString strQuery = "SELECT"
                       "    p.id,"
                       "    p.email,"
                       "    p.name,"
                       "    p.surname,"
                       "    p.prefix,"
                       "    p.sex,"
                       "    p.persisting,"
                       "    a.male,"
                       "    a.female "
                       "FROM peoples p "
                       "LEFT JOIN appeals a ON p.appeal = a.id";

    if(query.exec(strQuery))
    {
        while(query.next())
        {
            QString email = query.value(1).toString();
            QString name = query.value(2).toString();
            QString surname = query.value(3).toString();
            QString prefix = query.value(4).toString();
            int sex = query.value(5).toInt();
            bool persisting = query.value(6).toInt();
            QString appealMale = query.value(7).toString();
            QString appealFemale = query.value(8).toString();

            QString toEmail = name + " " + surname + " <" + email + ">";
            QString subject = m_model->data(m_model->index(ui->tblMessages->currentIndex().row(),
                                                           m_model->fieldIndex("subject"))).toString();
            QString message = m_model->data(m_model->index(ui->tblMessages->currentIndex().row(),
                                                           m_model->fieldIndex("message"))).toString();
            m_network->sendEmail(m_myEmail, toEmail, subject, message);
        }
    }
}

void WSending::authenticationCoplete(bool success, OAuthToken token)
{
    if(!success)
        return;

    m_network = new Network(token, this);
    ui->gbMessage->setEnabled(true);
}
