#include "ui/dcoredata.h"

#include <QtGui>
#include <QSqlTableModel>

#include "ui_dcoredata.h"
#include "core/database.h"

DCoreData::DCoreData(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::DCoreData)
{
    ui->setupUi(this);
    setupModels();
    setupHandlers();
}

DCoreData::~DCoreData(void)
{
    if(ui)
        delete ui;
}

void DCoreData::setupModels(void)
{
    QSqlDatabase db = Database::getDatabase();
    m_model = new QSqlTableModel(this, db);
    m_model->setTable("me");
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_model->select();

    QDataWidgetMapper *modelMapper = new QDataWidgetMapper(this);
    modelMapper->setModel(m_model);
    modelMapper->addMapping(ui->txtEmail, m_model->fieldIndex("email"));
    modelMapper->addMapping(ui->txtName, m_model->fieldIndex("name"));
    modelMapper->addMapping(ui->txtSurname, m_model->fieldIndex("surname"));
    modelMapper->addMapping(ui->txtOAuthClientID, m_model->fieldIndex("oauth_client_id"));
    modelMapper->addMapping(ui->txtOAuthClientSecrert, m_model->fieldIndex("oauth_client_secret"));
    modelMapper->addMapping(ui->txtSignature, m_model->fieldIndex("signature"));
    modelMapper->toFirst();
}

void DCoreData::setupHandlers(void)
{
    connect(this, SIGNAL(accepted()),
            this, SLOT(saveData()));
    connect(ui->btnSave, SIGNAL(clicked(bool)),
            this, SLOT(accept()));
    connect(ui->btnClose, SIGNAL(clicked(bool)),
            this, SLOT(reject()));
}

void DCoreData::saveData(void)
{
    m_model->submitAll();
}
