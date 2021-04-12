#ifndef BATTERY_H
#define BATTERY_H

#define MINBATTERYLEVEL = 0
#define MAXBATTERYLEVEL = 100

class Battery {
public:
    Battery(float b = MAXBATTERYLEVEL) : batteryLevel(b) {};

    float decreaseBatteryLevel(int currPwrLvl);
    float getBatteryLevel() { return batteryLevel; }
    bool isLow() { return batteryLevel <= 10; }

private:
    float batteryLevel;
};

#endif // BATTERY_H
