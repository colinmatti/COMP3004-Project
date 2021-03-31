#include "display.h"

#include <QStringList>

Display::Display()
{
    menu = new QStringList();
    menu->push_back("Programmed");
    menu->push_back("Frequency");
    menu->push_back("History");
}
