#include "device.h"

Device::Device() {
    battery = new Battery();
    poweredOn = false;
    powerLevel = 1;

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

/**
 * @brief Handles a request made by the main window requesting information about the device.
 * @param request: request made by main window.
 * @return a string...
 */
QStringList Device::receive(QString request) {
    int page = display->updateDisplay(request);
    cout << "page" << page << endl;
    if (page == 0){
        return *display->menu;
    } else if (page == 1){
        return *display->frequency;
    } else if (page == 2){
        return *display->program;
    } else if (page == 3){
        QStringList *history = new QStringList();
        for (int i = 0; i < treatmentHistory->size(); i++){
            QString str = treatmentHistory->at(i)->date.toString("yyyy/MM/dd");
            str.append("---");
            str.append(QString::number(treatmentHistory->at(i)->therapy->getFrequency()));
            history->append(str);
        }
        return *history;
    } else if (page == 4){
        // runTreatment(request) could be the below stuff!!
        if (display->frequency->contains(request)){
            for (int i = 0; i < frequencies->size(); i++){
                if (frequencies->at(i)->getFrequency() == request.toInt()){
                    float f = frequencies->at(i)->getFrequency();
                    int t = frequencies->at(i)->getTimer();
                    status = frequencies->at(i);
                    return (QStringList() << "timer" << QString::number(f) << QString::number(t)); // and data of treatment
                }
            }
        }
        if (display->program->contains(request)){
            for (int i = 0; i < programs->size(); i++){
                if (programs->at(i)->getName() == request){
                    QString n = programs->at(i)->getName();
                    int t = frequencies->at(i)->getTimer();
                    status = programs->at(i);
                    return (QStringList() << "timer" << n << QString::number(t)); // and data of treatment
                }
            }
        }
    }
    if (request == "add"){
        if (status != NULL){
            cout << "adding to history" << endl;
            addToHistory(status);
        }
    }
    return QStringList();
}

Therapy* Device::getStatus(){
    return status;
}


/**
 * @brief Increases the power level of the treatment by one, unless power is at max.
 * @return The current power level.
 */
int Device::increasePower() {
    // If treatment is running
    if (powerLevel == MAXPOWERLEVEL){
        return MAXPOWERLEVEL;
    }
    powerLevel += 1;
    return powerLevel;
}

/**
 * @brief Decreases the power level of the treatment by one, unless power is at min.
 * @return The current power level.
 */
int Device::decreasePower() {
    //If treatment is running
    if (powerLevel == MINPOWERLEVEL){
        return MINPOWERLEVEL;
    }
    powerLevel -= 1;
    return powerLevel;
}

/**
 * @brief performs a treatment.
 * @param none.
 */
void Device::runTreatment() {
    int timePassed = 1;
    battery->decreaseLevel(powerLevel,timePassed);
}

/**
 * @brief treatment has ended.
 * @param none.
 */
void Device::endTreatment() {
    status = NULL;
}

/**
 * @brief Adds a given therapy to treatment history.
 * @param The therapy to be added to treatment history.
 */
void Device::addToHistory(Therapy* therapy) {
    PreviousTreatment* newTreatment = new PreviousTreatment(therapy);
    treatmentHistory->append(newTreatment);
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
