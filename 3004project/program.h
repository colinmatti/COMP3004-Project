#ifndef PROGRAM_H
#define PROGRAM_H

#include "therapy.h"

#include <QString>

using namespace std;

class Program : public Therapy {
public:
    Program(QString n, float f, int t, int p) : Therapy(f, p, t), name(n) {}
    QString getName() { return name; };
    QString getType() { return "Program"; };

private:
    QString name;
};

#endif // PROGRAM_H
