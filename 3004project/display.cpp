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
        programsMenu->getChildren()->append(therapy);
    }

    for (Frequency* frequency : *frequencies) {
        TreatmentView* therapy = new TreatmentView(QString::number(frequency->getFrequency()), frequenciesMenu, frequency);
        frequenciesMenu->getChildren()->append(therapy);
    }

    // Add menues to children of main menu.
    mainMenu->getChildren()->append(programsMenu);
    mainMenu->getChildren()->append(frequenciesMenu);
    mainMenu->getChildren()->append(historyMenu);

    currentView = mainMenu;
}

/**
 * @brief Adds given previous treatment to navigation graph.
 * @param therapy: the therapy to be added to the navigation graph.
 */
void Display::addHistoryToNavigation(PreviousTreatment* previousTreatment) {
    // Gather data to construct history view name.
    QString weekday = previousTreatment->getDate().toString();
    QString time = previousTreatment->getTime().toString();
    QString type = previousTreatment->getTherapy()->getType();
    QString name = previousTreatment->getTherapy()->getName();
    QString powerLevel = QString::number(previousTreatment->getMaxPowerLevel());
    QString minutes = QString::number(floor(previousTreatment->getDurationInSeconds() / 60));
    QString seconds = QString::number(previousTreatment->getDurationInSeconds() % 60);

    // Construct history view name.
    QString historyName = QString("%1 %2\nTreatment: %3, %4\nPower Level: %5\nDuration: %6m%7s")
            .arg(weekday, time, type, name, powerLevel, minutes, seconds);

    // Construct history view and add to display graph.
    HistoryView* historyView = new HistoryView(historyName, historyMenu, previousTreatment);
    historyMenu->addChild(historyView);
}

/**
 * @brief Clears all history views from histories menu.
 * @return True if successfully cleared histories menu, False otherwise.
 */
bool Display::clearHistoryNavigation() {
    // If not currently on histories menu, abort.
    if (currentView->getName() != "History") { return false; }

    historyMenu->clearChildren();
    return true;
}

/**
 * @brief Removes view containing given previous treatment from history navigation.
 * @param index: the index of the previous treatment to be removed from the graph.
 * @return the history view removed from the navigation.
 */
HistoryView* Display::removeHistoryFromNavigation(int index) {
    // If not currently on histories menu, abort.
    if (currentView->getName() != "History") { return NULL; }

    // Find history view we're attempting to remove.
    View* historyView = currentView->getChildAt(index);
    if (historyView == NULL) { return NULL; }

    // If the history view is found, remove from navigation and return as a history view.
    historyMenu->removeChild(historyView);
    return dynamic_cast<HistoryView*>(historyView);
}

/**
 * @brief Attempts to navigate down in navigation menu.
 * @param index: the menu index to navigate down into.
 * @return the new view if successful, otherwise NULL.
 */
View* Display::navigateDown(int index) {
    // Find view we're attempting to move to.
    View* destination = currentView->getChildAt(index);

    if (destination == NULL) { return NULL; }

    currentView = destination;
    return currentView;
}

/**
 * @brief Attempts to navigate up in navigation menu.
 * @return the new view if successful, otherwise NULL.
 */
View* Display::navigateUp() {
    // Find view we're attempting to move to.
    View* destination = currentView->getParent();

    if (destination == NULL) { return NULL; }

    currentView = destination;
    return currentView;
}

/**
 * @brief Navigate to the main menu.
 * @return the main menu view.
 */
View* Display::navigateToMenu() {
    currentView = mainMenu;
    return currentView;
}
