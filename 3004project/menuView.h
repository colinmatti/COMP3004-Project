#ifndef MENUVIEW_H
#define MENUVIEW_H

#include "view.h"

#include <QList>

class MenuView : public View {
public:
    MenuView(QString n, View* p) : View(n, p) { children = new QList<View*>(); }
    ~MenuView() {};

    QList<View*>* children;

    QStringList constructMenu();
    QString type() { return "MenuView"; };
    QString getName() { return NULL; };
    Therapy* getTherapy() { return NULL; };
};

#endif // MENUVIEW_H
