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

    ui->warningLabel->setWordWrap(true);
    ui->listView->setModel(model);
    on();

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(on_timer_start()));
}

MainWindow::~MainWindow()
{
    delete empty;
    delete model;
    delete timer;
    delete ui;
}

void MainWindow::on_okButton_clicked()
{
    cout  << "index" << ui->listView->currentIndex().row() << endl;
    if (device.isPoweredOn()){
        *currentMenu = device.receive(ui->listView->currentIndex().data(Qt::DisplayRole).toString());
        if (currentMenu->contains("timer")){
            QString name = currentMenu->at(1);
            countdown = currentMenu->at(2).toInt();
            cout << "Starting treatment" << endl;
            // For every second
            timer->start(1000);
            onTreatment();
        } else if (currentMenu->contains("error")){
            cout << "Detected error" << endl;
            ui->warningLabel->setText(ERRSKIN);
        } else {
            cout << "options" << endl;
            model->setStringList(*currentMenu);
            on();
        }
    }
}

void MainWindow::on_powerButton_clicked()
{
    if (device.isPoweredOn() == false){
        *currentMenu = device.receive("on");
        model->setStringList(*currentMenu);
        device.power();
        on();
    } else {
        device.power();
        model->setStringList(*empty);
        device.receive("off");
        device.endTreatment();
        timer->stop();
        off();
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
    if (device.isPoweredOn() && device.getStatus() != NULL){
        QString power = QString::number(device.increasePower());
        ui->powerLabel->setText(power);
    }
}

void MainWindow::on_leftButton_clicked()
{
    if (device.isPoweredOn() && device.getStatus() != NULL){
        QString power = QString::number(device.decreasePower());
        ui->powerLabel->setText(power);
    }
}

void MainWindow::on_goBackButton_clicked()
{
    if (device.isPoweredOn() == true){
        if (device.getStatus() != NULL){
            ui->warningLabel->setText(ERRTREATMENTRUNNING);
        } else {
            model->setStringList(*empty);
            *currentMenu = device.receive("back");
            model->setStringList(*currentMenu);
            on();
        }
    }
}

void MainWindow::on_menuButton_clicked()
{
    if (device.isPoweredOn() == true){
        if (device.getStatus() != NULL){
            ui->warningLabel->setText(ERRTREATMENTRUNNING);
        } else {
            model->setStringList(*empty);
            *currentMenu = device.receive("menu");
            model->setStringList(*currentMenu);
            on();
        }
    }

}

void MainWindow::on_timer_start()
{
    if (countdown < 0) {
        timer->stop();
        device.endTreatment();
        on();
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
        if (device.getStatus() !=  NULL){
            timer->start();
        }
        ui->warningLabel->setText("No Error");
        cout <<  "SKIN DETECTED" << endl;
    } else {
        device.applyOnSkin();
        if (device.getStatus() !=  NULL){
            ui->warningLabel->setText(ERRSKIN);
            timer->stop();
        }
        cout << "SKIN NOT DETECTED" << endl;
    }
}

void MainWindow::on_addButton_clicked()
{
    device.receive("add");
}

void MainWindow::off(){
    ui->powerLabel->setVisible(false);
    ui->powerLevelLabel->setVisible(false);
    ui->timer->setVisible(false);
    ui->listView->setVisible(false);
    ui->warningLabel->setText(NOERR);
}

void MainWindow::onTreatment(){
    ui->powerLabel->setVisible(true);
    ui->powerLevelLabel->setVisible(true);
    ui->timer->setVisible(true);
    ui->listView->setVisible(false);
    ui->warningLabel->setText(NOERR);
}

void MainWindow::on(){
    currentIndex = model->index(0,0);
    ui->listView->setCurrentIndex(currentIndex);
    ui->powerLabel->setVisible(false);
    ui->powerLevelLabel->setVisible(false);
    ui->timer->setVisible(false);
    ui->listView->setVisible(true);
    ui->warningLabel->setText(NOERR);
}
