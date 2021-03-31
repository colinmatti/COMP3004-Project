#include "battery.h"

Battery::Battery(int batLevel, int max, int min) : batteryLevel(batLevel), maxLevel(max), minLevel(min) {}

Battery::~Battery() {}

/**
 * @brief Determines whether the current battery level of the device is low.
 * @return boolean
 */
bool Battery::isLow() {
    return batteryLevel <= 10;
}

/**
 * @brief Decreases the battery level by the amount passed in.
 * @param amnt: the amount by which to decrease the battery level.
 */
void Battery::decreaseLevel(int amnt)
{
    if (batteryLevel - amnt < 0) {
        batteryLevel = 0;
        return;
    }
    batteryLevel -= amnt;
}
