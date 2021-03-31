#ifndef THERAPY_H
#define THERAPY_H

class Therapy
{
public:
    virtual ~Therapy();

protected:
    int timer;
    int powerLevel;
    float frequency;
};

#endif // THERAPY_H
