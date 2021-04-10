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

#define NO_ERROR "***No error detected***"
#define ERROR_NO_SKIN "***ERROR: No skin detected***"
#define WARNING_LOW_BATT "***WARNING: Battery is low***"
#define WARNING_TREATMENT_RUNNING "***WARNING: treatment is currently running***"
#define WARNING_NO_TREATMENT_RUNNING "***WARNING: no treatment is currently running***"

class Device {
public:
    Device();
    ~Device();

    View* removeFromHistory(int index);
    View* clearHistory();

    bool applyOnSkin();

    int decreasePower();
    int increasePower();
    int getPowerLevel() { return powerLevel; }

    bool power();

    bool startTreatment(Therapy* therapy);
    bool stopTreatment();
    bool maybeAddTreatmentToHistory();
    void updateTimer();

    View* navigateDown(int index);
    View* navigateUp();
    View* navigateToMenu();
    View* getCurrentView();

    QString getActiveError() { return activeError; }
    int getBatteryLevel() { return battery->getBatteryLevel(); }

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

    QString activeError;

    QList<Frequency*> *frequencies;
    QList<Program*> *programs;
    QList<PreviousTreatment*> *treatmentHistory;

    void addToHistory();
};

#endif // DEVICE_H
