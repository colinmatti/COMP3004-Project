#ifndef BATTERY_H
#define BATTERY_H

#define MINBATTERYLEVEL = 0
#define MAXBATTERYLEVEL = 100

class Battery {
public:
    Battery(double b = MAXBATTERYLEVEL) : batteryLevel(b) {};

    double decreaseBatteryLevel(int currPwrLvl);
    double getBatteryLevel() { return batteryLevel; }
    bool isLow() { return batteryLevel <= 10; }

private:
    float batteryLevel;
};

#endif // BATTERY_H
