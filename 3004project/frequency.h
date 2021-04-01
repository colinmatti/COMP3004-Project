#ifndef FREQUENCY_H
#define FREQUENCY_H

#include "therapy.h"

class Frequency : public Therapy {
public:
    Frequency(float f, int p, int t) : Therapy(f, p, t) {};
    QString getName() { return QString::number(frequency); };
    QString getType() { return "Frequency"; };
};

#endif // FREQUENCY_H
