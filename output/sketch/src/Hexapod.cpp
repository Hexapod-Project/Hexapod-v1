#include <HardwareSerial.h>
#include "Hexapod.h"
#include "Tools.h"
#include "../includes/Enums.h"
#include "../includes/HexapodConstants.h"

extern HardwareSerial Serial;

void Hexapod::setup()
{
    mLegs[FRONTRIGHT].setBase(LEG_OFFSET_FRONTRIGHT, LEG_ANGLE_FRONTRIGHT);
    mLegs[MIDRIGHT].setBase(LEG_OFFSET_MIDRIGHT, LEG_ANGLE_MIDRIGHT);
    mLegs[BACKRIGHT].setBase(LEG_OFFSET_BACKRIGHT, LEG_ANGLE_BACKRIGHT);
    mLegs[FRONTLEFT].setBase(LEG_OFFSET_FRONTLEFT, LEG_ANGLE_FRONTLEFT);
    mLegs[MIDLEFT].setBase(LEG_OFFSET_MIDLEFT, LEG_ANGLE_MIDLEFT);
    mLegs[BACKLEFT].setBase(LEG_OFFSET_BACKLEFT, LEG_ANGLE_BACKLEFT);

    mLegs[FRONTRIGHT].attach(2, 3, 4);
    mLegs[MIDRIGHT].attach(5, 6, 7);
    mLegs[BACKRIGHT].attach(8, 9, 10);
    mLegs[FRONTLEFT].attach(32, 33, 34);
    mLegs[MIDLEFT].attach(35, 36, 37);
    mLegs[BACKLEFT].attach(38, 39, 40);

    _delay_ms(1000);

    mLegStartPos[FRONTRIGHT] = START_FOOT_POS_FRONTRIGHT;
    mLegStartPos[MIDRIGHT] = START_FOOT_POS_MIDRIGHT;
    mLegStartPos[BACKRIGHT] = START_FOOT_POS_BACKRIGHT;
    mLegStartPos[FRONTLEFT] = START_FOOT_POS_FRONTLEFT;
    mLegStartPos[MIDLEFT] = START_FOOT_POS_MIDLEFT;
    mLegStartPos[BACKLEFT] = START_FOOT_POS_BACKLEFT;

    mStartBodyPos = Vec3(0, START_POS_LOW, 0);

    mBaseMatrix = mBaseMatrix.translate(mStartBodyPos);
    mRootMatrix.set(mBaseMatrix);

    uint8_t legIdx;
    //Calculate the angles first
    for (legIdx = 0; legIdx < LEG_COUNT; legIdx++)
    {
        mLegs[legIdx].setStartFootPos(mLegStartPos[legIdx]);
        mLegs[legIdx].setRoot(&mRootMatrix);
        mLegs[legIdx].calculateJointAngles();
    }

    //Then update all at once
    for (legIdx = 0; legIdx < LEG_COUNT; legIdx++)
        mLegs[legIdx].updateServoAngles();

    _delay_ms(1000);
}

void Hexapod::updateLegs()
{
    uint8_t legIdx;

    //Calculate the angles for all the legs first
    for (legIdx = 0; legIdx < LEG_COUNT; legIdx++)
        mLegs[legIdx].calculateJointAngles();

    //Then update all at once
    for (legIdx = 0; legIdx < LEG_COUNT; legIdx++)
        mLegs[legIdx].updateServoAngles();
}

void Hexapod::resetFootPos()
{
    for (uint8_t legIdx = 0; legIdx < LEG_COUNT; legIdx++)
        mLegs[legIdx].setTargetFootPos(mLegStartPos[legIdx]);
}

void Hexapod::resetBodyPos()
{
    mBodyPos = Vec3();
    mBodyRot = Vec3();
    mRootMatrix.set(mBaseMatrix);
}

void Hexapod::update()
{
    if (mMoveState != MOVESTATE::STOPPED)
        walk();
}

void Hexapod::walk()
{
    float normalizedTimelapsed = normalizeTimelapsed(mStepStartTime, BASE_STEP_DUR);

    if (normalizedTimelapsed >= 1)
    {
        if (mMoveState != MOVESTATE::STOPPING)
        {
            mStepStartTime = millis();
            normalizedTimelapsed = 0;

            if(mMoveState == MOVESTATE::CHANGEDIR)
            {
                mCosMoveDir = cos(mCurrDir);
                mSinMoveDir = sin(mCurrDir);
            }

            if (mMoveState == MOVESTATE::START)
                mMoveState = MOVESTATE::MOVING;
            else if (mMoveState == MOVESTATE::STOPSTARTED)
                mMoveState = MOVESTATE::STOPPING;
            else if (mMoveState == MOVESTATE::CHANGEDIR)
                mMoveState = MOVESTATE::START;            

            mLegSeqIdx++;
            if (mLegSeqIdx > 1)
                mLegSeqIdx = 0;

            Vec3 rootPos = mRootMatrix.getPos();
            mBodyPos.mX = rootPos.mX;
            mBodyPos.mZ = rootPos.mZ;

            if (mIsChangeDir)
            {
                mIsChangeDir = false;
                mMoveState = MOVESTATE::CHANGEDIR;                
            }
        }
        else
        {
            mMoveState = MOVESTATE::STOPPED;
            return;
        }
    }

    if (normalizedTimelapsed >= 0)
    {
        float footY = sin(M_PI * normalizedTimelapsed) * STEP_HEIGHT;
        float baseStepOffset;

        if (mMoveState == MOVESTATE::START)
            baseStepOffset = STEP_DIST * normalizedTimelapsed;
        else if (mMoveState == MOVESTATE::STOPPING || mMoveState == MOVESTATE::CHANGEDIR)
            baseStepOffset = STEP_DIST * normalizedTimelapsed - STEP_DIST;
        else
            baseStepOffset = STEP_DIST_X2 * normalizedTimelapsed - STEP_DIST;

        Vec3 offset = Vec3(mCosMoveDir * baseStepOffset + mBodyPos.mX, footY, mSinMoveDir * baseStepOffset + mBodyPos.mZ);

        for (int i = 0; i < 3; i++)
        {
            int idx = mLegSequence[mLegSeqIdx][i];
            Vec3 newPos = mLegStartPos[idx] + offset;
            mLegs[idx].setTargetFootPos(newPos);
        }

        if (mMoveState != MOVESTATE::STOPPING && mMoveState != MOVESTATE::CHANGEDIR)
        {
            float baseBodyOffset = STEP_DIST * normalizedTimelapsed;
            mRootMatrix = mBaseMatrix.translate(mBodyPos + Vec3(mCosMoveDir * baseBodyOffset, 0, mSinMoveDir * baseBodyOffset));
        }

        updateLegs();
    }
}

void Hexapod::startWalk(float moveDir)
{
    if (mMoveState == MOVESTATE::STOPPED)
    {
        mMoveState = MOVESTATE::START;
        mLegSeqIdx = 0;
        mStepStartTime = millis();
        mCosMoveDir = cos(moveDir);
        mSinMoveDir = sin(moveDir);
        mCurrDir = moveDir;
    }
    else if (mMoveState == MOVESTATE::MOVING && !compareFloats(mCurrDir, moveDir))
    {
        mCurrDir = moveDir;
        mIsChangeDir = true;
    }
}

void Hexapod::stopWalk()
{
    mMoveState = MOVESTATE::STOPSTARTED;
}