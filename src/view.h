#ifndef VIEW_H
#define VIEW_H

#include "therapy.h"

#include <QString>
#include <QStringList>

class View {
public:
    View(QString n, View* p): children(new QList<View*>()), name(n), parent(p) {}
    virtual ~View() { delete children; }

    virtual QStringList constructMenu() = 0;

    QList<View*>* getChildren() { return children; }
    View* getChildAt(int index) {
        if (children->length() <= index || index == -1) { return nullptr; }
        return children->at(index);
    }


    View* getParent() { return parent; }

    virtual QString getName() = 0;
    virtual Therapy* getTherapy() = 0;
    virtual QString getType() = 0;

protected:
    QList<View*>* children;
    QString name;
    View* parent;
};

#endif // VIEW_H
