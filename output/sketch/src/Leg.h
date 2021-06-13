#ifndef LEG_H
#define LEG_H

#include "Joint.h"
#include "Datatypes.h"

class Leg : public Node
{
private:
    Joint mHipJoint;
    Joint mFemurJoint;
    Joint mTibiaJoint;    
    Node mFoot;    

public:
    Leg(){};
    Leg(Vec3 basePos, float baseAngle);
    void attach(int hipPin, int femurPin, int tibiaPin);
    void setFootTargetPos(Vec3 targetPos);
    Vec3 getFootWorldPos();
    void calculateJointAngles();
    void setup();
    void update();
    void test(float hipAngle, float femurAngle, float tibiaAngle);

    Vec3 mTargetFootPos;    
};

#endif
