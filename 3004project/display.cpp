#include "display.h"
#include <vector>

Display::Display()
{
    menu = new vector<string>();
    menu->push_back("Programmed");
    menu->push_back("Frequency");
    menu->push_back("History");

    programmed = new vector<string>();
    programmed->push_back("Throat");
    programmed->push_back("Joint");
    programmed->push_back("Bloating");
    programmed->push_back("Pain");

    frequency = new vector<string>();
    frequency->push_back("1.0-9.9 Hz");
    frequency->push_back("10 Hz");
    frequency->push_back("20 Hz");
    frequency->push_back("60 Hz");

}
