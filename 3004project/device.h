#ifndef DEVICE_H
#define DEVICE_H
#include "display.h"
#include <string>

class Device
{

public:
    Device();
    ~Device();
    bool poweredOn;
    QStringList* receive(int request);
    int increasePower();
    int decreasePower();

private:
    Display *display = new Display;
    int powerLevel;
    bool onSkin;
    int minPowerLevel;
    int maxPowerLevel;
    void updateBattery();
    void runTreatment();
};


#endif // DEVICE_H
