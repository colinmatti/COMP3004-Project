#ifndef FREQUENCY_H
#define FREQUENCY_H

#include "therapy.h"

class Frequency : public Therapy {
public:
    Frequency(float f, int t, int p) : Therapy(f, t, p) {};
};

#endif // FREQUENCY_H
