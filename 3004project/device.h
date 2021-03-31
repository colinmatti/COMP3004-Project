#ifndef DEVICE_H
#define DEVICE_H

#include "display.h"
#include <string>
#include "battery.h"
#include "program.h"
#include "frequency.h"
#include "therapy.h"
#include "previoustreatment.h"

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
    Battery *battery;
    Display *display;
    int powerLevel;
    int minPowerLevel;
    int maxPowerLevel;
    QList<Program> *programs;
    QList<Frequency> *frequencies;
    QList<PreviousTreatment> *treatmentHistory;

    void updateBattery();
    void runTreatment();
    void addToHistory(Therapy* therapy);
};


#endif // DEVICE_H
