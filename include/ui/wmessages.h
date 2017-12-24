#ifndef _W_MESSAGES_H_
#define _W_MESSAGES_H_

#include <QWidget>

namespace Ui
{
    class WMessages;
}

class QSqlTableModel;

class WMessages : public QWidget
{
    Q_OBJECT

public:
    explicit WMessages(QWidget *parent = 0);
    virtual ~WMessages(void);

private:
    void setupModels(void);
    void setupHandlers(void);

    Ui::WMessages *ui;

    QSqlTableModel *m_model;

private slots:
    void btnAddClick(void);
    void btnDeleteClick(void);
    void btnSaveClick(void);
};

#endif // _W_MESSAGES_H_
