#ifndef BATTERY_H
#define BATTERY_H

#define MINBATTERYLEVEL = 0
#define MAXBATTERYLEVEL = 100

class Battery {
public:
    Battery(double b = 11) : batteryLevel(b) {};

    double decreaseBatteryLevel(int currPwrLvl);
    double getBatteryLevel() { return batteryLevel; } // NOT CURRENTLY USED
    bool isLow() { return batteryLevel <= 10; } //  NOT CURRENTLY USED

private:
    float batteryLevel;
};

#endif // BATTERY_H
