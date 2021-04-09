#include "device.h"

Device::Device() : powerLevel(1), currentMaxPower(1), poweredOn(true), battery(new Battery()) {
    // Instantiate all preset therapies.
    programs = new QList<Program*>();
    frequencies = new QList<Frequency*>();

    // Create and append programs.
    Program* throat = new Program(QString("Throat"), 10, 600, 30);
    programs->append(throat);

    Program* nausea = new Program(QString("Nausea"), 15, 240, 10);
    programs->append(nausea);

    Program* chlamydia = new Program(QString("Chlamydia"), 25, 1200, 80);
    programs->append(chlamydia);

    Program* diarrhea = new Program(QString("Diarrhea"), 5, 120, 65);
    programs->append(diarrhea);

    // Create and append frequencies.
    Frequency* five = new Frequency(5, 300, 50);
    frequencies->append(five);

    Frequency* ten = new Frequency(10, 300, 50);
    frequencies->append(ten);

    Frequency* fifteen = new Frequency(15, 300, 50);
    frequencies->append(fifteen);

    Frequency* twenty = new Frequency(20, 300, 50);
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

View* Device::mainMenu() { return display->mainMenu; }

/**
 * @brief Increases the power level of the treatment by one, unless power is at max.
 * @return The current power level.
 */
int Device::increasePower() {
    if (powerLevel == MAXPOWERLEVEL){
        return MAXPOWERLEVEL;
    }
    powerLevel += 1;
    if (powerLevel > currentMaxPower){
        currentMaxPower = powerLevel;
    }
    return powerLevel;
}

/**
 * @brief Decreases the power level of the treatment by one, unless power is at min.
 * @return The current power level.
 */
int Device::decreasePower() {
    if (powerLevel == MINPOWERLEVEL){
        return MINPOWERLEVEL;
    }
    powerLevel -= 1;
    return powerLevel;
}
int Device::resetPower() {
    powerLevel = MINPOWERLEVEL;
    currentMaxPower = MINPOWERLEVEL;
    return powerLevel;
}
/**
 * @brief Returns the current treatment's max power level.
 */
int Device::getCurrentMaxPower(){
    return currentMaxPower;
}

/**
 * @brief Adds a given therapy to treatment history.
 * @param The therapy to be added to treatment history.
 */
void Device::addToHistory(Therapy* therapy, int powerLevel, int duration) {
    PreviousTreatment* newTreatment = new PreviousTreatment(therapy, powerLevel, duration);
    treatmentHistory->append(newTreatment);
    display->addHistoryToNavigation(newTreatment);
}

/**
 * @brief Removes specified previousTreatment from therapy history.
 * @param previousTreatment: The treatment to be removed from history.
 */
void Device::removeFromHistory(HistoryView* historyView) {
    treatmentHistory->removeOne(historyView->getPreviousTreatment());
    display->removeHistoryFromNavigation(historyView);
}

void Device::clearHistory() {
    display->clearHistoryNavigation();
    treatmentHistory->clear();
}

/**
 * @brief Gets whether the device is currently powered on.
 * @return True if powered on, False otherwise.
 */
bool Device::isPoweredOn() { return poweredOn; }

/**
 * @brief Gets whether the device is currently on the skin.
 * @return True if on skin, False otherwise.
 */
bool Device::isOnSkin() { return onSkin; }

/**
 * @brief Powers on the device if powered off, otherwise powers on.
 */
void Device::power() {
    poweredOn = !poweredOn;
    powerLevel = 1;
}

/**
 * @brief Applies device to skin if off skin, otherwise removes from skin.
 */
void Device::applyOnSkin() { onSkin = !onSkin; }

/**
 * @brief Gets the battery level.
 * @return integer value of the battery's level.
 */
int Device::batteryLevel() { battery->getBatteryLevel(); }
