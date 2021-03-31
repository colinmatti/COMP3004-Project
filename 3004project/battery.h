#ifndef BATTERY_H
#define BATTERY_H

#include <iostream>

using namespace std;

class Battery
{
public:
    Battery(int batteryLevel=100, int maxLevel=100, int minLevel=0);
    ~Battery();
    bool isLow();
    void decreaseLevel(int amnt);

private:
    int batteryLevel;
    int maxLevel;
    int minLevel;

};

#endif // BATTERY_H
