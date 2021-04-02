#ifndef TREATMENTVIEW_H
#define TREATMENTVIEW_H

#include "view.h"

class TreatmentView : public View {
public:
    TreatmentView(QString n, View* p, Therapy* t) : View(n, p), therapy(t) {};
    ~TreatmentView() {};

    Therapy* therapy;

    QStringList constructMenu() { return QStringList(); };
    QString type() { return "TreatmentView"; };
    QString getName() { return name; };
    Therapy* getTherapy() { return therapy; };
};

#endif // TREATMENTVIEW_H
