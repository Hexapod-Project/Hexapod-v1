#include <HardwareSerial.h>
#include "Hexapod.h"
#include "Tools.h"
#include "../includes/Enums.h"
#include "../includes/HexapodConstants.h"

extern HardwareSerial Serial;
String inputStr;

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

    mLegs[FRONTRIGHT].setStartFootPos(START_FOOT_POS_FRONTRIGHT);
    mLegs[MIDRIGHT].setStartFootPos(START_FOOT_POS_MIDRIGHT);
    mLegs[BACKRIGHT].setStartFootPos(START_FOOT_POS_BACKRIGHT);
    mLegs[FRONTLEFT].setStartFootPos(START_FOOT_POS_FRONTLEFT);
    mLegs[MIDLEFT].setStartFootPos(START_FOOT_POS_MIDLEFT);
    mLegs[BACKLEFT].setStartFootPos(START_FOOT_POS_BACKLEFT);

    mStartBodyPos = Vec3(0, START_POS_LOW, 0);

    mBaseMatrix = mBaseMatrix.translate(mStartBodyPos);
    mRootMatrix = mBaseMatrix;

    //Calculate the angles first
    for (mLegIdx = 0; mLegIdx < LEG_COUNT; mLegIdx++)
    {
        mLegs[mLegIdx].setRoot(&mRootMatrix);
        mLegs[mLegIdx].calculateJointAngles();
    }

    _delay_ms(1000);

    //Then update all at once
    for (mLegIdx = 0; mLegIdx < LEG_COUNT; mLegIdx++)
        mLegs[mLegIdx].updateServoAngles();

    mGaitManager = new GaitManager(this);
}

void Hexapod::updateLegs()
{
    //Calculate the angles for all the legs first
    for (mLegIdx = 0; mLegIdx < LEG_COUNT; mLegIdx++)
        mLegs[mLegIdx].calculateJointAngles();

    //Then update all at once
    for (mLegIdx = 0; mLegIdx < LEG_COUNT; mLegIdx++)
        mLegs[mLegIdx].updateServoAngles();
}

void Hexapod::resetFeetPos()
{
    for (mLegIdx = 0; mLegIdx < LEG_COUNT; mLegIdx++)
        mLegs[mLegIdx].resetFootTargetPos();
}

void Hexapod::resetBodyPos()
{
    mBodyPos = mStartBodyPos;
    mRootMatrix = mBaseMatrix.rotate(mBodyRot);
}

void Hexapod::resetBodyRot()
{
    mMoveDir = mStartDir;
    mTargetDir = mStartDir;
    mFaceDir = mStartDir;
    mBodyRot = mStartBodyRot;
    mRootMatrix = mBaseMatrix.translate(mBodyPos);
}

void Hexapod::update()
{
    mIsMoving = mGaitManager->isMoving();

    if (mIsMoving)
    {
        mGaitManager->runGait();

        if(mMoveType == MOVETYPE::WALK)
            centerBody();

        stepTowardsTarget();
    }

    mRootMatrix = mBaseMatrix.translate(mBodyPos).rotate(mBodyRot);

    updateLegs();
}

void Hexapod::move(float dir)
{
    Serial.println("Move starting...");

    if (mGaitManager->isStopping())
        return;
    
    //TODO; Update movetype from serial

    if (!mGaitManager->isMoving() && (mMoveType == MOVETYPE::WALK || mMoveType == MOVETYPE::ROTATE && compareFloats(mFaceDir, dir)))
    {
        if (!mCrabMode || mMoveType == MOVETYPE::ROTATE)
            mTargetDir = mFaceDir;

        for (mLegIdx = 0; mLegIdx < LEG_COUNT; mLegIdx++)
        {
            mStepStartPos[mLegIdx] = mLegs[mLegIdx].getTargetFootPos();
            mStepOffsetPos[mLegIdx] = Vec3();
        }

        mGaitManager->setWalkDir(dir);
        mGaitManager->startGait(mGaitType);
    }
    else if (!compareFloats(mTargetDir, dir) || mMoveType == MOVETYPE::ROTATE && !compareFloats(mFaceDir, dir))
        mGaitManager->setWalkDir(dir);

    Serial.println("Move started");
}

