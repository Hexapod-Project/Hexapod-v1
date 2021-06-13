#include "Leg.h"
#include <math.h>

Leg::Leg(Vec3 basePos, float baseAngle)
{
    setBase(basePos, Vec3(0, baseAngle, 0));

    mHipJoint.setBase(Vec3(), Vec3());
    mFemurJoint.setBase(Vec3(3.8, 0, 0), Vec3(1.57, 0.0, 0.0));
    mTibiaJoint.setBase(Vec3(4.2, 0, 0), Vec3());
    mFoot.setBase(Vec3(8.1, 0, 0), Vec3());
}

void Leg::setup()
{
    setChild(&mHipJoint);
    mHipJoint.setChild(&mFemurJoint);
    mFemurJoint.setChild(&mTibiaJoint);
    mTibiaJoint.setChild(&mFoot);
}

void Leg::attach(int hipPin, int femurPin, int tibiaPin)
{
    mHipJoint.attach(hipPin);
    mFemurJoint.attach(femurPin);
    mTibiaJoint.attach(tibiaPin);
}

void Leg::setFootTargetPos(Vec3 targetPos)
{
    mTargetFootPos = targetPos;
}

Vec3 Leg::getFootWorldPos()
{
    return mFoot.getWorldPos();
}

void Leg::calculateJointAngles()
{
    Mat4 inverseWorldMatrix = mWorldMatrix.inverse();    

    Vec3 localTargetFootPos = inverseWorldMatrix.multiply(Vec4(mTargetFootPos, 1));    

    Vec3 localFootPos = mFoot.getLocalPos();    

    Vec3 footDiff = Vec3((localFootPos.mX - localTargetFootPos.mX), 
    fabs(localFootPos.mX - localTargetFootPos.mY), fabs(localFootPos.mZ - localTargetFootPos.mZ));

    if(footDiff.mX <= 0.0001 && footDiff.mY <= 0.0001 && footDiff.mZ <= 0.0001)
        return;

    Vec3 localHipPos = mHipJoint.getLocalPos(inverseWorldMatrix);
    Vec3 localFemurPos = mFemurJoint.getLocalPos(inverseWorldMatrix);
    Vec3 localTibiaPos = mTibiaJoint.getLocalPos(inverseWorldMatrix);

    Vec3 targetFootPosToHipDiff = localTargetFootPos - localHipPos;
    float hipAngle = - atan2(targetFootPosToHipDiff.mZ, targetFootPosToHipDiff.mX);

    if(!isnanf(hipAngle))
        mHipJoint.write(hipAngle);

    Vec3 verificationDiff = Vec3(fabs(localTargetFootPos.mX) - fabs(localFemurPos.mX), 
    fabs(localTargetFootPos.mY) - fabs(localFemurPos.mY), fabs(localTargetFootPos.mZ) - fabs(localFemurPos.mZ));

    if(!(verificationDiff.mX < 0 && fabs(verificationDiff.mZ) <= 0.00001 || verificationDiff.mZ < 0 && fabs(verificationDiff.mX) <= 0.00001))
    {
        Vec3 targetFootPosToFemurDiff = localTargetFootPos - localFemurPos;
        float dist = targetFootPosToFemurDiff.magnitude();

        if(dist <= 0)
            dist = 0.00001;
        else if(dist > 16.1)
            dist = 16.1;
        else if(dist < 3.9)
            dist = 3.9;

        float distSqr = dist * dist;

        float distXZ = sqrt(targetFootPosToFemurDiff.mX * targetFootPosToFemurDiff.mX + targetFootPosToFemurDiff.mZ * targetFootPosToFemurDiff.mZ);
        float femurToTargetAngle = atan2(targetFootPosToFemurDiff.mY, distXZ);        

        float femurAcosVal = (distSqr - 47.97) / (35.28 * dist);
        float femurAngle = acos(femurAcosVal) + femurToTargetAngle;

        float tibiaAngle = 0;
        if(dist < 16.1)
        {
            float tibiaAcosVal = (83.25 - distSqr) / 68.04;
            tibiaAngle = acos(tibiaAcosVal) - M_PI;
        }

        if(!isnanf(femurAngle))
            mFemurJoint.write(femurAngle);

        if(!isnanf(tibiaAngle))
            mTibiaJoint.write(tibiaAngle);
    }
}

void Leg::update()
{
    calculateJointAngles();
    
    updateMatrix();
    mHipJoint.updateMatrix();
    mFemurJoint.updateMatrix();
    mTibiaJoint.updateMatrix();
    mFoot.updateMatrix();
}

void Leg::test(float hipAngle, float femurAngle, float tibiaAngle)
{
    mHipJoint.write(hipAngle);
    mFemurJoint.write(femurAngle);
    mTibiaJoint.write(tibiaAngle);
}