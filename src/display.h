#ifndef DISPLAY_H
#define DISPLAY_H

#include "historyView.h"
#include "menuView.h"
#include "treatmentView.h"
#include "frequency.h"
#include "activeTreatment.h"
#include "program.h"
#include <QStringListModel>

class Display {
public:
    Display(QList<Frequency*>* frequencies, QList<Program*>* programs);
    ~Display();
    void cleanUp(View* view);

    void addHistoryToNavigation(ActiveTreatment* previousTreatment);

    ActiveTreatment* removeHistoryFromNavigation();
    bool clearHistoryNavigation();

    View* navigateDown();
    View* navigateUp();
    View* navigateToMenu();

    QModelIndex decreaseIndex();
    QModelIndex increaseIndex();
    QModelIndex resetIndex();
    QStringListModel* getModel() { return model; }

    int getCurrentIndex() {return currentIndex; }
    View* getCurrentView() { return currentView; }
    MenuView* getMainMenu() { return mainMenu; }

private:
    MenuView* historyMenu;
    MenuView* mainMenu;
    View* currentView;
    int currentIndex;
    QStringListModel* model;
};

#endif // DISPLAY_H
