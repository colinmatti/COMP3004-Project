#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    model(new QStringListModel()),
    timer(new QTimer()),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);
    ui->warningLabel->setWordWrap(true);
    ui->batteryLabel->setWordWrap(true);

    connect(timer, SIGNAL(timeout()), this, SLOT(on_timerStart()));

    offVisibility();
}

MainWindow::~MainWindow() {
    delete model;
    delete timer;
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
    View* currentView = device.navigateDown(currentSelectionIndex.row());

    // If navigation failed, show warning. Otherwise, change view.
    if (currentView == NULL) {
        ui->warningLabel->setText(device.getActiveError());
    } else if (currentView->getType() == "TreatmentView") {
        treatmentVisibility(currentView);
    } else if (currentView->getType() == "MenuView") {
        menuVisibility(currentView);
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
        menuVisibility(currentView);
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
        menuVisibility(currentView);
    }
}

/**
 * @brief When the power button is pressed, turn on or off the device.
 */
void MainWindow::on_powerButton_clicked() {
    // If the device is now ON, turn on main menu visibility.
    if (device.power()) { menuVisibility(device.navigateToMenu()); }

    // Otherwise, toggle OFF visibility.
    else { offVisibility(); }
}

/**
 * @brief Navigate down in menu options.
 */
void MainWindow::on_downButton_clicked() {
    if (currentSelectionIndex.row() < 0) { return; }

    int newIndex = (currentSelectionIndex.row() + 1) % model->stringList().size();

    currentSelectionIndex = model->index(newIndex);
    ui->listView->setCurrentIndex(currentSelectionIndex);
}

/**
 * @brief Navigate up in menu options.
 */
void MainWindow::on_upButton_clicked() {
    if (currentSelectionIndex.row() < 0) { return; }

    int newIndex = (currentSelectionIndex.row() + model->stringList().size() - 1) % model->stringList().size();

    currentSelectionIndex = model->index(newIndex);
    ui->listView->setCurrentIndex(currentSelectionIndex);
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
    // If countdown reaches 0, stop the treatment and retreat to menu.
    if (countdown < 0) {
        device.stopTreatment();
        menuVisibility(device.getCurrentView());
    }

    // Otherwise, decrement counter.
    else {
        ui->timer->display(countdown--);
        device.updateTimer();

        // Update the battery level every second.
        float batteryLevel = device.updateBattery();
        // Formats the float value to round up to nearest whole number.
        ui->batteryLabel->setText(QString::number(batteryLevel, 'f', 0));

        ui->warningLabel->setText(device.getActiveError());
    }
}

/**
 * @brief Checks if the device is on the skin or off (currently simulated on admin console).
 * @param checked: When checked == 2, else error.
 */
void MainWindow::on_onSkin_stateChanged(int checked) {
    // Toggle device applied to skin.
    bool treatmentRunning = device.applyOnSkin();

    // If device is NOT running a treatment, do nothing
    if (!treatmentRunning) { return; }

    ui->warningLabel->setText(device.getActiveError());

    // If the treatment is running and the device is ON skin, resume timer.
    if (checked == 2) { timer->start(); }
    // If the treatment is running and the device is OFF skin, pause timer.
    else { timer->stop(); }
}

/**
 * @brief Clears the entire history.
 */
void MainWindow::on_clearButton_clicked() {
    View* currentView = device.clearHistory();
    if (currentView == NULL) { return; }
    menuVisibility(currentView);
}

/**
 * @brief Deletes a single treatment history.
 */
void MainWindow::on_deleteButton_clicked() {
    View* currentView = device.removeFromHistory(currentSelectionIndex.row());
    if (currentView == NULL) { return; }
    menuVisibility(currentView);
}


// ========================================
//
// PRIVATE HELPER FUNCTIONS
//
// ========================================


/**
 * @brief Toggles UI to set components visible or invisible for a menu.
 */
void MainWindow::menuVisibility(View* menu) {
    timer->stop();
    model->setStringList(menu->constructMenu());
    ui->listView->setModel(model);
    currentSelectionIndex = model->index(0);
    ui->listView->setCurrentIndex(currentSelectionIndex);
    ui->warningLabel->setText(device.getActiveError());

    ui->batteryLabel->setText(QString::number(device.getBatteryLevel()));

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

    countdown = treatmentView->getTherapy()->getTimer();

    ui->therapyLabel->setText("Frequency: " + QString::number(treatmentView->getTherapy()->getFrequency()) + "Hz");
    ui->powerLabel->setText(QString::number(device.getPowerLevel()));

    timer->start(1000);
}
