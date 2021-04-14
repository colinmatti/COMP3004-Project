#include "battery.h"

/**
 * @brief Decreases the battery level by the the device's current powerlevel and the time elapsed for the treatment.
 * @param currPwrLvl: the power level of the device.
 * @param timePassed: the time elapsed in a therapy treatment.
 */
float Battery::decreaseBatteryLevel(int powerLevel) {
    batteryLevel -= (float) powerLevel / 700;

    // If we're decreasing the battery lower than 0%, make the battery 0%.
    if (batteryLevel < MINBATTERYLEVEL) { batteryLevel = MINBATTERYLEVEL; }
    return batteryLevel;
}

float Battery::chargeBattery(){
    batteryLevel=MAXBATTERYLEVEL;
    return batteryLevel;
}
