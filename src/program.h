#ifndef PROGRAM_H
#define PROGRAM_H

#include "therapy.h"

#include <QString>

class Program : public Therapy {
public:
    Program(QString n, float f, int t) : Therapy(f, t), name(n) {}
    ~Program() {}
    QString getName() { return name; }
    QString getType() { return "Program"; }

private:
    QString name;
};

#endif // PROGRAM_H
