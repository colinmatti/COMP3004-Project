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

    // Instantiate all preset therapies.
    programs = new QList<Program>();
    frequencies = new QList<Frequency>();
}

QList<Therapy>* Device::receive(int request)
{
    if (request == -1){
        return display->menu;
    }
    else if (request == 0){
        return programs;
    } else if (request == 1){
        return frequencies;
    }
}

int Device::increasePower()
{
    if (powerLevel >= maxPowerLevel){
        return powerLevel;
    }
    powerLevel += 1;
    return powerLevel;
}

int Device::decreasePower()
{
    if (powerLevel <= minPowerLevel){
        return powerLevel;
    }
    powerLevel -= 1;
    return powerLevel;
}

Device::~Device()
{
}
