#include "battery.h"

#include <iostream>
using namespace std;

Battery::Battery(int batLevel, int max, int min) : batteryLevel(batLevel), maxLevel(max), minLevel(min) {}

Battery::~Battery() {}

bool Battery::isLow()
{
    return batteryLevel <= 10
        return true;
    }
    return false;
}

void Battery::decreaseLevel(int amnt)
{
    if (batteryLevel - amnt < 0) {
        batteryLevel = 0;
        return;
    }
    batteryLevel -= amnt;
}
