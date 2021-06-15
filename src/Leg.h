#ifndef LEG_H
#define LEG_H

#include <Servo.h>
#include "Datatypes.h"

class Leg
{
private:
    Servo mHipServo;
    Servo mFemurServo;
    Servo mTibiaServo;    
    
    Vec3 mFootPos;
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
    void setBase(Vec3 pos, float angle, bool isLeftLeg = false);
    void setRoot(Mat4 *matrix);
    void attach(int hipPin, int femurPin, int tibiaPin);
    void setStartFootPos(Vec3 startPos);
    void setTargetFootPos(Vec3 targetPos);
    Vec3 getFootPos();
    void calculateJointAngles();
    void updateServoAngles();
    void setAngles(float hipAngle, float femurAngle, float tibiaAngle); 
    void resetFootTargetPos();
    Vec3 getTargetFootPos();
    Vec3 getStartFootPos();    
};

#endif
