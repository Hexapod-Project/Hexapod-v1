#ifndef LEG_H
#define LEG_H

#include "Datatypes.h"
#include "Adafruit_PWMServoDriver.h"

class Leg
{
private:
    Adafruit_PWMServoDriver *mServoDriver;
    uint8_t mHipPin, mFemurPin, mTibiaPin;

    Vec3 mStartFootPos;
    Vec3 mTargetFootPos;

    Vec3 mStartPos;
    float mStartAngle;

    Mat4 mBaseMatrix;
    Mat4 *mRootMatrix = new Mat4();

    float mHipAngle;
    float mFemurAngle;
    float mTibiaAngle;

public:
    void setBase(Vec3 pos, float angle);
    void setRoot(Mat4 *matrix);
    void attach(uint8_t hipPin, uint8_t femurPin, uint8_t tibiaPin, Adafruit_PWMServoDriver* servoDriver);
    void setStartFootPos(Vec3 startPos);
    void setTargetFootPos(Vec3 targetPos);
    void calculateJointAngles();
    void updateServoAngles();
    void setAngles(float hipAngle, float femurAngle, float tibiaAngle);
    void resetFootTargetPos();
    Vec3 getTargetFootPos();
    Vec3 getStartFootPos();
    Vec3 getAngles();
};

#endif
