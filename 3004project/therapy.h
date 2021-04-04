#ifndef THERAPY_H
#define THERAPY_H

#include <QString>

class Therapy {
public:
    float getFrequency() { return frequency; };
    int getTimer() { return timer; };
    int getPowerLevel() { return powerLevel; };

    virtual QString getName() = 0;
    virtual QString getType() = 0;

protected:
    Therapy(int f, int p, int t): frequency(f), timer(t), powerLevel(p) {};

    float frequency;
    int timer;
    int powerLevel;
};

#endif // THERAPY_H
