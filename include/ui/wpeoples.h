#ifndef _W_PEOPLES_H_
#define _W_PEOPLES_H_

#include <QWidget>

namespace Ui
{
    class WPeoples;
}

class QSqlRelationalTableModel;

class WPeoples : public QWidget
{
    Q_OBJECT

public:
    explicit WPeoples(QWidget *parent = 0);
    virtual ~WPeoples(void);

private:
    void setupModels(void);
    void setupHandlers(void);

    Ui::WPeoples *ui;

    QSqlRelationalTableModel *m_model;

private slots:
    void btnAddClick(void);
    void btnDeleteClick(void);
    void btnSaveClick(void);
};

#endif // _W_PEOPLES_H_
