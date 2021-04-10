#include "device.h"

Device::Device() :
    battery(new Battery()),
    powerLevel(1),
    poweredOn(false),
    treatmentRunning(false),
    attemptedQuitTreatment(false),
    activeError(NO_ERROR) {

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
    treatmentHistory = new QList<PreviousTreatment*>();

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
 * @return True if the device is now on skin, False otherwise.
 */
bool Device::applyOnSkin() {
    isOnSkin = !isOnSkin;
    return isOnSkin;
}

bool Device::maybeAddTreatmentToHistory() {
    if (activeTherapy == nullptr) {
        shouldAddTreatmentToHistory = false;
        return shouldAddTreatmentToHistory;
    }

    if (treatmentRunning) {
        shouldAddTreatmentToHistory = true;
        return shouldAddTreatmentToHistory;
    }

    if (shouldAddTreatmentToHistory) {
        addToHistory();
        shouldAddTreatmentToHistory = false;
    }

    activeTherapy = nullptr;
}

void Device::updateTimer() {
    activeTherapy->increaseTime();
}

/**
 * @brief Attempt to navigate down through the display menu.
 * @param index: the menu index to navigate down into.
 * @return the new view if successfully navigated, otherwise NULL.
 */
View* Device::navigateDown(int index) {
    if (!poweredOn) { return NULL; }
    View* newView = display->navigateDown(index);

    if (newView == NULL) { return newView; }

    if (newView->getType() == "TreatmentView") {
        startTreatment(newView->getTherapy());
        if (treatmentRunning) { return newView; }
        else { return NULL; }
    }
}

/**
 * @brief Increases the power level of the treatment by one, unless power is at max.
 * @return The current power level.
 */
int Device::increasePower() {
    if (!treatmentRunning) { return powerLevel; }
    if (++powerLevel > MAXPOWERLEVEL) { powerLevel = MAXPOWERLEVEL; }
    activeTherapy->increasePowerLevel();
    return powerLevel;
}

/**
 * @brief Decreases the power level of the treatment by one, unless power is at min.
 * @return The current power level.
 */
int Device::decreasePower() {
    if (!treatmentRunning) { return powerLevel; }
    if (--powerLevel < MINPOWERLEVEL) { powerLevel = MINPOWERLEVEL; }
    return powerLevel;
}

/**
 * @brief Adds a given therapy to treatment history.
 * @param The therapy to be added to treatment history.
 */
void Device::addToHistory() {
    treatmentHistory->append(activeTherapy);
    display->addHistoryToNavigation(activeTherapy);
}

/**
 * @brief Removes specified previousTreatment from therapy history.
 * @param previousTreatment: The treatment to be removed from history.
 */
void Device::removeFromHistory(HistoryView* historyView) {
    treatmentHistory->removeOne(historyView->getPreviousTreatment());
    display->removeHistoryFromNavigation(historyView);
}

/**
 * @brief Clears all previous treatments from therapy history.
 */
void Device::clearHistory() {
    display->clearHistoryNavigation();
    treatmentHistory->clear();
}

/**
 * @brief Powers on the device if powered off, otherwise powers on.
 */
bool Device::power() {
    poweredOn = !poweredOn;
    powerLevel = MINPOWERLEVEL;
    return poweredOn;
}

/**
 * @brief Attempts to start a treatment.
 * @return True if the treatment was started, False otherwise.
 */
bool Device::startTreatment(Therapy* therapy) {
    if (!isOnSkin) {
        activeError = ERROR_NO_SKIN;
        return false;
    }

    activeTherapy = new PreviousTreatment(therapy, MINPOWERLEVEL, 0);
    treatmentRunning = true;
    return true;
}

/**
 * @brief Attempts to stop a treatment.
 * @return True if the treatment was stopped, False otherwise.
 */
bool Device::stopTreatment() {
    if (!attemptedQuitTreatment) {
        attemptedQuitTreatment = true;
        return false;
    }

    treatmentRunning = false;
    attemptedQuitTreatment = false;
    powerLevel = MINPOWERLEVEL;
    return true;
}
