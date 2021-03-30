#ifndef PROGRAM_H
#define PROGRAM_H

#include <QString>
#include "therapy.h"

using namespace std;

class Program : public Therapy
{
public:
    Program(QString n, int f, int t, int p, int s);
    ~Program();
private:
    QString name;
    int frequency;
};

#endif // PROGRAM_H
