#ifndef HEXAPOD_H
#define HEXAPOD_H

#include "Leg.h"
#include "GaitManager.h"
#include "../includes/HexapodConstants.h"

class GaitManager;

class Hexapod
{
private:
    GaitManager *mGaitManager;

    Vec3 mStartBodyPos;
    Vec3 mStartBodyRot;
    Vec3 mBodyPos;
    Vec3 mBodyRot;

    Mat4 mBaseMatrix;
    Mat4 mRootMatrix;

    Leg mLegs[LEG_COUNT];

    GAITTYPE mGaitType = GAITTYPE::TRIPOD;
    MOVETYPE mMoveType = MOVETYPE::WALK;
    bool mCrabMode = true;

    float mStartDir = M_PI_2;
    float mMoveDir = M_PI_2;
    float mFaceDir = M_PI_2;
    float mTargetDir = M_PI_2;
    float mChangeStartDir;
    float mChangeOffsetDir;
    float mChangeDirStartTime;
    float mChangeDirDur;

    Vec3 mStepStartPos[LEG_COUNT];
    Vec3 mStepBodyStartPos[LEG_COUNT];
    float mStepFootAngle[LEG_COUNT];
    Vec3 mStepOffsetPos[LEG_COUNT];
    int mStepStartTimes[LEG_COUNT];
    bool mStepFootIsStop[LEG_COUNT];
    
    void stop();
    void centerBody();
    void orientToFront();
    void resetFeetPos();
    void resetBodyPos();
    void resetBodyRot();
    void stepTowardsTarget();
    void orientBody();
    void setFeetToCurrPos(); 

    int mLegIdx;
    bool mIsMoving;
    float mTimeLapsedRatio, mNewFootAngle, mFootDist;
    Vec3 mStartFootPos, mCurrFootPos, mTargetFootPos, mCurrStepStartPos, 
    mCurrStepOffset, mBodyStepStartPos, mFootDiff, mOffset;

public:
    void setup();
    void update();
    void updateLegs();
    void setNextStep(int footIdx, int startTime, bool isStop = false);
    void changeDir(float walkDir, float grpSize, int startTime);
    void move(float walkDir);
};

#endif