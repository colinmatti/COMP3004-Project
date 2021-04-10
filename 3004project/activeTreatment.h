#ifndef ACTIVETREATMENT_H
#define ACTIVETREATMENT_H

#include "therapy.h"

#include <QDate>

class ActiveTreatment {
public:
    ActiveTreatment(Therapy* t, int p = 1, int d = 0) :
        date(QDate::currentDate()),
        durationInSeconds(d),
        maxPowerLevel(p),
        time(QTime::currentTime()),
        therapy(t) {}

    QDate getDate() { return date; }
    int getDurationInSeconds() { return durationInSeconds; }
    int getMaxPowerLevel() { return maxPowerLevel; }
    QTime getTime() { return time; }
    Therapy* getTherapy() { return therapy; }

    void increasePowerLevel(int powerLevel) { maxPowerLevel = (powerLevel > maxPowerLevel) ? powerLevel : maxPowerLevel; }
    void increaseTime() { durationInSeconds++; }

    bool isOngoing() { return (durationInSeconds < therapy->getTimer()); }
    int timeRemaining() {return therapy->getTimer() - durationInSeconds; }

private:
    QDate date;
    int durationInSeconds;
    int maxPowerLevel;
    QTime time;
    Therapy* therapy;
};

#endif // ACTIVETREATMENT_H
