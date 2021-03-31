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
    ui->listView->setVisible(false);
    ui->timer->setVisible(false);

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
    cout  << "index" << ui->listView->currentIndex().row() << endl;
    if (device.poweredOn){
        *currentMenu = device.receive(ui->listView->currentIndex().data(Qt::DisplayRole).toString());
        if (currentMenu->contains("timer")){
            ui->listView->setVisible(false);
            ui->timer->setVisible(true);
            // For every second
            timer->start(1000);
        } else {
            //listview
            ui->listView->setVisible(true);
            ui->timer->setVisible(false);
            model->setStringList(*currentMenu);
            currentIndex = model->index(0,0);
            ui->listView->setCurrentIndex(currentIndex);
        }
    }
}

void MainWindow::on_powerButton_clicked()
{
    if (device.poweredOn == false){
        ui->listView->setVisible(true);
        *currentMenu = device.receive("on");
        model->setStringList(*currentMenu);
        currentIndex = model->index(0,0);
        ui->listView->setCurrentIndex(currentIndex);
        device.poweredOn = true;
    } else {
        device.poweredOn = false;
        model->setStringList(*empty);
        device.receive("off");
        ui->listView->setVisible(false);
        ui->timer->setVisible(false);
        timer->stop();
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
        currentIndex = model->index(currentIndex.row()-1,0);
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
        *currentMenu = device.receive("menu");
       // cout << "currentMenu" << device.receive("menu").at(0) << endl;
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



void MainWindow::on_onSkin_stateChanged(int checked)
{
    cout << "arg1" << checked << endl;
    if (checked == 2){
        device.onSkin = true;
        cout <<  "SKIN DETECTED" << endl;
    } else {
        device.onSkin = false;
        cout << "SKIN NOT DETECTED" << endl;
    }
}
