#ifndef _D_APPEALS_H_
#define _D_APPEALS_H_

#include <QDialog>

namespace Ui
{
    class DAppeals;
}

class QSqlTableModel;

class DAppeals : public QDialog
{
    Q_OBJECT

public:
    explicit DAppeals(QWidget *parent = 0);
    virtual ~DAppeals(void);

private:
    void setupModels(void);
    void setupHandlers(void);

    Ui::DAppeals *ui;

    QSqlTableModel *m_model;

private slots:
    void btnAddClick(void);
    void btnDeleteClick(void);
    void saveData(void);
};

#endif // _D_APPEALS_H_
