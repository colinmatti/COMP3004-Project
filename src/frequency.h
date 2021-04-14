#ifndef FREQUENCY_H
#define FREQUENCY_H

#include "therapy.h"

class Frequency : public Therapy {
public:
    Frequency(float f, int t) : Therapy(f, t) {};

    QString getName() { return QString("%1 Hz").arg(QString::number(frequency)); }
    QString getType() { return "Frequency"; }
};

#endif // FREQUENCY_H
