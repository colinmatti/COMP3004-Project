#ifndef DEVICE_H
#define DEVICE_H

#include "display.h"
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
    QStringList receive(QString request);
    bool onSkin;
    int increasePower();
    int decreasePower();

private:
    Display *display = new Display;
    int powerLevel;
    int minPowerLevel;
    int maxPowerLevel;
    QList<Program> *programs;
    QList<Frequency> *frequencies;

    void updateBattery();
    void runTreatment();
};


#endif // DEVICE_H
