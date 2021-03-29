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
    stringList = new QStringList();
    empty = new QStringList();
    model = new QStringListModel(*stringList, NULL);
    currentIndex = model->index(0,0);
    ui->listView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_okButton_clicked()
{
    stringList = device.receive(ui->listView->currentIndex().row());

    model->setStringList(*stringList);
    currentIndex = model->index(0,0);
}

void MainWindow::on_powerButton_clicked()
{
    if (device.poweredOn == false){
        stringList = device.receive(-1);
        model->setStringList(*stringList);
        ui->listView->setCurrentIndex(currentIndex);
        device.poweredOn = true;
    } else {
        device.poweredOn = false;
        model->setStringList(*empty);
    }
}

void MainWindow::on_downButton_clicked()
{
    if (currentIndex.row() >= stringList->size()-1) {
        currentIndex  = model->index(0,0);
    } else {
        currentIndex  = model->index(currentIndex.row()+1,0);
    }
    ui->listView->setCurrentIndex(currentIndex);
}

void MainWindow::on_upButton_clicked()
{
    if (currentIndex.row() <= 0) {
        currentIndex = model->index(stringList->size()-1,0);
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
