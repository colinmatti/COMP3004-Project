#include "battery.h"

/**
 * @brief Decreases the battery level by the the device's current powerlevel and the time elapsed for the treatment.
 * @param currPwrLvl: the power level of the device.
 * @param timePassed: the time elapsed in a therapy treatment.
 */
void Battery::decreaseBatteryLevel(int currPwrLvl, int timePassed) {
    if (timePassed <= 0) { return; }

    batteryLevel -= currPwrLvl*timePassed;

    // If we're decreasing the battery lower than 0%, make the battery 0%.
    if (batteryLevel < 0) { batteryLevel = 0; }
}
