#ifndef FREQUENCY_H
#define FREQUENCY_H

#include "therapy.h"

class Frequency : public Therapy
{
public:
    Frequency(int f, int t, int p, int s);
    ~Frequency();
private:
    int frequency;
};

#endif // FREQUENCY_H
