#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow(void);

private:
    void setupUI(void);
    void setupDatabase(void);

    Ui::MainWindow *ui;
};

#endif // _MAIN_WINDOW_H_
