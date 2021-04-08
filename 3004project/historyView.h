#ifndef HISTORYVIEW_H
#define HISTORYVIEW_H

#include "previoustreatment.h"
#include "view.h"

class HistoryView : public View {
public:
    HistoryView(QString n, View* p, PreviousTreatment* t) : View(n, p), previousTreatment(t) {};
    ~HistoryView() {};

    PreviousTreatment* previousTreatment;

    QStringList constructMenu() { return QStringList(); };
    QString type() { return "HistoryView"; };
    QString getName() { return name; };
    Therapy* getTherapy() { return previousTreatment->therapy; }
    PreviousTreatment* getPreviousTreatment() { return previousTreatment; }
};

#endif // HISTORYVIEW_H
