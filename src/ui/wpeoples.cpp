#include "ui/wpeoples.h"

#include "ui_wpeoples.h"

WPeoples::WPeoples(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::WPeoples)
{
    ui->setupUi(this);
}

WPeoples::~WPeoples(void)
{
    if(ui)
        delete(ui);
}
