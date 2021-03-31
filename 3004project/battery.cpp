#include "battery.h"

#include <iostream>
using namespace std;

Battery::Battery(int batLevel, int max, int min) : batteryLevel(batLevel), maxLevel(max), minLevel(min) {}

Battery::~Battery() {}

bool Battery::isLow()
{
    return batteryLevel <= 10;
}

void Battery::decreaseLevel(int currPwrLvl, int timePassed)
{
    if (timePassed > 0) {
        if (batteryLevel - currPwrLvl*timePassed < 0) {
            batteryLevel = 0;
            return;
        }
        batteryLevel -= currPwrLvl*timePassed ;
    }
}
