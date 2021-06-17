#ifndef HEXAPOD_H
#define HEXAPOD_H

#include "Leg.h"
#include "../includes/HexapodConstants.h"

class GaitManager;

class Hexapod
{
private:
    Vec3 mStartBodyPos;
    Vec3 mStartBodyRot;
    Vec3 mBodyPos;
    Vec3 mBodyRot;

    Mat4 mBaseMatrix;
    Mat4 mRootMatrix;

    Leg mLegs[LEG_COUNT];
    Vec3 mLegStartPos[LEG_COUNT];

    LEG mLegSequence[2][3] = {
    {LEG::FRONTRIGHT, LEG::MIDLEFT, LEG::BACKRIGHT},
    {LEG::FRONTLEFT, LEG::MIDRIGHT, LEG::BACKLEFT}};

    uint8_t mLegSeqIdx;

    bool mIsChangeDir = false;
    float mCurrDir;
    float mCosMoveDir, mSinMoveDir;

    MOVESTATE mMoveState = MOVESTATE::STOPPED;
    unsigned long mStepStartTime;

    void walk();
    void resetFootPos();
    void resetBodyPos();

public:
    void setup();
    void updateLegs();
    void update();    
    void startWalk(float moveDir);
    void stopWalk();
};

#endif