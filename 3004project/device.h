#ifndef DEVICE_H
#define DEVICE_H
#include "display.h"
#include <string>
#include "battery.h"

class Device
{

public:
    Device();
    ~Device();
    bool poweredOn;
    vector<string>* receive(int request);
    int increasePower();
    int decreasePower();
private:
    Battery *battery;
    Display *display;
    int powerLevel;
    bool onSkin;
    int minPowerLevel;
    int maxPowerLevel;
    void updateBattery();
    void runTreatment();
};


#endif // DEVICE_H
