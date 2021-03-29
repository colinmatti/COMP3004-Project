#include "device.h"
#include <string>
#include <iostream>
#include <array>

Device::Device()
{
    poweredOn = false;
    powerLevel = 0;
    minPowerLevel = 0; // constant?
    maxPowerLevel = 100; // constant?
}

QStringList* Device::receive(int request)
{
    if (request == -1){
        return display->menu;
    }
    else if (request == 0){
        return display->programmed;
    } else if (request == 1){
        return display->frequency;
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
