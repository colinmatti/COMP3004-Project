#ifndef DISPLAY_H
#define DISPLAY_H

#include <QStringList>

using namespace std;

class Display
{
public:
    Display();
    QStringList *programmed;
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
