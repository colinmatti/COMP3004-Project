#include "battery.h"

/**
 * @brief Determines whether the current battery level of the device is low.
 * @return boolean
 */
bool Battery::isLow() {
    return batteryLevel <= 10;
}

/**
 * @brief Decreases the battery level by the the device's current powerlevel and the time elapsed for the treatment.
 * @param currPwrLvl: the power level of the device.
 *        timePassed: the time elapsed in a therapy treatment.
 */
void Battery::decreaseLevel(int currPwrLvl, int timePassed) {
    if (timePassed > 0) {
        if (batteryLevel - currPwrLvl*timePassed < 0) {
            batteryLevel = 0;
            return;
        }
        batteryLevel -= currPwrLvl*timePassed ;
    }
}

int Battery::getBatteryLevel() {
    return batteryLevel;
}

