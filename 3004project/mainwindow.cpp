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
    bool willAddToHistory = device.maybeAddTreatmentToHistory();
    if (!willAddToHistory) { ui->warningLabel->setText(WARNING_NO_TREATMENT_RUNNING); }
}

/**
 * @brief When the OK button is clicked, navigate to the next view.
 */
void MainWindow::on_okButton_clicked() {
    View* currentView = device.navigateDown(currentSelectionIndex.row());
    if (currentView == NULL) {
        ui->warningLabel->setText(ERROR_NO_SKIN);
    } else if (currentView->getType() == "TreatmentView") {
        treatmentVisibility(currentView);
    } else if (currentView->getType() == "MenuView") {
        menuVisibility(currentView);
    }
}

/**
 * @brief When the power button is pressed, turn on or off the device.
 */
void MainWindow::on_powerButton_clicked() {
    // If the device is now ON, turn on main menu visibility.
    if (device.power()) { menuVisibility(device.getMainMenu()); }
    // Otherwise, toggle OFF visibility.
    else { offVisibility(); }
}

/**
 * @brief Navigate down in menu options if on MenuView.
 */
void MainWindow::on_downButton_clicked() {
    currentSelectionIndex = model->index((currentSelectionIndex.row() + 1) % model->stringList().size());
    ui->listView->setCurrentIndex(currentSelectionIndex);
}

/**
 * @brief Navigate up in menu options if on MenuView.
 */
void MainWindow::on_upButton_clicked() {
    currentSelectionIndex = model->index((currentSelectionIndex.row() + model->stringList().size() - 1) % model->stringList().size());
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
 * @brief Return to the previous screen when back button is pressed.
 * If previous screen does not exist, do nothing.
 */
void MainWindow::on_goBackButton_clicked() {
    navigateBackScreens(currentView->getParent());
}

/**
 * @brief Returns view to reflect being on the main menu of the device.
 */
void MainWindow::on_menuButton_clicked() {
    navigateBackScreens(device.getMainMenu());
}

/**
 * @brief Display and decrease countdown until countdown reaches zero.
 */
void MainWindow::on_timerStart() {
    if (countdown < 0) {
        treatmentEnded();
    } else {
        ui->timer->display(countdown--);
        device.updateTimer();
    }
}

/**
 * @brief Checks if the device is on the skin or off (currently simulated on admin console).
 * @param checked: When checked == 2, else error.
 */
void MainWindow::on_onSkin_stateChanged(int checked) {
    // Toggle device applied to skin.
    device.applyOnSkin();

    // If we're not currently in a treatment, return.
    if (!device.isTreatmentRunning()) { return; }

    if (checked == 2) {
        ui->warningLabel->setText(NO_ERROR);
        timer->start();
    } else {
        ui->warningLabel->setText(ERROR_NO_SKIN);
        timer->stop();
    }
}

/**
 * @brief Clears the entire history.
 */
void MainWindow::on_clearButton_clicked() {
    // If we're not on the history view, do nothing.
    if (currentView->getName() != "History") { return; }

    device.clearHistory();
    menuVisibility(currentView);
}

/**
 * @brief Deletes a single treatment history.
 */
void MainWindow::on_deleteButton_clicked() {
    // If we're not on the history view, do nothing.
    if (currentView->getName() != "History") { return; }

    // Fetch therapy history to delete and pass to device to delete.
    View* history = currentView->getChildren()->at(currentSelectionIndex.row());
    HistoryView* historyView = dynamic_cast<HistoryView*>(history);
    device.removeFromHistory(historyView);

    menuVisibility(currentView);
}


// ========================================
//
// PRIVATE HELPER FUNCTIONS
//
// ========================================


void MainWindow::navigateBackScreens(View* destination) {
    if (!device.isPoweredOn()) { return; }
    if (destination == nullptr) { return; }

    if (!device.isTreatmentRunning()) {
        menuVisibility(destination);
    } else {
        bool treatmentStopped = device.stopTreatment();
        if (treatmentStopped) {
            menuVisibility(destination);
            treatmentEnded();
        } else {
            ui->warningLabel->setText(WARNING_TREATMENT_RUNNING);
        }
    }
}

/**
 * @brief Notifies that treatment has ended or has been interrupted
 * and to add if required and stop timer.
 */
void MainWindow::treatmentEnded() {
    timer->stop();
    device.stopTreatment();
    menuVisibility(device.getMainMenu());
}

/**
 * @brief Updates menu view to navigate to specified option index.
 * @param index: the index to navigate to in the menu.
 */
void MainWindow::navigateMenu(int index) {
    if (currentView->getType() != "MenuView") { return; }

    currentSelectionIndex = model->index(index);
    ui->listView->setCurrentIndex(currentSelectionIndex);
}

/**
 * @brief Toggles UI to set components visible or invisible for a menu.
 */
void MainWindow::menuVisibility(View* menu) {    
    model->setStringList(menu->constructMenu());
    ui->listView->setModel(model);
    currentSelectionIndex = model->index(0);
    ui->listView->setCurrentIndex(currentSelectionIndex);
    ui->warningLabel->setText(device.getActiveError());

    // 📌 TO DO: Create a way to make sure to update battery as it depletes, and show it in main window, for now, it'll "change" for every menu change
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
    currentView = treatmentView;
    ui->powerLabel->setVisible(true);
    ui->powerLevelLabel->setVisible(true);
    ui->therapyLabel->setVisible(true);
    ui->timer->setVisible(true);
    ui->listView->setVisible(false);
    ui->warningLabel->setText(NO_ERROR);

    countdown = currentView->getTherapy()->getTimer();
    ui->therapyLabel->setText("Frequency: " + QString::number(currentView->getTherapy()->getFrequency()) + "Hz");
    ui->powerLabel->setText(QString::number(device.getPowerLevel()));
    timer->start(1000);
}
