#ifndef PREVIOUSTREATMENT_H
#define PREVIOUSTREATMENT_H

#include "therapy.h"

#include <QDate>

class PreviousTreatment {
public:
    PreviousTreatment(Therapy* t, int p = 0, int d = 0) : date(QDate::currentDate()), therapy(t), maxPowerLevel(p), durationInSeconds(d) {}

    QDate date;
    Therapy* therapy;

private:
    int maxPowerLevel;
    int durationInSeconds;
};

#endif // PREVIOUSTREATMENT_H
