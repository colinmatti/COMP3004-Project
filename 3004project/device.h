#ifndef DEVICE_H
#define DEVICE_H

#include "battery.h"
#include "display.h"
#include "frequency.h"
#include "previoustreatment.h"
#include "program.h"
#include "therapy.h"
#include "view.h"

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
    int increasePower();
    int decreasePower();
    int resetPower();
    void addToHistory(Therapy* therapy, int powerLevel, int duration);
    void removeFromHistory(HistoryView* historyView);
    void clearHistory();
    View* mainMenu();
    int batteryLevel();
    int getCurrentMaxPower();

private:
    int powerLevel;
    int currentMaxPower;
    bool poweredOn;
    bool onSkin;
    Battery *battery;
    Display *display;
    QList<Program*> *programs;
    QList<Frequency*> *frequencies;
    QStringList runTreatment(QString request);
    QList<PreviousTreatment*> *treatmentHistory;
};

#endif // DEVICE_H
