#ifndef PREVIOUSTREATMENT_H
#define PREVIOUSTREATMENT_H

#include <QDate>
#include "therapy.h"

class PreviousTreatment
{
public:
    PreviousTreatment(Therapy* t);
    QDate date;
    Therapy* therapy;
};

#endif // PREVIOUSTREATMENT_H
