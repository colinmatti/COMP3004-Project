#include "display.h"

Display::Display(QList<Frequency*>* frequencies, QList<Program*>* programs) {
    // Create main menu node.
    mainMenu = new MenuView("Main Menu", NULL);

    // Create other menu nodes.
    MenuView* programsMenu = new MenuView("Programs", mainMenu);
    MenuView* frequenciesMenu = new MenuView("Frequencies", mainMenu);
    historyMenu = new MenuView("History", mainMenu);

    // Populate menues with therapies.
    for (Program* program : *programs) {
        TreatmentView* therapy = new TreatmentView(program->getName(), programsMenu, program);
        programsMenu->children->append(therapy);
    }

    for (Frequency* frequency : *frequencies) {
        TreatmentView* therapy = new TreatmentView(QString::number(frequency->getFrequency()), frequenciesMenu, frequency);
        frequenciesMenu->children->append(therapy);
    }

    // Add menues to children of main menu.
    mainMenu->children->append(programsMenu);
    mainMenu->children->append(frequenciesMenu);
    mainMenu->children->append(historyMenu);
}

// TODO: destructor.

/**
 * @brief Adds given previous treatment to navigation graph.
 * @param therapy: the therapy to be added to the navigation graph.
 */
void Display::addHistoryToNavigation(PreviousTreatment* previousTreatment) {
    HistoryView* historyView = new HistoryView(previousTreatment->therapy->getName(), historyMenu, previousTreatment);
    historyMenu->children->append(historyView);
}

/**
 * @brief Removes view containing given previous treatment from history navigation.
 * @param previousTreatment: the previous treatment to be removed from the graph.
 */
void Display::removeHistoryFromNavigation(HistoryView* historyView) {
    historyMenu->children->removeOne(historyView);
}

void Display::clearHistoryNavigation() {
    historyMenu->children->clear();
}
