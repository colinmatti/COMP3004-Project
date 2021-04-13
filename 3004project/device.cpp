#include "device.h"

Device::Device() :
    battery(new Battery()),
    powerLevel(1),
    poweredOn(false),
    treatmentRunning(false),
    attemptedQuitTreatment(false),
    timer(new QTimer()),
    activeError(NO_ERROR),
    notifiedLowBattery(false) {

    // Instantiate all preset therapies.
    programs = new QList<Program*>();
    frequencies = new QList<Frequency*>();

    // Create and append programs.
    Program* throat = new Program(QString("Throat"), 10, 600);
    programs->append(throat);

    Program* nausea = new Program(QString("Nausea"), 15, 240);
    programs->append(nausea);

    Program* chlamydia = new Program(QString("Chlamydia"), 25, 1200);
    programs->append(chlamydia);

    Program* diarrhea = new Program(QString("Diarrhea"), 5, 120);
    programs->append(diarrhea);

    // Create and append frequencies.
    Frequency* five = new Frequency(5, 50);
    frequencies->append(five);

    Frequency* ten = new Frequency(10, 50);
    frequencies->append(ten);

    Frequency* fifteen = new Frequency(15, 50);
    frequencies->append(fifteen);

    Frequency* twenty = new Frequency(20, 50);
    frequencies->append(twenty);

    // Instantiate empty therapy history.
    treatmentHistory = new QList<ActiveTreatment*>();

    // Instantiate the display.
    display = new Display(frequencies, programs);
}

Device::~Device() {
    qDeleteAll(*programs);
    qDeleteAll(*frequencies);
    qDeleteAll(*treatmentHistory);
  
    delete display;
    delete battery;
    delete programs;
    delete frequencies;
    delete treatmentHistory;
}

/**
 * @brief Applies device to skin if off skin, otherwise removes from skin.
 * @return True if the treatment is running, False otherwise.
 */
bool Device::applyOnSkin() {
    isOnSkin = !isOnSkin;

    // If the device is now ON the skin, remove any active errors.
    if (isOnSkin && treatmentRunning) {
        timer->start();
        activeError = NO_ERROR;
    }

    // If the device is now OFF the skin, warn that treatment is running.
    else if (!isOnSkin && treatmentRunning) {
        timer->stop();
        activeError = WARNING_TREATMENT_RUNNING;
    }

    return isOnSkin;
}

/**
 * @brief Plan to add treatment to history if a therapy is ongoing.
 * @return True if we will add treatment to history, False otherwise.
 */
bool Device::addTreatmentToHistory() {
    if (treatmentRunning) { shouldAddTreatmentToHistory = true; }
    else if (poweredOn) { activeError = WARNING_NO_TREATMENT_RUNNING; }
    return shouldAddTreatmentToHistory;
}

/**
 * @brief Increase elapsed therapy time by 1 if a therapy is ongoing.
 */
int Device::updateTimer() {
    // If there's no active therapy, do nothing.
    if (!treatmentRunning) { return -1; }

    activeTherapy->increaseTime();

    if (!activeTherapy->isOngoing()) { stopTreatment(); }
    return activeTherapy->timeRemaining();
}

/**
 * @brief Decreases the battery level for one second passed if a therapy is ongoing.
 * @return the updated battery level if decrease successful, otherwise -1.
 */
float Device::updateBattery() {
    // If there's no active therapy, do nothing.
    if (!treatmentRunning) { return -1; }

    float batteryLevel = battery->decreaseBatteryLevel(powerLevel);

    // If the battery is low and we have not yet notified the user, notify the user.
    if (battery->isLow() && !notifiedLowBattery) {
        activeError = WARNING_LOW_BATT;
        notifiedLowBattery = true;
    }

    return batteryLevel;
}

/**
 * @brief Attempt to navigate down through the display menu.
 * @return the new view if successfully navigated, otherwise NULL.
 */
View* Device::navigateDown() {
    // If the device is powered OFF, do nothing.
    if (!poweredOn) { return NULL; }

    // Attempt to navigate down through the display menu.
    View* newView = display->navigateDown();

    if (newView == NULL) { return NULL; }

    // If we navigate to a treatment, attempt to start a treatment.
    if (newView->getType() == "TreatmentView") {
        startTreatment(newView->getTherapy());

        // If the treatment failed to start, navigate back to menu.
        if (!treatmentRunning) {
            display->navigateUp();
            return NULL;
        }
    }

    return newView;
}

/**
 * @brief Attempt to navigate to the main menu.
 * @return the main menu view if successfully navigated, otherwise NULL.
 */
