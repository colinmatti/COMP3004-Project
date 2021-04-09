#ifndef THERAPY_H
#define THERAPY_H

#include <QString>

class Therapy {
public:
    float getFrequency() { return frequency; }
    int getTimer() { return timer; }

    virtual QString getName() = 0;
    virtual QString getType() = 0;

protected:
    Therapy(int f, int t): frequency(f), timer(t){};

    float frequency;
    int timer;
};

#endif // THERAPY_H
