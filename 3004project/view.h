#ifndef VIEW_H
#define VIEW_H

#include "therapy.h"

#include <QString>
#include <QStringList>

class View {
public:
    View(QString n, View* p) : name(n), parent(p) {};

    View* parent;

    virtual QStringList constructMenu() = 0;
    virtual QString type() = 0;
    virtual QString getName() = 0;
    virtual Therapy* getTherapy() = 0;
    View* getParent() { return parent; };

protected:
    QString name;
};

#endif // VIEW_H
