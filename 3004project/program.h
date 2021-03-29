#ifndef PROGRAM_H
#define PROGRAM_H

#include <QString>
#include "therapy.h"

using namespace std;

class Program : public Therapy
{
public:
    Program();
    ~Program();
private:
    QString name;
    int frequency;
};

#endif // PROGRAM_H
