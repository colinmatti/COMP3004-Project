#include "device.h"

#include <string>
#include <iostream>
#include <array>
#include <QList>

Device::Device()
{
    battery = new Battery();
    poweredOn = false;
    powerLevel = 1;

    // Instantiate all preset therapies.
    programs = new QList<Program>();
    frequencies = new QList<Frequency>();

    // Create and append programs.
    Program throat = Program(QString("Throat"), 10, 600, 30);
    programs->append(throat);

    Program nausea = Program(QString("Nausea"), 15, 240, 10);
    programs->append(nausea);

    Program chlamydia = Program(QString("Chlamydia"), 25, 1200, 80);
    programs->append(chlamydia);

    Program diarrhea = Program(QString("Diarrhea"), 5, 120, 65);
    programs->append(diarrhea);

    // Create and append frequencies.
    Frequency five = Frequency(5, 300, 50);
    frequencies->append(five);

    Frequency ten = Frequency(10, 300, 50);
    frequencies->append(ten);

    Frequency fifteen = Frequency(15, 300, 50);
    frequencies->append(fifteen);

    Frequency twenty = Frequency(20, 300, 50);
    frequencies->append(twenty);

    // Instantiate empty therapy history.
    treatmentHistory = new QList<PreviousTreatment>();

    display = new Display(frequencies, programs);
}

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
        //create a QStringList of the history, and return it
        //return treatmentHistory;
    } else if (page == 4){
        // runTreatment(request)
        return (QStringList() << "timer"); // and data of treatment
    } /*else if (page == 5){
        return (QStringList() << "power" << QString::number(powerLevel));
    }*/
    return QStringList();
}

int Device::increasePower()
{
    // If treatment is running
    if (powerLevel >= MAXPOWERLEVEL){
        return MAXPOWERLEVEL;
    }
    powerLevel += 1;
    return powerLevel;
}

int Device::decreasePower()
{
    //If treatment is running
    if (powerLevel <= MINPOWERLEVEL){
        return MINPOWERLEVEL;
    }
    powerLevel -= 1;
    return powerLevel;
}

void Device::addToHistory(Therapy* therapy)
{
    PreviousTreatment newTreatment = PreviousTreatment(therapy);
    treatmentHistory->append(newTreatment);
}

Device::~Device()
{
}

void Device::updateBattery(int currPwrLvl, int time)
{
    if (time > 0) {
        battery->decreaseLevel(currPwrLvl*time);
    }
}

int Device::runTreatment () {return 0;}

