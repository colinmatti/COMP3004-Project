#ifndef HISTORYVIEW_H
#define HISTORYVIEW_H

#include "previousTreatment.h"
#include "treatmentView.h"

class HistoryView : public TreatmentView {
public:
    HistoryView(QString n, View* p, PreviousTreatment* t) : TreatmentView(n, p, t->getTherapy()), previousTreatment(t) {};
    ~HistoryView() {};

    QStringList constructMenu() { return QStringList(); }

    PreviousTreatment* getPreviousTreatment() { return previousTreatment; }

    QString getType() { return "TreatmentView"; }
    QString getName() { return name; }
    Therapy* getTherapy() { return previousTreatment->getTherapy(); }

private:
    PreviousTreatment* previousTreatment;
};

#endif // HISTORYVIEW_H
