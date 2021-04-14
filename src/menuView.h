#ifndef MENUVIEW_H
#define MENUVIEW_H

#include "view.h"

#include <QList>

class MenuView : public View {
public:
    MenuView(QString n, View* p) : View(n, p) {}
    ~MenuView() {};

    QStringList constructMenu();

    void addChild(View* child) { children->append(child); }
    void clearChildren() { children->clear(); }
    void removeChild(View* child) { children->removeOne(child); }

    QString getType() { return "MenuView"; }
    QString getName() { return name; }
    Therapy* getTherapy() { return NULL; }
};

#endif // MENUVIEW_H
