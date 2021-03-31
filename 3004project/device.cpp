#include "device.h"

#include <string>
#include <iostream>
#include <array>
#include <QList>

Device::Device()
{
    battery = new Battery();
    display = new Display();
    poweredOn = false;
    powerLevel = 1;

    // Instantiate all preset therapies.
    programs = new QList<Program>();
    frequencies = new QList<Frequency>();

    // Create and append programs.
    Program throat = Program(QString("Throat"), 10, 600, 30);
    programs->append(throat);

    Program nausea = Program(QString("Nausea"), 15, 240, 10);
    programs->append(nausea);

    Program chlamydia = Program(QString("Chlamydia"), 25, 1200, 80);
    programs->append(chlamydia);

    Program diarrhea = Program(QString("Diarrhea"), 5, 120, 65);
    programs->append(diarrhea);

    // Create and append frequencies.
    Frequency five = Frequency(5, 300, 50);
    frequencies->append(five);

    Frequency ten = Frequency(10, 300, 50);
    frequencies->append(ten);

    Frequency fifteen = Frequency(15, 300, 50);
    frequencies->append(fifteen);

    Frequency twenty = Frequency(20, 300, 50);
    frequencies->append(twenty);
}

QList<Therapy>* Device::receive(int request)
{
    if (request == -1){
        return display->menu;
    }
    else if (request == 0){
        return programs;
    } else if (request == 1){
        return frequencies;
    }
}

int Device::increasePower()
{
    if (powerLevel >= MAXPOWERLEVEL){
        return powerLevel;
    }
    powerLevel += 1;
    return powerLevel;
}

int Device::decreasePower()
{
    if (powerLevel <= MINPOWERLEVEL){
        return powerLevel;
    }
    powerLevel -= 1;
    return powerLevel;
}

Device::~Device()
{
}

void Device::updateBattery(int currPwrLvl, int time)
{
    if (time > 0) {
        battery->decreaseLevel(currPwrLvl*time);
    }
}

int Device::runTreatment () {}

