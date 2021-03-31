#include "program.h"
#include <vector>

Program::Program(QString n, int f, int t, int p, int s)
{
    name = n;
    frequency = f;
    timer = t;
    powerLevel = p;
    status = s;
}
