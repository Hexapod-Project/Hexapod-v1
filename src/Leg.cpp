#include "Leg.h"
#include <math.h>
#include "../includes/HexapodConstants.h"
#include "Tools.h"
#include <HardwareSerial.h>

extern HardwareSerial Serial;

void Leg::setBase(Vec3 pos, float angle)
{
    mStartPos = pos;

    // 90deg is middle of the servos max angle of rotation (which is the default angle of the leg)
    mStartAngle = angle;

    mBaseMatrix = mBaseMatrix.translate(pos).rotate(Vec3(0, -mStartAngle, 0));
}

void Leg::setRoot(Mat4 *matrix)
{
    mRootMatrix = matrix;
}

void Leg::setServos(uint8_t hip, uint8_t femur, uint8_t tibia)
{
    mHipServoId = hip - 1;
    mFemurServoId = femur - 1;
    mTibiaServoId = tibia - 1;
}

void Leg::attach(uint8_t hipPin, uint8_t femurPin, uint8_t tibiaPin, Adafruit_PWMServoDriver *servoDriver)
{
    mHipAngle = START_HIP_ANGLE;
    mFemurAngle = START_FEMUR_ANGLE;
    mTibiaAngle = START_TIBIA_ANGLE;

    mHipPin = hipPin;
    mFemurPin = femurPin;
    mTibiaPin = tibiaPin;

    mServoDriver = servoDriver;

    mDriverPrescale = mServoDriver->readPrescale();

    updateServoAngles();
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
        tibiaAngle = M_PI - acos(tibiaAcosVal);
    }

    hipAngle = M_PI_2 - hipAngle;

    if (!isnan(hipAngle))
        mHipAngle = clampTo360Deg(hipAngle * RAD_TO_DEG);

    if (!isnan(femurAngle))
        mFemurAngle = clampTo360Deg(femurAngle * RAD_TO_DEG);

    if (!isnan(tibiaAngle))
        mTibiaAngle = clampTo360Deg(tibiaAngle * RAD_TO_DEG);
}

void Leg::updateServoAngles()
{
    checkInterpolationAngle(mHipAngle, mHipTargetAngle);
    checkInterpolationAngle(mFemurAngle, mFemurTargetAngle);
    checkInterpolationAngle(mTibiaAngle, mTibiaTargetAngle);

    setAngles(mHipAngle, mFemurAngle, mTibiaAngle);
}

void Leg::checkInterpolationAngle(float &angle, float &targetAngle)
{
    if (targetAngle >= 0)
    {
        if (fabs(targetAngle - angle) > 0.01)
        {
            angle += (targetAngle - angle) * LEG_INTERPOLATION;
        }
        else
        {
            angle = targetAngle;
            targetAngle = -1;
        }
    }
}

void Leg::setInterpolatedAngles(float hipAngle, float femurAngle, float tibiaAngle)
{
    mHipTargetAngle = hipAngle;
    mFemurTargetAngle = femurAngle;
    mTibiaTargetAngle = tibiaAngle;

    Serial.println(String(hipAngle) + ", " + String(femurAngle) + ", " + String(tibiaAngle));
}

void Leg::setAngles(float hipAngle, float femurAngle, float tibiaAngle)
{
    if (tibiaAngle > MAX_TIBIA_ANGLE)
        tibiaAngle = MAX_TIBIA_ANGLE;

    if (hipAngle > MAX_HIP_ANGLE)
        hipAngle = MAX_HIP_ANGLE;
    else if (hipAngle < MIN_HIP_ANGLE)
        hipAngle = MIN_HIP_ANGLE;    

    mServoDriver->setPWM(mHipPin, 0, degToPWM(hipAngle, SERVO_US[mHipServoId], mDriverPrescale));
    mServoDriver->setPWM(mFemurPin, 0, degToPWM(femurAngle, SERVO_US[mFemurServoId], mDriverPrescale));
    mServoDriver->setPWM(mTibiaPin, 0, degToPWM(tibiaAngle, SERVO_US[mTibiaServoId], mDriverPrescale));
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

Vec3 Leg::getAngles()
{
    return Vec3(mHipAngle, mFemurAngle, mTibiaAngle);
}

bool Leg::isFinishedInterpolation()
{
    return mHipTargetAngle == -1 && mFemurTargetAngle == -1 && mTibiaTargetAngle == -1;
}