void Hexapod::stop()
{
    if (mCrabMode || !mCrabMode && compareFloats(mTargetDir, mFaceDir))
        mGaitManager->stopGait();
}

void Hexapod::stepTowardsTarget()
{
    for (mLegIdx = 0; mLegIdx < LEG_COUNT; mLegIdx++)
    {
        mTimeLapsedRatio = getTimeLapsedRatio(mStepStartTimes[mLegIdx], mGaitManager->getStepDur());
        if(mTimeLapsedRatio > 1) mTimeLapsedRatio = 1;

        if (mTimeLapsedRatio >= 0)
        {
            mStartFootPos = mLegs[mLegIdx].getStartFootPos() + mBodyPos;
            mTargetFootPos = mLegs[mLegIdx].getTargetFootPos();
            mCurrStepStartPos = mStepStartPos[mLegIdx];
            mCurrStepOffset = mStepOffsetPos[mLegIdx];
            mBodyStepStartPos = mStepBodyStartPos[mLegIdx];

            //TODO: not Crab Mode

            mOffset = mCurrStepOffset * mTimeLapsedRatio;

            if (mMoveType == MOVETYPE::WALK || mMoveType == MOVETYPE::ROTATE && !compareFloats(mTargetDir, mFaceDir))
                mOffset.mY = sin(mTimeLapsedRatio * M_PI) * STEP_HEIGHT - mCurrStepStartPos.mY * mTimeLapsedRatio;
            else
            {
                mFootDist = mCurrStepOffset.mX * mCurrStepOffset.mX + mCurrStepOffset.mZ + mCurrStepOffset.mZ;

                if (mFootDist > 0.00001)
                    mOffset.mY = sin(mTimeLapsedRatio * M_PI) * mFootDist - mStepStartPos->mY * mTimeLapsedRatio;
                else
                    mGaitManager->stopGaitImmediate();
            }

            mTargetFootPos = mCurrStepStartPos + mOffset;

            mLegs[mLegIdx].setTargetFootPos(mTargetFootPos);
        }
    }
}

void Hexapod::setNextStep(int footIdx, int startTime, bool isStop)
{
    mStartFootPos = mLegs[mLegIdx].getStartFootPos() + mBodyPos;
    mCurrFootPos = mLegs[mLegIdx].getTargetFootPos();

    mFootDiff = mCurrFootPos - mStartFootPos;

    if (!isStop)
    {
        mStepOffsetPos[footIdx] = Vec3(cos(mMoveDir) * STEP_DIST - mFootDiff.mX, 0,
                                       sin(mMoveDir) * STEP_DIST - mFootDiff.mZ);

        mStepStartPos[footIdx] = mCurrFootPos;
        mStepBodyStartPos[footIdx] = mBodyPos;
        mStepFootIsStop[footIdx] = isStop;
        
        mStepStartTimes[footIdx] = startTime;
    }
}

void Hexapod::centerBody()
{
    Vec2 feetPolygon[LEG_COUNT];
    for(mLegIdx = 0; mLegIdx < LEG_COUNT; mLegIdx++)
    {
        mTargetFootPos = mLegs[mLegIdx].getTargetFootPos();
        feetPolygon->mX = mTargetFootPos.mX;
        feetPolygon->mY = mTargetFootPos.mZ;
    }

    Vec2 centroid = getCentroid(feetPolygon, LEG_COUNT); 

    mBodyPos.mX = centroid.mX;
    mBodyPos.mZ = centroid.mY;    
}

void Hexapod::changeDir(float walkDir, float grpSize, int startTime)
{

}