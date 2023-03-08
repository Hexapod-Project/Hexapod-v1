#ifndef LEG_H
#define LEG_H

#include "Datatypes.h"
#include "Adafruit_PWMServoDriver.h"

class Leg
{
private:
    Adafruit_PWMServoDriver *mServoDriver;
    uint8_t mDriverPrescale;

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

    float mHipTargetAngle = -1;
    float mFemurTargetAngle = -1;
    float mTibiaTargetAngle = -1;

    uint8_t mHipServoId, mFemurServoId, mTibiaServoId;  

    bool isLeft = false;  

public:
    void setBase(Vec3 pos, float angle);
    void setRoot(Mat4 *matrix);
    void setIsLeft(bool isLeft = true);
    void setServos(uint8_t hip, uint8_t femur, uint8_t tibia);
    void attach(uint8_t hipPin, uint8_t femurPin, uint8_t tibiaPin, Adafruit_PWMServoDriver* servoDriver);
    void setStartFootPos(Vec3 startPos);
    void setTargetFootPos(Vec3 targetPos);
    void calculateJointAngles();
    void updateServoAngles();
    void checkTargetAngle(float &angle, float &targetAngle);
    void setTargetAngles(float hipAngle, float femurAngle, float tibiaAngle);
    void setAngles(float hipAngle, float femurAngle, float tibiaAngle);
    void resetFootTargetPos();
    Vec3 getTargetFootPos();
    Vec3 getStartFootPos();
    Vec3 getAngles();
    bool isFinishedInterpolation();
};

#endif
