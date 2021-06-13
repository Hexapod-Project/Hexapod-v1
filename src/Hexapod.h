#ifndef HEXAPOD_H
#define HEXAPOD_H

#include "Leg.h"
#include "Node.h"

class Hexapod
{
private:
    Node mBody;
    Leg mLegs[6];

public:
    void setup();
    void update();
};

#endif