#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef long long LL;

class Thread;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_ss_clicked();
    void on_cr_clicked();
    void showTim();

private:
    Ui::MainWindow *ui;
    bool flag;
    QString space = "                         ";
    QString history = "";
    LL lstTime = 0;
    LL lstIntervals = 0;
    LL lstRemember = 0;
    LL tot = 0;

    LL getTim();
    QString toStr(LL n);
    void start();
    void stop();
    void clean();
    void remember();
    Thread *thread;
};
#endif // MAINWINDOW_H
