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

    bool poweredOn;
    bool onSkin;

    QStringList receive(QString request);
    int increasePower();
    int decreasePower();

private:
    int powerLevel;
    Battery *battery;
    Display *display;
    QList<Program*> *programs;
    QList<Frequency*> *frequencies;
    QList<PreviousTreatment*> *treatmentHistory;

    void updateBattery(int currPwrLvl, int time);
    int runTreatment();
    void addToHistory(Therapy* therapy);
};

#endif // DEVICE_H
