#ifndef PREVIOUSTREATMENT_H
#define PREVIOUSTREATMENT_H

#include "therapy.h"

#include <QDate>

class PreviousTreatment {
public:
    PreviousTreatment(Therapy* t, int p = 1, int d = 0) :
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

private:
    QDate date;
    int durationInSeconds;
    int maxPowerLevel;
    QTime time;
    Therapy* therapy;
};

#endif // PREVIOUSTREATMENT_H
