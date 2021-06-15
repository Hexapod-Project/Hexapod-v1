#include "Leg.h"
#include <math.h>
#include <HardwareSerial.h>
#include "../includes/HexapodConstants.h"
#include "../includes/Constants.h"
#include "Tools.h"

extern HardwareSerial Serial;

void Leg::setBase(Vec3 pos, float angle, bool isLeftLeg)
{
    mStartPos = pos;

    //90deg is middle of the servos max angle of rotation (which is the default angle of the leg)
    mStartAngle = angle;

    mBaseMatrix = mBaseMatrix.translate(pos);
}

void Leg::setRoot(Mat4 *matrix)
{
    mRootMatrix = matrix;
}

void Leg::attach(int hipPin, int femurPin, int tibiaPin)
{
    mHipAngle = START_HIP_ANGLE;
    mFemurAngle = START_FEMUR_ANGLE;
    mTibiaAngle = START_TIBIA_ANGLE;

    mHipServo.attach(hipPin);
    mHipServo.write(mHipAngle);

    mFemurServo.attach(femurPin);
    mFemurServo.write(mFemurAngle);

    mTibiaServo.attach(tibiaPin);
    mTibiaServo.write(mTibiaAngle);
}

void Leg::setStartFootPos(Vec3 startPos)
{
    mStartFootPos = startPos;
    mTargetFootPos = startPos;
}

void Leg::setTargetFootPos(Vec3 targetPos)
{
    mTargetFootPos = targetPos;
}

Vec3 Leg::getFootPos()
{
    return mFootPos;
}

void Leg::calculateJointAngles()
{
    Mat4 invMatrix = mRootMatrix->multiply(mBaseMatrix).inverse();
    Vec3 localTargetFootPos = invMatrix.multiply(Vec4(mTargetFootPos, 1));

    float hipAngle = atan2(localTargetFootPos.mZ, localTargetFootPos.mX);

    Vec3 localFemurPos = Vec3(cos(hipAngle) * HIP_LENGTH, 0, sin(hipAngle) * HIP_LENGTH);
    localTargetFootPos = localTargetFootPos - localFemurPos;

    float dist = localTargetFootPos.magnitude();

    if (dist <= 0)
        dist = 0.00001;
    else if (dist > LEG_LENGTH)
        dist = LEG_LENGTH;
    else if (dist < FEMURTIBIA_DIFF)
        dist = FEMURTIBIA_DIFF;

    float distSqr = dist * dist;

    float distXZ = sqrt(localTargetFootPos.mX * localTargetFootPos.mX + localTargetFootPos.mZ * localTargetFootPos.mZ);
    float femurToTargetAngle = atan2(localTargetFootPos.mY, distXZ);

    float femurAcosVal = (distSqr + FEMURTIBIASQR_DIFF) / (dist * FEMUR_LENGTH_X2);
    float femurAngle = acos(femurAcosVal) + femurToTargetAngle + M_PI_2;

    float tibiaAngle = 0;
    if (dist < LEG_LENGTH)
    {
        float tibiaAcosVal = (FEMURTIBIASQR_TOTAL - distSqr) / FEMURTIBIA_PRODUCT_X2;
        tibiaAngle = M_PI - acos(tibiaAcosVal) + TIBIA_ANGLE_OFFSET;
    }

    hipAngle = toPositiveRad(-(mStartAngle - toPositiveRad(hipAngle)) + M_PI_2);

    if (!isnanf(hipAngle))
        mHipAngle = clampTo360(hipAngle * RADTODEG);

    if (!isnanf(femurAngle))
        mFemurAngle = clampTo360(femurAngle * RADTODEG);

    if (!isnanf(tibiaAngle))
        mTibiaAngle = clampTo360(tibiaAngle * RADTODEG);
}

void Leg::updateServoAngles()
{
    setAngles(mHipAngle, mFemurAngle, mTibiaAngle);
}

void Leg::setAngles(float hipAngle, float femurAngle, float tibiaAngle)
{
    if(hipAngle > HIP_MAX_ANGLE)
        hipAngle = HIP_MAX_ANGLE;
    else if (hipAngle < HIP_MIN_ANGLE)
        hipAngle = HIP_MIN_ANGLE;

    mHipServo.write(hipAngle);
    mFemurServo.write(femurAngle);
    mTibiaServo.write(tibiaAngle);
}

void Leg::resetFootTargetPos()
{
    setTargetFootPos(mStartFootPos);
}

Vec3 Leg::getTargetFootPos()
{
    return mTargetFootPos;
}

Vec3 Leg::getStartFootPos()
{
    return mStartFootPos;
}