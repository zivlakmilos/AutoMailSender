#include "ui/dappeals.h"

#include <QtGui>
#include <QSqlTableModel>

#include "ui_dappeals.h"
#include "database.h"

DAppeals::DAppeals(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::DAppeals)
{
    ui->setupUi(this);
    setupModels();
    setupHandlers();
}

DAppeals::~DAppeals(void)
{
    if(ui)
        delete ui;
}

void DAppeals::setupModels(void)
{
    QSqlDatabase db = Database::getDatabase();
    m_model = new QSqlTableModel(this, db);
    m_model->setTable("appeals");
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    int indexId = m_model->fieldIndex("id");
    int indexName = m_model->fieldIndex("name");
    int indexMale = m_model->fieldIndex("male");
    int indexFemale = m_model->fieldIndex("female");

    m_model->setHeaderData(indexName, Qt::Horizontal, "Name");
    m_model->setHeaderData(indexMale, Qt::Horizontal, "Male");
    m_model->setHeaderData(indexFemale, Qt::Horizontal, "Female");

    ui->tblAppeals->setModel(m_model);
    ui->tblAppeals->setColumnHidden(indexId, true);

    QDataWidgetMapper *modelMapper = new QDataWidgetMapper(this);
    modelMapper->setModel(m_model);
    modelMapper->addMapping(ui->txtName, indexName);
    modelMapper->addMapping(ui->txtMale, indexMale);
    modelMapper->addMapping(ui->txtFemale, indexFemale);
    connect(ui->tblAppeals->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            modelMapper, SLOT(setCurrentModelIndex(QModelIndex)));

    m_model->select();
    ui->tblAppeals->setCurrentIndex(m_model->index(0, 0));
    modelMapper->toFirst();
}

void DAppeals::setupHandlers(void)
{
    connect(ui->btnAdd, SIGNAL(clicked(bool)),
            this, SLOT(btnAddClick()));
    connect(ui->btnDelete, SIGNAL(clicked(bool)),
            this, SLOT(btnDeleteClick()));
    connect(ui->btnSave, SIGNAL(clicked(bool)),
            this, SLOT(saveData()));
    connect(ui->btnClose, SIGNAL(clicked(bool)),
            this, SLOT(accept()));
}

void DAppeals::btnAddClick(void)
{
    m_model->insertRow(m_model->rowCount());
}

void DAppeals::btnDeleteClick(void)
{
    if(m_model->rowCount() == 0)
        return;

    QString name = m_model->data(m_model->index(ui->tblAppeals->currentIndex().row(),
                                                m_model->fieldIndex("name"))).toString();
    QMessageBox msg(QMessageBox::Critical,
                    QCoreApplication::applicationName(),
                    trUtf8("Are you sure you want to delete appeal: %1?").arg(name),
                    QMessageBox::Yes | QMessageBox::No);
    msg.setDefaultButton(QMessageBox::No);

    if(msg.exec() == QMessageBox::Yes)
    {
        m_model->removeRow(ui->tblAppeals->currentIndex().row());
    }
}

void DAppeals::saveData(void)
{
    m_model->submitAll();
}
