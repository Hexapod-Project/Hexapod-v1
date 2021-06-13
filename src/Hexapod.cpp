#include "Hexapod.h"
#include "../includes/Enums.h"

void Hexapod::setup()
{
    // mBody.setBase(Vec3(), Vec3());
    // mBody.mCurrentPos = Vec3(0, 2, 0);

    // mLegs[FRONTRIGHT] = Leg(Vec3(4.6, 2.3, 8.2), 1.05);
    // mLegs[MIDRIGHT] = Leg(Vec3(5.2, 2.3, 0), 0);
    // mLegs[BACKRIGHT] = Leg(Vec3(4.6, 2.3, -8.2), 5.24);
    // mLegs[FRONTLEFT] = Leg(Vec3(-4.8, 2.3, 8), 2.09);
    // mLegs[MIDLEFT] = Leg(Vec3(-5.9, 2.3, 0), 3.14);
    // mLegs[BACKLEFT] = Leg(Vec3(4.85, 2.3, -8.15), 4.19);

    mLegs[FRONTRIGHT].attach(2, 3, 4);
    mLegs[MIDRIGHT].attach(5, 6, 7);
    mLegs[BACKRIGHT].attach(8, 9, 10);
    mLegs[FRONTLEFT].attach(32, 33, 34);
    mLegs[MIDLEFT].attach(35, 36, 37);
    mLegs[BACKLEFT].attach(38, 39, 40);

    // mLegs[FRONTRIGHT].setFootTargetPos(Vec3(6.5, 0, 11.25));
    // mLegs[MIDRIGHT].setFootTargetPos(Vec3(13, 0, 0));
    // mLegs[BACKRIGHT].setFootTargetPos(Vec3(6.5, 0, -11.25));
    // mLegs[FRONTLEFT].setFootTargetPos(Vec3(-6.5, 0, 11.25));
    // mLegs[MIDLEFT].setFootTargetPos(Vec3(-6.5, 0, 0));
    // mLegs[BACKLEFT].setFootTargetPos(Vec3(-6.5, 0, -11.25));    
}

void Hexapod::update()
{
    for (Leg leg : mLegs)
        leg.update();
}