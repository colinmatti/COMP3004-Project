#ifndef DISPLAY_H
#define DISPLAY_H

#include "historyView.h"
#include "menuView.h"
#include "treatmentView.h"
#include "frequency.h"
#include "previousTreatment.h"
#include "program.h"

class Display {
public:
    Display(QList<Frequency*>* frequencies, QList<Program*>* programs);

    void addHistoryToNavigation(PreviousTreatment* previousTreatment);
    void clearHistoryNavigation();
    View* removeHistoryFromNavigation(HistoryView* historyView);

    View* navigateDown(int index);
    View* navigateUp();

    View* getCurrentView() { return currentView; }
    MenuView* getMainMenu() { return mainMenu; }

private:
    MenuView* historyMenu;
    MenuView* mainMenu;
    View* currentView;
};

#endif // DISPLAY_H
