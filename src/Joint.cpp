#include "Joint.h"

void Joint::attach(int pin)
{
    mServo.attach(pin);
}

void Joint::write(float angle)
{
    mCurrentRot = Vec3(mCurrentRot.mX, angle, mCurrentRot.mZ);
    mServo.write(angle * 57.3);
}