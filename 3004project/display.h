#ifndef DISPLAY_H
#define DISPLAY_H

#include "menuView.h"
#include "treatmentView.h"
#include "frequency.h"
#include "previoustreatment.h"
#include "program.h"

using namespace std;

class Display {
public:
    Display(QList<Frequency*>* frequencies, QList<Program*>* programs);
    // TODO: destructor.
    MenuView* mainMenu;
    MenuView* historyMenu;

    void addHistoryToNavigation(Therapy* therapy);
};

#endif // DISPLAY_H
