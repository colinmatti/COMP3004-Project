#ifndef PROGRAM_H
#define PROGRAM_H

#include <QString>
#include "therapy.h"

using namespace std;

class Program : public Therapy
{
public:
    Program(QString n, float f, int t, int p);
    //~Program();
    QString name;
};

#endif // PROGRAM_H
