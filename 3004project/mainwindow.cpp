#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    model = new QStringListModel();
    ui->warningLabel->setWordWrap(true);

    // Fetch view graph from device.
    currentView = device.mainMenu();

    // Instantiate timer.
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(on_timerStart()));

    powerOffDevice();
}

MainWindow::~MainWindow() {
    delete model;
    delete timer;
    delete ui;
}

/**
 * @brief When the OK button is clicked, navigate to the next view.
 */
void MainWindow::on_okButton_clicked() {
    // If the device is powered OFF, do nothing.
    if (!device.isPoweredOn()) { return; }

    // If the device is currently administering a treatment, do nothing.
    if (currentView->type() == "TreatmentView") { return; }

    MenuView* menuView = dynamic_cast<MenuView*>(currentView);
    currentView = menuView->children->at(currentSelectionIndex.row());

    if (currentView->type() == "TreatmentView" && device.isOnSkin()) {
        treatmentVisibility();
        countdown = currentView->getTherapy()->getTimer();
        ui->therapyLabel->setText("Frequency: " + QString::number(currentView->getTherapy()->getFrequency()) + "Hz");
        ui->powerLabel->setText(QString::number(device.resetPower()));
        timer->start(1000);
    } else if  (currentView->type() == "TreatmentView" && !device.isOnSkin()){
        ui->warningLabel->setText(ERROR_NO_SKIN);
        currentView = currentView->getParent();
    }
    else if (currentView->type() == "MenuView") {
        menuVisibility();
    }
}

/**
 * @brief When the power button is pressed, turn on or off the device.
 */
void MainWindow::on_powerButton_clicked() {
    !device.isPoweredOn() ? powerOnDevice() : powerOffDevice();
}

/**
 * @brief Updates the view and device to reflect device being powered ON.
 */
void MainWindow::powerOnDevice() {
    displayMainMenu();
    device.power();
}

/**
 * @brief Updates the view and device to reflect device being powered OFF.
 */
void MainWindow::powerOffDevice() {
    offVisibility();
    device.power();
    timer->stop();
}

/**
 * @brief Navigate down in menu options if on MenuView.
 */
void MainWindow::on_downButton_clicked() {
    // If we are not currently on a MenuView, do nothing.
    if (currentView->type() != "MenuView") { return; }

    // If we are currently at index 0, wrap around to end of the option list.
    int index = (currentSelectionIndex.row() + 1) % model->stringList().size();
    currentSelectionIndex = model->index(index);
    ui->listView->setCurrentIndex(currentSelectionIndex);
}

/**
 * @brief Navigate up in menu options if on MenuView.
 */
void MainWindow::on_upButton_clicked() {
    // If we are not currently on a MenuView, do nothing.
    if (currentView->type() != "MenuView") { return; }

    // If we are currently at index n, wrap around to beginning of the option list.
    int index = (currentSelectionIndex.row() + model->stringList().size() - 1) % model->stringList().size();
    currentSelectionIndex = model->index(index);
    ui->listView->setCurrentIndex(currentSelectionIndex);
}

/**
 * @brief Increases the device's power level by one.
 */
void MainWindow::on_rightButton_clicked() {
    if (!device.isPoweredOn()) { return; }

    QString power = QString::number(device.increasePower());
    ui->powerLabel->setText(power);
}

/**
 * @brief Decreases the device's power level by one.
 */
void MainWindow::on_leftButton_clicked() {
    if (!device.isPoweredOn()) { return; }

    QString power = QString::number(device.decreasePower());
    ui->powerLabel->setText(power);
}

/**
 * @brief Return to the previous screen when back button is pressed.
 * If previous screen does not exist, do nothing.
 */
void MainWindow::on_goBackButton_clicked() {
    if (currentView->type() == "TreatmentView" && ui->warningLabel->text() != WARNING_TREATMENT_RUNNING) {
        ui->warningLabel->setText(WARNING_TREATMENT_RUNNING);
        return;
    }
    View* parent = currentView->getParent();

    // If the parent does not exist, do nothing.
    if (parent == nullptr) { return; }
    currentView = parent;
    menuVisibility();
}

/**
 * @brief Returns view to reflect being on the main menu of the device.
 */
void MainWindow::on_menuButton_clicked() {
    if (!device.isPoweredOn()) { return; }
    if (currentView->type() == "TreatmentView" && ui->warningLabel->text() != WARNING_TREATMENT_RUNNING) {
        ui->warningLabel->setText(WARNING_TREATMENT_RUNNING);
        return;
    }
    // Stop timer?
    displayMainMenu();
}

/**
 * @brief Display and decrease countdown until countdown reaches zero.
 */
void MainWindow::on_timerStart() {
    if (countdown < 0) {
        timer->stop();
        // Return to menu screen after treatment ends
        currentView = currentView->getParent();
        menuVisibility();
    } else {
        ui->timer->display(countdown);
        countdown--;
    }
}

void MainWindow::on_onSkin_stateChanged(int checked) {
    if (checked == 2){
        device.applyOnSkin();
        if (currentView->type() == "TreatmentView") {
            ui->warningLabel->setText(NO_ERROR);
            timer->start();
        }
        cout <<  "SKIN DETECTED" << endl;
    } else {
        device.applyOnSkin();
        if (currentView->type() == "TreatmentView") {
            ui->warningLabel->setText(ERROR_NO_SKIN);
            timer->stop();
        }
        cout << "SKIN NOT DETECTED" << endl;
    }
}

/**
 * @brief Adds a therapy to treatment history if currently on treatment
 * screen and therapy has concluded.
 */
void MainWindow::on_addButton_clicked() {
    // If the device is not currently running a treatment, do nothing.
    if (currentView->type() != "TreatmentView") { return; }

    device.addToHistory(currentView->getTherapy());
}

/**
 * @brief Changes window view to display device main menu.
 */
void MainWindow::displayMainMenu() {
    // Fetch view graph from device.
    currentView = device.mainMenu();

    // Construct menu model for current menu view.
    model = new QStringListModel(currentView->constructMenu(), NULL);
    ui->listView->setModel(model);

    // Reset menu option index to 0.
    currentSelectionIndex = model->index(0);
    ui->listView->setCurrentIndex(currentSelectionIndex);

    menuVisibility();
}

/**
 * @brief Toggles UI to set components visible or invisible for a menu.
 */
void MainWindow::menuVisibility() {
    model->setStringList(currentView->constructMenu());
    currentSelectionIndex = model->index(0);
    ui->listView->setCurrentIndex(currentSelectionIndex);
    ui->warningLabel->setText(NO_ERROR);

    ui->listView->setVisible(true);
    ui->timer->setVisible(false);
    ui->powerLabel->setVisible(false);
    ui->powerLevelLabel->setVisible(false);
    ui->therapyLabel->setVisible(false);
}

/**
 * @brief Toggles UI to set components invisible for device powered OFF.
 */
void MainWindow::offVisibility() {
    ui->listView->setVisible(false);
    ui->timer->setVisible(false);
    ui->powerLabel->setVisible(false);
    ui->powerLevelLabel->setVisible(false);
    ui->therapyLabel->setVisible(false);
}

/**
 * @brief Toggles UI to set components visible or invisible for a treatment.
 */
void MainWindow::treatmentVisibility() {
    ui->powerLabel->setVisible(true);
    ui->powerLevelLabel->setVisible(true);
    ui->therapyLabel->setVisible(true);
    ui->timer->setVisible(true);
    ui->listView->setVisible(false);
    ui->warningLabel->setText(NO_ERROR);
}
