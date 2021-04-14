#ifndef BATTERY_H
#define BATTERY_H

#define MINBATTERYLEVEL 0
#define MAXBATTERYLEVEL 100
#define LOWBATTERYLEVEL 10

class Battery {
public:
    Battery(float b = MAXBATTERYLEVEL) : batteryLevel(b) {};

    float   decreaseBatteryLevel(int currPwrLvl);
    float   getBatteryLevel() { return batteryLevel; }
    bool    isLow() { return batteryLevel <= LOWBATTERYLEVEL; }
    float   chargeBattery();

private:
    float batteryLevel;
};

#endif // BATTERY_H
