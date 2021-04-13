#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);
    ui->warningLabel->setWordWrap(true);
    ui->batteryLabel->setWordWrap(true);

    connect(device.getTimer(), SIGNAL(timeout()), this, SLOT(on_timerStart()));

    offVisibility();
}

MainWindow::~MainWindow() {
    delete ui;
}


// ========================================
//
// SLOTS
//
// ========================================


/**
 * @brief Attempt to add active therapy to history if therapy ongoing.
 */
void MainWindow::on_addButton_clicked() {
    // Attempt to add the ongoing treatment to history.
    bool willAddToHistory = device.addTreatmentToHistory();

    // If adding to history failed, show warning.
    if (!willAddToHistory) { ui->warningLabel->setText(device.getActiveError()); }
}

/**
 * @brief Attempt to navigate down the menu when OK button clicked.
 */
void MainWindow::on_okButton_clicked() {
    // Attempt to navigate down the menu.
    View* currentView = device.navigateDown();

    // If navigation failed, show warning. Otherwise, change view.
    if (currentView == NULL) {
        ui->warningLabel->setText(device.getActiveError());
        ui->listView->setCurrentIndex(device.resetIndex());
    } else if (currentView->getType() == "TreatmentView") {
        treatmentVisibility(currentView);
    } else if (currentView->getType() == "MenuView") {
        menuVisibility();
    }
}

/**
 * @brief Attempt to navigate up the menu when BACK button clicked.
 */
void MainWindow::on_goBackButton_clicked() {
    // Attempt to navigate up the menu.
    View* currentView = device.navigateUp();

    // If navigation failed, show warning. Otherwise, change view.
    if (currentView == NULL) {
        ui->warningLabel->setText(device.getActiveError());
    } else if (currentView->getType() == "MenuView") {
        menuVisibility();
    }
}

/**
 * @brief Attempt to navigate to the main menu when MENU button clicked.
 */
void MainWindow::on_menuButton_clicked() {
    // Attempt to navigate to the main menu.
    View* currentView = device.navigateToMenu();

    // If navigation failed, show warning. Otherwise, change view.
    if (currentView == NULL) {
        ui->warningLabel->setText(device.getActiveError());
    } else if (currentView->getType() == "MenuView") {
        menuVisibility();
    }
}

/**
 * @brief When the power button is pressed, turn on or off the device.
 */
void MainWindow::on_powerButton_clicked() {
    // If the device is now ON, turn on main menu visibility.
    if (device.power()) {
        device.navigateToMenu();
        menuVisibility();
    }

    // Otherwise, toggle OFF visibility.
    else { offVisibility(); }
}

/**
 * @brief Navigate down in menu options.
 */
void MainWindow::on_downButton_clicked() {
    ui->listView->setCurrentIndex(device.decreaseIndex());
}

/**
 * @brief Navigate up in menu options.
 */
void MainWindow::on_upButton_clicked() {
    ui->listView->setCurrentIndex(device.increaseIndex());
}

/**
 * @brief Increases the device's power level by one.
 */
void MainWindow::on_rightButton_clicked() {
    QString power = QString::number(device.increasePower());
    ui->powerLabel->setText(power);
}

/**
 * @brief Decreases the device's power level by one.
 */
void MainWindow::on_leftButton_clicked() {
    QString power = QString::number(device.decreasePower());
    ui->powerLabel->setText(power);
}

/**
 * @brief Display and decrease countdown until countdown reaches zero.
 */
void MainWindow::on_timerStart() {
    int timeRemaining = device.updateTimer();

    // Updates the battery and formats the float value to round up to nearest whole number.
    float batteryLevel = device.updateBattery();
    ui->batteryLabel->setText(QString::number(batteryLevel, 'f', 0));

    ui->timer->display(timeRemaining);
    ui->warningLabel->setText(device.getActiveError());
}

/**
 * @brief Checks if the device is on the skin or off (currently simulated on admin console).
 */
void MainWindow::on_onSkin_stateChanged() {
    device.applyOnSkin();
    ui->warningLabel->setText(device.getActiveError());
}

/**
 * @brief Clears the entire history.
 */
void MainWindow::on_clearButton_clicked() {
    View* currentView = device.clearHistory();
    if (currentView == NULL) { return; }
    menuVisibility();
}

/**
 * @brief Deletes a single treatment history.
 */
void MainWindow::on_deleteButton_clicked() {
    View* currentView = device.removeFromHistory();
    if (currentView == NULL) { return; }
    menuVisibility();
}

/**
 * @brief Charges the battery to 100%
 */
void MainWindow::on_chargeBatteryButton_clicked()
{
    device.chargeBattery();

    float batteryLevel = device.updateBattery();
    ui->batteryLabel->setText(QString::number(batteryLevel, 'f', 0));
}


// ========================================
//
// PRIVATE HELPER FUNCTIONS
//
// ========================================


/**
 * @brief Toggles UI to set components visible or invisible for a menu.
 */
void MainWindow::menuVisibility() {
    ui->listView->setModel(device.getModel());
    ui->listView->setCurrentIndex(device.resetIndex());

    ui->warningLabel->setText(device.getActiveError());

    ui->batteryLabel->setText(QString::number(device.getBatteryLevel(), 'f', 0));

    ui->listView->setVisible(true);
    ui->timer->setVisible(false);
    ui->powerLabel->setVisible(false);
    ui->powerLevelLabel->setVisible(false);
    ui->therapyLabel->setVisible(false);
    ui->batteryLabel->setVisible(true);
    ui->warningLabel->setVisible(true);
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
    ui->batteryLabel->setVisible(false);
    ui->warningLabel->setVisible(false);
}

/**
 * @brief Toggles UI to set components visible or invisible for a treatment.
 */
void MainWindow::treatmentVisibility(View* treatmentView) {
    ui->powerLabel->setVisible(true);
    ui->powerLevelLabel->setVisible(true);
    ui->therapyLabel->setVisible(true);
    ui->timer->setVisible(true);
    ui->listView->setVisible(false);
    ui->warningLabel->setText(device.getActiveError());

    ui->timer->display(treatmentView->getTherapy()->getTimer());
    ui->therapyLabel->setText("Frequency: " + QString::number(treatmentView->getTherapy()->getFrequency()) + "Hz");
    ui->powerLabel->setText(QString::number(device.getPowerLevel()));
}

