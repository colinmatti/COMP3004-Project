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
QStringList Device::receive(QString request)
{
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
            //history->append(treatmentHistory->at(i).therapy.frequency); // append how we want output to look
        }
        return *history;
    } else if (page == 4){
        // runTreatment(request) could be the below stuff!!
        if (display->frequency->contains(request)){
            for (int i = 0; i < frequencies->size(); i++){
                if (frequencies->at(i)->frequency == request.toInt()){
                    float f = frequencies->at(i)->frequency;
                    int t = frequencies->at(i)->timer;
                    return (QStringList() << "timer" << QString::number(f) << QString::number(t)); // and data of treatment
                }
            }
            //float f = frequencies->at(request.toInt()).frequency;
            //int t = frequencies->at(request.toInt()).timer;
        }
        if (display->program->contains(request)){
            for (int i = 0; i < programs->size(); i++){
                if (programs->at(i)->name == request){
                    QString n = programs->at(i)->name;
                    int t = frequencies->at(i)->timer;
                    return (QStringList() << "timer" << n << QString::number(t)); // and data of treatment
                }
            }
            //QString n = programs->at(request.toInt()).name;
            //int t = programs->at(request.toInt()).timer;
        }
    } /*else if (page == 5){
        return (QStringList() << "power" << QString::number(powerLevel));
    }*/
    return QStringList();
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
void Device::runTreatment()
{
    int timePassed = 1;
    battery->decreaseLevel(powerLevel,timePassed);
}

/**
 * @brief Adds a given therapy to treatment history.
 * @param The therapy to be added to treatment history.
 */
void Device::addToHistory(Therapy* therapy) {
    PreviousTreatment* newTreatment = new PreviousTreatment(therapy);
    treatmentHistory->append(newTreatment);
}
