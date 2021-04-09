#ifndef PREVIOUSTREATMENT_H
#define PREVIOUSTREATMENT_H

#include "therapy.h"

#include <QDate>

class PreviousTreatment {
public:
    PreviousTreatment(Therapy* t, int p = 0, int d = 0) :
        date(QDate::currentDate()),
        time(QTime::currentTime()),
        therapy(t),
        maxPowerLevel(p),
        durationInSeconds(d) {}

    QDate date;
    QTime time;
    Therapy* therapy;
    int getMaxPowerLevel() { return maxPowerLevel; }
    int getDurationInSeconds() { return durationInSeconds; }

private:
    int maxPowerLevel;
    int durationInSeconds;
};

#endif // PREVIOUSTREATMENT_H
