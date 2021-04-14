#ifndef TREATMENTVIEW_H
#define TREATMENTVIEW_H

#include "view.h"

class TreatmentView : public View {
public:
    TreatmentView(QString n, View* p, Therapy* t) : View(n, p), therapy(t) {}
    ~TreatmentView() {};

    QStringList constructMenu() { return QStringList(); }

    QString getType() { return "TreatmentView"; }
    QString getName() { return therapy->getName(); }
    Therapy* getTherapy() { return therapy; }

private:
    Therapy* therapy;
};

#endif // TREATMENTVIEW_H
