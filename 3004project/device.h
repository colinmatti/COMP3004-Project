#ifndef DEVICE_H
#define DEVICE_H

#include "display.h"
#include <string>
#include "battery.h"
#include "program.h"
#include "frequency.h"
#include "therapy.h"
#include <QStringList>

class Device
{
public:
    Device();
    ~Device();
    bool poweredOn;
    QList<Therapy>* receive(int request);
    int increasePower();
    int decreasePower();

private:
    Battery *battery;
    Display *display;
    int powerLevel;
    bool onSkin;
    int minPowerLevel;
    int maxPowerLevel;
    QList<Program> *programs;
    QList<Frequency> *frequencies;

    void updateBattery();
    void runTreatment();
};


#endif // DEVICE_H
