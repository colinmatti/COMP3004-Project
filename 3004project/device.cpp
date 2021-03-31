#include "device.h"

#include <string>
#include <iostream>
#include <array>
#include <QList>

Device::Device()
{
    poweredOn = false;
    powerLevel = 0;
    minPowerLevel = 0; // constant?
    maxPowerLevel = 100; // constant?
    display = new Display();

    // Instantiate all preset therapies.
    programs = new QList<Program>();
    frequencies = new QList<Frequency>();
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
        return *display->programmed;
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
    if (powerLevel >= maxPowerLevel){
        return powerLevel;
    }
    powerLevel += 1;
    return powerLevel;
}

int Device::decreasePower()
{
    //If treatment is running
    if (powerLevel <= minPowerLevel){
        return powerLevel;
    }
    powerLevel -= 1;
    return powerLevel;
}

Device::~Device()
{
}
