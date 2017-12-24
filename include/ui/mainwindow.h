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
    void setupHandlers(void);

    Ui::MainWindow *ui;

private slots:
    void changeCoreData(void);
    void changeAppealData(void);
};

#endif // _MAIN_WINDOW_H_
