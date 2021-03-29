#include "display.h"

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

}
