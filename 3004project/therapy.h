#ifndef THERAPY_H
#define THERAPY_H

class Therapy {
public:
    // virtual ~Therapy();
    // MAKE PROTECTED
    int timer;
    int powerLevel;

protected:
    Therapy(int t, int p, int f): timer(t), powerLevel(p), frequency(f) {};
    float frequency;
};

#endif // THERAPY_H
