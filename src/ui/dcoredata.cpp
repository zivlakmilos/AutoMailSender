#include "ui/dcoredata.h"

#include <QtGui>

#include "ui_dcoredata.h"

DCoreData::DCoreData(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::DCoreData)
{
    setupUI();
}

DCoreData::~DCoreData(void)
{
    if(ui)
        delete ui;
}

void DCoreData::setupUI(void)
{
    ui->setupUi(this);

    connect(ui->btnSave, SIGNAL(clicked(bool)),
            this, SLOT(accept()));
    connect(ui->btnClose, SIGNAL(clicked(bool)),
            this, SLOT(reject()));
}

