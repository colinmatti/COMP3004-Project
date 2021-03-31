#ifndef DEVICE_H
#define DEVICE_H

#include "battery.h"
#include "display.h"
#include "frequency.h"
#include "previoustreatment.h"
#include "program.h"
#include "therapy.h"

#include <array>
#include <iostream>
#include <QList>
#include <QStringList>

#define MINPOWERLEVEL 1
#define MAXPOWERLEVEL 100

class Device {
public:
    Device();
    ~Device();

    bool isPoweredOn();
    bool isOnSkin();
    void power();
    void applyOnSkin();
    QStringList receive(QString request);
    int increasePower();
    int decreasePower();
    void endTreatment();
    Therapy* getStatus();

private:
    int powerLevel;
    bool poweredOn;
    bool onSkin;
    Battery *battery;
    Display *display;
    QList<Program*> *programs;
    QList<Frequency*> *frequencies;
    void runTreatment();
    QList<PreviousTreatment*> *treatmentHistory;
    void addToHistory(Therapy* therapy);
    Therapy* status;
};

#endif // DEVICE_H
