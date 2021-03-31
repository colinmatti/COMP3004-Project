#ifndef BATTERY_H
#define BATTERY_H

#include <iostream>

#define MINBATTERYLEVEL = 0
#define MAXBATTERYLEVEL = 100

using namespace std;

class Battery {
public:
    Battery(int b = 100) : batteryLevel(b) {};

    bool isLow();
    void decreaseLevel(int amnt);

private:
    int batteryLevel;
};

#endif // BATTERY_H
