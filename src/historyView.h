#ifndef HISTORYVIEW_H
#define HISTORYVIEW_H

#include "activeTreatment.h"
#include "treatmentView.h"

class HistoryView : public TreatmentView {
public:
    HistoryView(QString n, View* p, ActiveTreatment* t) : TreatmentView(n, p, t->getTherapy()), previousTreatment(t) {}
    ~HistoryView() {}

    QStringList constructMenu() { return QStringList(); }

    ActiveTreatment* getPreviousTreatment() { return previousTreatment; }

    QString getType() { return "TreatmentView"; }
    QString getName() { return name; }
    Therapy* getTherapy() { return previousTreatment->getTherapy(); }

private:
    ActiveTreatment* previousTreatment;
};

#endif // HISTORYVIEW_H
