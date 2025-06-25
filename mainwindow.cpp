#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <unistd.h>
#include <thread.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);


    thread = new Thread();

    connect(thread, SIGNAL(showtim(int)), this, SLOT(showTim()));

//    QTime qtim = QTime::currentTime();
//    printf("%lld\n", qtim.msec());

}



LL MainWindow::getTim() {
    return QDateTime::currentMSecsSinceEpoch();
}



QString MainWindow::toStr(LL n) {
    return QString().sprintf("%02lld : %02lld : %02lld . %02lld", n / 3600000, n % 3600000 / 60000, n % 60000 / 1000, n % 1000 / 10);
}

void MainWindow::showTim()
{
    if (flag)
        ui->tim->setText(toStr(getTim() - lstTime + lstIntervals));
    return ;
}


void MainWindow::start() {
    flag = true;
    lstTime = getTim();
    thread->start();
    return ;
}

void MainWindow::stop() {
    flag = false;
    lstIntervals += getTim() - lstTime;
    thread->stop();
}

void MainWindow::remember()
{
    LL tmp = getTim() - lstTime + lstIntervals;
    history = QString().sprintf("%02lld", ++tot) + space + toStr(tmp) + space + "+ "
            + toStr(tmp - tmp % 10 - lstRemember + lstRemember % 10) + "\n" + history;
    ui->his->setPlainText(history);
    lstRemember = tmp;
    return ;
}

void MainWindow::clean() {
    lstTime = lstIntervals = tot = lstRemember = 0;
    history = "";
    ui->tim->setText("00 : 00 : 00 . 00");
    ui->his->clear();
    return ;
}


void MainWindow::on_ss_clicked()
{
    if (ui->ss->text() == "Start") {
        start();
        ui->ss->setText("Stop");
        ui->cr->setText("Remember");
    } else {
        stop();
        ui->ss->setText("Start");
        ui->cr->setText("Clean");
    }
    return ;
}



void MainWindow::on_cr_clicked()
{
    if (ui->cr->text() == "Clean") {
        clean();
    } else {
        remember();
    }
    return ;
}



MainWindow::~MainWindow()
{
    delete ui;
}
