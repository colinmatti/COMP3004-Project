#ifndef THERAPY_H
#define THERAPY_H

#include <QString>

class Therapy {
public:
    Therapy(float f, int t): frequency(f), timer(t) {}
    virtual ~Therapy() {}

    float getFrequency() { return frequency; }
    int getTimer() { return timer; }

    virtual QString getName() = 0;
    virtual QString getType() = 0;

protected:
    float frequency;
    int timer;
};

#endif // THERAPY_H
