#ifndef DISPLAY_H
#define DISPLAY_H

#include "frequency.h"
#include "program.h"

#include <QStringList>

using namespace std;

class Display {
public:
    Display(QList<Frequency*>* frequencies, QList<Program*>* programs);

    QStringList *program;
    QStringList *frequency;
    QStringList *menu;

    int updateDisplay(QString request);

private:
    int currentDisplay;
};

#endif // DISPLAY_H
