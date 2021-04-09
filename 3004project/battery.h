#ifndef BATTERY_H
#define BATTERY_H

#define MINBATTERYLEVEL = 0
#define MAXBATTERYLEVEL = 100

class Battery {
public:
    Battery(int b = 100) : batteryLevel(b) {};

    void decreaseBatteryLevel(int currPwrLvl, int timePassed); // NOT CURRENTLY USED
    int getBatteryLevel() { return batteryLevel; } // NOT CURRENTLY USED
    bool isLow() { return batteryLevel <= 10; } //  NOT CURRENTLY USED

private:
    int batteryLevel;
};

#endif // BATTERY_H
