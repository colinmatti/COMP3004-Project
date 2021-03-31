#ifndef DISPLAY_H
#define DISPLAY_H

#include <QStringList>
#include "frequency.h"
#include "program.h"

using namespace std;

class Display
{
public:
    Display(QList <Frequency> *frequencies, QList<Program> *programs);
    QStringList *program;
    QStringList *frequency;
    QStringList *menu;
    int updateDisplay(QString request);
private:
    int currentDisplay;
};

// Current Display
// 0: menu
// 1: frequency
// 2: programmed
// 3: timer (specific therapy)
// 4: power level

#endif // DISPLAY_H
