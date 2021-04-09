#ifndef DEVICE_H
#define DEVICE_H

#include "battery.h"
#include "display.h"
#include "frequency.h"
#include "previousTreatment.h"
#include "program.h"
#include "therapy.h"
#include "view.h"

#include <QList>
#include <QStringList>

#define MINPOWERLEVEL 1
#define MAXPOWERLEVEL 100

class Device {
public:
    Device();
    ~Device();

    void addToHistory();
    void clearHistory();
    void removeFromHistory(HistoryView* historyView);

    bool applyOnSkin();

    int decreasePower();
    int increasePower();
    int getPowerLevel() { return powerLevel; }

    bool power();

    bool startTreatment(Therapy* therapy);
    bool stopTreatment();
    bool maybeAddTreatmentToHistory();
    bool isTreatmentRunning() { return treatmentRunning; }
    void updateTimer();

    View* navigateDown(int index);

    int getBatteryLevel() { return battery->getBatteryLevel(); }
    View* getMainMenu() { return display->getMainMenu(); }

private:
    Display *display;
    Battery *battery;

    bool isOnSkin;
    int powerLevel;
    bool poweredOn;

    bool treatmentRunning;
    bool attemptedQuitTreatment;
    PreviousTreatment* activeTherapy;

    bool shouldAddTreatmentToHistory;

    QList<Frequency*> *frequencies;
    QList<Program*> *programs;
    QList<PreviousTreatment*> *treatmentHistory;
};

#endif // DEVICE_H
