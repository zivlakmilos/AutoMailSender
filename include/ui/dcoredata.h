#ifndef _D_CORE_DATA_H_
#define _D_CORE_DATA_H_

#include <QDialog>

namespace Ui
{
    class DCoreData;
}

class DCoreData : public QDialog
{
    Q_OBJECT

public:
    explicit DCoreData(QWidget *parent = 0);
    virtual ~DCoreData(void);

private:
    void setupUI(void);

    Ui::DCoreData *ui;
};

#endif // _D_CORE_DATA_H_