View* Device::navigateToMenu() {
    // If the device is powered OFF, do nothing.
    if (!poweredOn) { return NULL; }

    // Attempt to stop any running treatments.
    stopTreatment();
    if (treatmentRunning) { return NULL; }

    return display->navigateToMenu();
}

/**
 * @brief Attempt to navigate up through the display menu.
 * @return the new view if successfully navigated, otherwise NULL.
 */
View* Device::navigateUp() {
    // If the device is powered OFF, do nothing.
    if (!poweredOn) { return NULL; }

    // Attempt to stop any running treatments.
    stopTreatment();
    if (treatmentRunning) { return NULL; }

    return display->navigateUp();
}

/**
 * @brief Get the current display view of the device.
 * @return the current view.
 */
View* Device::getCurrentView() {
    return display->getCurrentView();
}

/**
 * @brief Increases the power level of the treatment by one, unless power is at MAX.
 * @return the current power level.
 */
int Device::increasePower() {
    // If there's no treatment running, do nothing
    if (!treatmentRunning) { return powerLevel; }

    // Increment the power level. If it exceeds the MAXPOWERLEVEL, set it to the max.
    if (++powerLevel > MAXPOWERLEVEL) { powerLevel = MAXPOWERLEVEL; }

    // Update the max power level of the active therapy.
    activeTherapy->increasePowerLevel(powerLevel);

    return powerLevel;
}

/**
 * @brief Decreases the power level of the treatment by one, unless power is at MIN.
 * @return the current power level.
 */
int Device::decreasePower() {
    // If there's no treatment running, do nothing
    if (!treatmentRunning) { return powerLevel; }

    // Decrement the power level. If it exceeds the MINPOWERLEVEL, set it to the min.
    if (--powerLevel < MINPOWERLEVEL) { powerLevel = MINPOWERLEVEL; }

    return powerLevel;
}

/**
 * @brief Adds the active therapy to treatment history.
 */
void Device::addToHistory() {
    treatmentHistory->append(activeTherapy);
    display->addHistoryToNavigation(activeTherapy);

    shouldAddTreatmentToHistory = false;
    activeTherapy = nullptr;
}

/**
 * @brief Removes previousTreatment at specified index from therapy history.
 * @return the updated view without specified history if successful, otherwise NULL.
 */
View* Device::removeFromHistory() {
    // Attempt to remove previous treatment from history navigation.
    HistoryView* removedHistoryView = display->removeHistoryFromNavigation();

    if (removedHistoryView == NULL) { return NULL; }

    // Remove previous treatment from treatment history if successful.
    treatmentHistory->removeOne(removedHistoryView->getPreviousTreatment());
    return getCurrentView();
}

/**
 * @brief Clears all previous treatments from therapy history.
 * @return the updated view without histories if successful, otherwise NULL.
 */
View* Device::clearHistory() {
    // Attempt to clear history navigation.
    bool clearedHistory = display->clearHistoryNavigation();

    if (!clearedHistory) { return NULL; }

    // Clear treatment history if successful.
    treatmentHistory->clear();
    return display->getCurrentView();
}

/**
 * @brief Powers ON the device if currently OFF, otherwise powers OFF.
 */
bool Device::power() {
    poweredOn = !poweredOn;

    // Stop any active treatments.
    stopTreatment();

    display->navigateToMenu();
    return poweredOn;
}

/**
 * @brief Attempts to start a treatment.
 * @param therapy: the therapy treatment we wish to start.
 * @return True if the treatment was started, False otherwise.
 */
bool Device::startTreatment(Therapy* therapy) {
    // If the treatment is already running, do nothing.
    if (treatmentRunning) { return false; }

    // If device is not on skin, update error and return False.
    if (!isOnSkin) {
        activeError = ERROR_NO_SKIN;
        return false;
    }

    // Create an active therapy.
    activeTherapy = new ActiveTreatment(therapy, MINPOWERLEVEL, 0);

    timer->start(1000);
    treatmentRunning = true;
    return true;
}

/**
 * @brief Attempts to stop a treatment.
 * @return True if the treatment was stopped, False otherwise.
 */
bool Device::stopTreatment() {
    // If the treatment is already not running, do nothing.
    if (!treatmentRunning) { return true; }

    // If the timer is still going and the user has not yet attempted to quit therapy.
    if (activeTherapy->isOngoing() && !attemptedQuitTreatment && poweredOn) {
        activeError = WARNING_TREATMENT_RUNNING;
        attemptedQuitTreatment = true;
        return false;
    }

    // Add treatment to history if user previously asked to.
    if (shouldAddTreatmentToHistory) { addToHistory(); }

    timer->stop();
    treatmentRunning = false;
    attemptedQuitTreatment = false;
    powerLevel = MINPOWERLEVEL;
    activeError = NO_ERROR;

    return true;
}
