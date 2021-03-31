#include "display.h"

Display::Display(QList<Frequency*>* frequencies, QList<Program*>* programs) {
    menu = new QStringList();
    menu->append("Programs");
    menu->append("Frequency");
    menu->append("History");

    frequency = new QStringList();
    for (int i = 0; i < frequencies->size(); i++){
        frequency->append(QString::number(frequencies->at(i)->getFrequency()));
    }

    program = new QStringList();
    for (int i = 0; i < programs->size(); i++){
        program->append(programs->at(i)->getName());
    }

    currentDisplay = 0;
}

// Current Display
// 0: menu
// 1: frequency
// 2: programmed
// 3: history
// 4: timer (specific therapy)
// 5: power level????

int Display::updateDisplay(QString request)
{
    if (request == "off" || request == "on" || request == "menu" || request == "back"){
        currentDisplay = 0;
    } else if (request == "Frequency"){
        currentDisplay = 1;
    } else if (request == "Programs"){
        currentDisplay = 2;
    } else if (request == "History"){
        currentDisplay = 3;
    } else if (program->contains(request) || frequency->contains(request)){
        currentDisplay = 4;
    }
    return currentDisplay;
}

