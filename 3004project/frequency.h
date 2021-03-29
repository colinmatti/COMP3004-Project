#ifndef FREQUENCY_H
#define FREQUENCY_H

#include "therapy.h"

class Frequency : public Therapy
{
public:
    Frequency();
    ~Frequency();
private:
    int frequency;
};

#endif // FREQUENCY_H
