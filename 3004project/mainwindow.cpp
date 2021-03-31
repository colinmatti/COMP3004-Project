#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    currentMenu = new QStringList();
    empty = new QStringList();
    model = new QStringListModel(*currentMenu, NULL);
    currentIndex = model->index(0,0);
    ui->listView->setModel(model);

    // REPLACE WITH THERAPY TIMER
    countdown = 10;
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(on_timer_start()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_okButton_clicked()
{
    currentMenu = device.receive(ui->listView->currentIndex().row());

    model->setStringList(*currentMenu);
    currentIndex = model->index(0,0);

    ui->timer->setVisible(true);
    // For every second
    timer->start(1000);
}

void MainWindow::on_powerButton_clicked()
{
    if (device.poweredOn == false){
        currentMenu = device.receive(-1);
        model->setStringList(*currentMenu);
        ui->listView->setCurrentIndex(currentIndex);
        device.poweredOn = true;
    } else {
        device.poweredOn = false;
        model->setStringList(*empty);
    }
}

void MainWindow::on_downButton_clicked()
{
    if (currentIndex.row() >= currentMenu->size()-1) {
        currentIndex  = model->index(0,0);
    } else {
        currentIndex  = model->index(currentIndex.row()+1,0);
    }
    ui->listView->setCurrentIndex(currentIndex);
}

void MainWindow::on_upButton_clicked()
{
    if (currentIndex.row() <= 0) {
        currentIndex = model->index(currentMenu->size()-1,0);
    } else {
        currentIndex  = model->index(currentIndex.row()-1,0);
    }
    ui->listView->setCurrentIndex(currentIndex);
}

void MainWindow::on_rightButton_clicked()
{
    QString power = QString::number(device.increasePower());
    ui->powerLabel->setText(power);
}

void MainWindow::on_leftButton_clicked()
{
    QString power = QString::number(device.decreasePower());
    ui->powerLabel->setText(power);
}

void MainWindow::on_goBackButton_clicked()
{

}

void MainWindow::on_menuButton_clicked()
{
    if (device.poweredOn == true){
        model->setStringList(*empty);
        currentMenu = device.receive(-1);
        model->setStringList(*currentMenu);
        ui->listView->setCurrentIndex(currentIndex);
    }

}

void MainWindow::on_timer_start()
{
    // countdown will be taken from device.therapy.timer
    if (countdown < 0)
    {
        timer->stop();
    } else {
        ui->timer->display(countdown);
        countdown--;
    }

}
