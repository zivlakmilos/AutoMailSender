#include "ui/wmessages.h"

#include <QtGui>
#include <QSqlTableModel>

#include "ui_wmessage.h"
#include "core/database.h"

WMessages::WMessages(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::WMessages)
{
    ui->setupUi(this);
    setupModels();
    setupHandlers();
}

WMessages::~WMessages(void)
{
    if(ui)
        delete ui;
}

void WMessages::setupModels(void)
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
    modelMapper->addMapping(ui->txtSubject, indexSubject);
    modelMapper->addMapping(ui->txtMessage, indexMessage);
    connect(ui->tblMessages->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            modelMapper, SLOT(setCurrentModelIndex(QModelIndex)));

    m_model->select();
    ui->tblMessages->setCurrentIndex(m_model->index(0, 0));
    modelMapper->toFirst();
}

void WMessages::setupHandlers(void)
{
    connect(ui->btnAdd, SIGNAL(clicked(bool)),
            this, SLOT(btnAddClick()));
    connect(ui->btnDelete, SIGNAL(clicked(bool)),
            this, SLOT(btnDeleteClick()));
    connect(ui->btnSave, SIGNAL(clicked(bool)),
            this, SLOT(btnSaveClick()));
}

void WMessages::btnAddClick(void)
{
    m_model->insertRow(m_model->rowCount());
}

void WMessages::btnDeleteClick(void)
{
    if(m_model->rowCount() == 0)
        return;

    QString subject = m_model->data(m_model->index(ui->tblMessages->currentIndex().row(),
                                                   m_model->fieldIndex("email"))).toString();
    QMessageBox msg(QMessageBox::Critical,
                    QCoreApplication::applicationName(),
                    trUtf8("Are you sure you want to delete message: %1?").arg(subject),
                    QMessageBox::Yes | QMessageBox::No);
    msg.setDefaultButton(QMessageBox::No);

    if(msg.exec() == QMessageBox::Yes)
    {
        m_model->removeRow(ui->tblMessages->currentIndex().row());
    }
}

void WMessages::btnSaveClick(void)
{
    m_model->submitAll();
}
