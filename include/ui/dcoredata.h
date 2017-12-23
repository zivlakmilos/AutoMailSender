#ifndef _D_CORE_DATA_H_
#define _D_CORE_DATA_H_

#include <QDialog>

namespace Ui
{
    class DCoreData;
}

class QSqlTableModel;

class DCoreData : public QDialog
{
    Q_OBJECT

public:
    explicit DCoreData(QWidget *parent = 0);
    virtual ~DCoreData(void);

private:
    void setupModels(void);
    void setupHandlers(void);

    Ui::DCoreData *ui;

    QSqlTableModel *m_model;

private slots:
    void saveData(void);
};

#endif // _D_CORE_DATA_H_
