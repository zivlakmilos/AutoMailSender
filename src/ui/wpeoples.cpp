#include "ui/wpeoples.h"

#include <QtGui>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>

#include "ui_wpeoples.h"
#include "database.h"

WPeoples::WPeoples(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::WPeoples)
{
    ui->setupUi(this);
    setupModels();
    setupHandlers();
}

WPeoples::~WPeoples(void)
{
    if(ui)
        delete(ui);
}

void WPeoples::setupModels(void)
{
    QSqlDatabase db = Database::getDatabase();
    m_model = new QSqlRelationalTableModel(this, db);
    m_model->setTable("peoples");
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    int indexId = m_model->fieldIndex("id");
    int indexEmail = m_model->fieldIndex("email");
    int indexName = m_model->fieldIndex("name");
    int indexSurname = m_model->fieldIndex("surname");
    int indexDisplayName = m_model->fieldIndex("display_name");
    int indexPrefix = m_model->fieldIndex("prefix");
    int indexAppeal = m_model->fieldIndex("appeal");
    int indexSex = m_model->fieldIndex("sex");
    int indexPersisting = m_model->fieldIndex("persisting");

    m_model->setRelation(indexAppeal, QSqlRelation("appeals", "id", "name"));

    m_model->setHeaderData(indexEmail, Qt::Horizontal, trUtf8("Email"));
    m_model->setHeaderData(indexName, Qt::Horizontal, trUtf8("Name"));
    m_model->setHeaderData(indexSurname, Qt::Horizontal, trUtf8("Surname"));
    m_model->setHeaderData(indexDisplayName, Qt::Horizontal, trUtf8("Display name"));
    m_model->setHeaderData(indexPrefix, Qt::Horizontal, trUtf8("Prefix"));
    m_model->setHeaderData(indexAppeal, Qt::Horizontal, trUtf8("Appeal"));
    m_model->setHeaderData(indexSex, Qt::Horizontal, trUtf8("Sex"));
    m_model->setHeaderData(indexPersisting, Qt::Horizontal, trUtf8("Persisting"));

    ui->tblPeoples->setModel(m_model);
    ui->tblPeoples->setItemDelegate(new QSqlRelationalDelegate(this));
    ui->tblPeoples->setColumnHidden(indexId, true);

    m_model->select();
    ui->tblPeoples->setCurrentIndex(m_model->index(0, 0));
}

void WPeoples::setupHandlers(void)
{
    connect(ui->btnAdd, SIGNAL(clicked(bool)),
            this, SLOT(btnAddClick()));
    connect(ui->btnDelete, SIGNAL(clicked(bool)),
            this, SLOT(btnDeleteClick()));
    connect(ui->btnSave, SIGNAL(clicked(bool)),
            this, SLOT(btnSaveClick()));
}

void WPeoples::btnAddClick(void)
{
    m_model->insertRow(m_model->rowCount());
}

void WPeoples::btnDeleteClick(void)
{
    if(m_model->rowCount() == 0)
        return;

    QString email = m_model->data(m_model->index(ui->tblPeoples->currentIndex().row(),
                                                 m_model->fieldIndex("email"))).toString();
    QMessageBox msg(QMessageBox::Critical,
                    QCoreApplication::applicationName(),
                    trUtf8("Are you sure you want to delete people: %1?").arg(email),
                    QMessageBox::Yes | QMessageBox::No);
    msg.setDefaultButton(QMessageBox::No);

    if(msg.exec() == QMessageBox::Yes)
    {
        m_model->removeRow(ui->tblPeoples->currentIndex().row());
    }
}

void WPeoples::btnSaveClick(void)
{
    m_model->submitAll();
}
