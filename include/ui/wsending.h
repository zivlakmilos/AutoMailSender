#ifndef _W_SENDING_H_
#define _W_SENDING_H_

#include <QWidget>

namespace Ui
{
    class WSending;
}

class WSending : public QWidget
{
    Q_OBJECT

public:
    explicit WSending(QWidget *parent = 0);
    virtual ~WSending(void);

private:
    void setupHandlers(void);

    Ui::WSending *ui;

private slots:
    void btnAuthenticateClick(void);
};

#endif // _W_SENDING_H_
