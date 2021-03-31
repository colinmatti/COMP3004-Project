#ifndef PROGRAM_H
#define PROGRAM_H

#include "therapy.h"

#include <QString>

using namespace std;

class Program : public Therapy {
public:
    Program(QString n, float f, int t, int p) : Therapy(f, t, p), name(n) {}
    QString name; // MAKE PROTECTED
};

#endif // PROGRAM_H
