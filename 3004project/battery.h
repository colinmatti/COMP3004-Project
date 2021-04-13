#ifndef BATTERY_H
#define BATTERY_H

#define MINBATTERYLEVEL 0
#define MAXBATTERYLEVEL 100
#define LOWBATTERYLEVEL 10

class Battery {
public:
    Battery(float b = MAXBATTERYLEVEL) : batteryLevel(b) {};

    float decreaseBatteryLevel(int currPwrLvl);
    int   getBatteryLevel() { return batteryLevel; }
    bool  isLow() { return batteryLevel <= LOWBATTERYLEVEL; }
    void  chargeBattery(){ batteryLevel=MAXBATTERYLEVEL; }
private:
    float batteryLevel;
};

#endif // BATTERY_H
