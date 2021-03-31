#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    //countdown = 10;
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
    if (device.isPoweredOn()){
        *currentMenu = device.receive(ui->listView->currentIndex().data(Qt::DisplayRole).toString());
        if (currentMenu->contains("timer")){
            ui->listView->setVisible(false);
            ui->timer->setVisible(true);
            QString name = currentMenu->at(1);
            countdown = currentMenu->at(2).toInt();
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
    if (device.isPoweredOn() == false){
        ui->powerLabel->setVisible(true);
        ui->powerLabel->setText("1");
        ui->listView->setVisible(true);
        *currentMenu = device.receive("on");
        model->setStringList(*currentMenu);
        currentIndex = model->index(0,0);
        ui->listView->setCurrentIndex(currentIndex);
        device.power();
    } else {
        device.power();
        model->setStringList(*empty);
        device.receive("off");
        ui->listView->setVisible(false);
        ui->timer->setVisible(false);
        timer->stop();
        ui->powerLabel->setVisible(false);
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
    if (device.isPoweredOn() == false){
        return;
    }
    else {
        QString power = QString::number(device.increasePower());
        ui->powerLabel->setText(power);
    }
}

void MainWindow::on_leftButton_clicked()
{
    if (device.isPoweredOn() == false){
        return;
    }
    else {
        QString power = QString::number(device.decreasePower());
        ui->powerLabel->setText(power);
    }
}

void MainWindow::on_goBackButton_clicked()
{
    if (device.isPoweredOn() == true){
        model->setStringList(*empty);
        *currentMenu = device.receive("menu");
        model->setStringList(*currentMenu);
        ui->listView->setCurrentIndex(currentIndex);
        ui->listView->setVisible(true);
        ui->timer->setVisible(false);
        // TODO: when treatment is running, send warning
    }
}

void MainWindow::on_menuButton_clicked()
{
    if (device.isPoweredOn() == true){
        model->setStringList(*empty);
        *currentMenu = device.receive("menu");
        model->setStringList(*currentMenu);
        ui->listView->setCurrentIndex(currentIndex);
        ui->listView->setVisible(true);
        ui->timer->setVisible(false);
        // TODO: when treatment is running, send warning
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
        device.applyOnSkin();
        cout <<  "SKIN DETECTED" << endl;
    } else {
        device.applyOnSkin();
        cout << "SKIN NOT DETECTED" << endl;
    }
}
