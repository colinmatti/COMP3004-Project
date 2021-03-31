#ifndef THERAPY_H
#define THERAPY_H

class Therapy {
public:
    float getFrequency() { return frequency; };
    int getTimer() { return timer; };
    int getPowerLevel() { return powerLevel; };

protected:
    Therapy(int t, int p, int f): frequency(f), timer(t), powerLevel(p) {};

    float frequency;
    int timer;
    int powerLevel;
};

#endif // THERAPY_H
