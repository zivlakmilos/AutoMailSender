#ifndef _W_PEOPLES_H_
#define _W_PEOPLES_H_

#include <QWidget>

namespace Ui
{
    class WPeoples;
}

class WPeoples : public QWidget
{
    Q_OBJECT

public:
    explicit WPeoples(QWidget *parent = 0);
    virtual ~WPeoples(void);

private:
    Ui::WPeoples *ui;
};

#endif // _W_PEOPLES_H_
