#ifndef PREVIOUSTREATMENT_H
#define PREVIOUSTREATMENT_H

#include "therapy.h"

#include <QDate>

class PreviousTreatment {
public:
    PreviousTreatment(Therapy* t) : date(QDate::currentDate()), therapy(t) {}

    QDate date;
    Therapy* therapy;
};

#endif // PREVIOUSTREATMENT_H
