#include "display.h"

#include <QStringList>

Display::Display()
{
    menu = new QStringList();
    menu->append("Programmed");
    menu->append("Frequency");
    menu->append("History");

    programmed = new QStringList();
    programmed->append("Throat");
    programmed->append("Joint");
    programmed->append("Bloating");
    programmed->append("Pain");

    frequency = new QStringList();
    frequency->append("1.0-9.9 Hz");
    frequency->append("10 Hz");
    frequency->append("20 Hz");
    frequency->append("60 Hz");

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
    if (request == "off" || request == "on" || request == "menu"){
        currentDisplay = 0;
    } else if (request == "back"){
        if (currentDisplay > 0){
            currentDisplay--;
        }
    } else if (request == "Frequency"){
        currentDisplay = 1;
    } else if (request == "Programmed"){
        currentDisplay = 2;
    } else if (request == "History"){
        currentDisplay = 3;
    } else if (programmed->contains(request) || frequency->contains(request)){
        currentDisplay = 4;
    }
    return currentDisplay;
}
