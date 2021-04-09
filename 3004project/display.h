#ifndef DISPLAY_H
#define DISPLAY_H

#include "historyView.h"
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

    void addHistoryToNavigation(PreviousTreatment* previousTreatment);
    void removeHistoryFromNavigation(HistoryView* historyView);
    void clearHistoryNavigation();
};

#endif // DISPLAY_H
