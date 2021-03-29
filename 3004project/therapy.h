#ifndef THERAPY_H
#define THERAPY_H

class Therapy
{

public:
    virtual ~Therapy();

private:
    int timer;
    int powerLevel;
    int status;
};

#endif // THERAPY_H
