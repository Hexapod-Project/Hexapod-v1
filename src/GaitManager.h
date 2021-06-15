#ifndef GAITMANAGER_H
#define GAITMANAGER_H

#include "Hexapod.h"
#include "Gait.h"

class Hexapod;

class GaitManager
{
private:
    Hexapod *mTarget;

    GAITTYPE mCurrGaitType;
    Gait mCurrGait;

    MOVESTATE mMoveState = MOVESTATE::IDLE;
    ROTATEDIR mRotateDir = ROTATEDIR::COUNTERCW;

    float mWalkDir = M_PI_2;

    bool mIsStopping = false;

    int mStoppedGroupCount = 0;
    GAITGROUPSTATE mGroupState[16];
    float mGroupMoveDir[16];

    Gait mGaits[GAITTYPE::Count];

    void restartGait();
    void changeAllGroupStates(GAITGROUPSTATE groupState);

    int mGrpIdx, mLegIdx, mLegIndicesSize, mCurrTime, mStartTime;
    GaitGroup *mCurrGroup, *mPrevGroup;
    LEG *mLegIndices;
    float mTimeLapsed, mTimeLapsedRatio;

public:
    GaitManager(Hexapod *target);
    void initGaits();
    void startGait(GAITTYPE gaitType = GAITTYPE::TRIPOD);
    void runGait(Vec3 dir = Vec3());
    void stopGait();
    void stopGaitImmediate();
    GAITTYPE getGaitType();
    void setGaitType(GAITTYPE gaitType, GAITGROUPSTATE groupState = GAITGROUPSTATE::MOVING);
    void setWalkDir(float walkDir);
    void setRotateDir(ROTATEDIR rotateDir);
    ROTATEDIR getRotateDir();
    MOVESTATE getMoveState();
    bool isWalking();
    bool isMoving();
    bool isStopping();
    int getStepDur();

    int mCurrGaitGroupSize;
};

#endif