#include "previoustreatment.h"

PreviousTreatment::PreviousTreatment(Therapy* t)
{
    therapy = t;
    date = QDate::currentDate();
}
