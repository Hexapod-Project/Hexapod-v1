#include "GaitManager.h"
#include <Arduino.h>

const String LEG_NAMES[]{"FRONTRIGHT", "MIDRIGHT", "BACKRIGHT", "BACKLEFT", "MIDLEFT", "FRONTLEFT"};

GaitManager::GaitManager(Hexapod *target)
{
    mTarget = target;

    initGaits();
}

void GaitManager::initGaits()
{
    mGaits[TRIPOD].setStepDur(BASE_STEP_DUR / 2);
    mGaits[TRIPOD].setGroups(new GaitGroup[2]{
                                 GaitGroup(new LEG[3]{FRONTLEFT, MIDRIGHT, BACKLEFT}, 3),
                                 GaitGroup(new LEG[3]{FRONTLEFT, MIDRIGHT, BACKLEFT}, 3)},
                             2);

    mGaits[RIPPLE].setStepDur(BASE_STEP_DUR / 3);
    mGaits[RIPPLE].setTimeOffset(-BASE_STEP_DUR / 6);
    mGaits[RIPPLE].setGroups(new GaitGroup[6]{
                                 GaitGroup(new LEG[1]{FRONTRIGHT}, 1),
                                 GaitGroup(new LEG[1]{MIDRIGHT}, 1),
                                 GaitGroup(new LEG[1]{BACKRIGHT}, 1),
                                 GaitGroup(new LEG[1]{BACKLEFT}, 1),
                                 GaitGroup(new LEG[1]{MIDLEFT}, 1),
                                 GaitGroup(new LEG[1]{FRONTLEFT}, 1)},
                             6);
    
    mGaits[TRIPLE].setStepDur(BASE_STEP_DUR / 3);
    mGaits[TRIPLE].setTimeOffset(-BASE_STEP_DUR/13.5);
    int triplePauseDur = (7 / 20) * mGaits[GAITTYPE::TRIPLE].getStepDur();
    mGaits[TRIPLE].setGroups(new GaitGroup[6]{
                                 GaitGroup(new LEG[1]{FRONTLEFT}, 1),
                                 GaitGroup(new LEG[1]{MIDLEFT}, 1),
                                 GaitGroup(new LEG[1]{BACKLEFT}, 1, triplePauseDur),
                                 GaitGroup(new LEG[1]{FRONTRIGHT}, 1),
                                 GaitGroup(new LEG[1]{MIDRIGHT}, 1),
                                 GaitGroup(new LEG[1]{BACKLEFT}, 1, triplePauseDur)},
                             6);

    mGaits[WAVE].setStepDur(BASE_STEP_DUR / 3);
    mGaits[WAVE].setTimeOffset(-BASE_STEP_DUR / 18);
    mGaits[WAVE].setGroups(new GaitGroup[6]{
                                 GaitGroup(new LEG[1]{FRONTLEFT}, 1),
                                 GaitGroup(new LEG[1]{MIDLEFT}, 1),
                                 GaitGroup(new LEG[1]{BACKLEFT}, 1),
                                 GaitGroup(new LEG[1]{FRONTRIGHT}, 1),
                                 GaitGroup(new LEG[1]{MIDRIGHT}, 1),
                                 GaitGroup(new LEG[1]{BACKRIGHT}, 1)},
                             6);
}

void GaitManager::startGait(GAITTYPE gaitType)
{
    if(mIsStopping)
        return;

    mMoveState = MOVE;

    setGaitType(gaitType);

    mCurrGait.initStartTime(millis(), mCurrGait.getStepDur());

    for(mGrpIdx = 0; mGrpIdx < mCurrGaitGroupSize; mGrpIdx++)
    {
        mCurrGroup = mCurrGait.getGroup(mGrpIdx);
        mStartTime = mCurrGroup->getStartTime();
        mLegIndices = mCurrGroup->getLegIndices();
        mLegIndicesSize = mCurrGroup->getLegIndicesSize();
        for(int footIdx = 0; footIdx < mLegIndicesSize; footIdx++)
            mTarget->setNextStep(mLegIndices[footIdx], mStartTime);
    }
}

void GaitManager::runGait(Vec3 dir)
{
    mCurrTime = millis();

    for(mGrpIdx = 0; mGrpIdx < mCurrGaitGroupSize; mGrpIdx++)
    {
        GaitGroup *currGroup = mCurrGait.getGroup(mGrpIdx);

        mStartTime = currGroup->getStartTime();

        mTimeLapsed = mCurrTime - mStartTime;
        mTimeLapsedRatio = mTimeLapsed / mCurrGait.getStepDur();

        mLegIndices = currGroup->getLegIndices();
        GAITGROUPSTATE currGroupState = mGroupState[mGrpIdx];

        if(mTimeLapsedRatio >= 1)
        {
            if(currGroupState == GAITGROUPSTATE::MOVING)
            {
                mPrevGroup = mCurrGait.getGroup(mGrpIdx > 0 ? mGrpIdx - 1 : mCurrGaitGroupSize - 1);
                currGroup->setStartTime(mPrevGroup->getStartTime() + mPrevGroup->getPauseDur(), mCurrGait.getStepDur(), mCurrGait.getTimeOffset());

                if(mIsStopping && mGroupState[mGrpIdx] != GAITGROUPSTATE::STOPPING)
                    mGroupState[mGrpIdx] = GAITGROUPSTATE::STOPPING;
            }
            else if (currGroupState == GAITGROUPSTATE::STOPPING)
            {
                mGroupState[mGrpIdx] = GAITGROUPSTATE::STOPPED;
                mStoppedGroupCount ++;

                if(mStoppedGroupCount >= mCurrGaitGroupSize)
                {
                    mMoveState = MOVESTATE::IDLE;
                    mIsStopping = false;
                }
            }
        }

        if(mTimeLapsedRatio < 0 || mTimeLapsedRatio >= 1)
        {
            mLegIndicesSize = currGroup->getLegIndicesSize();
            for(mLegIdx = 0; mLegIdx < mLegIndicesSize; mLegIdx ++)
                mTarget->setNextStep(mLegIndices[mLegIdx], mStartTime, mIsStopping);
        }
    }
}

void GaitManager::stopGait()
{
    if(mIsStopping || mMoveState == MOVESTATE::IDLE)
        return;

    mIsStopping = true;

    mStoppedGroupCount = 0;
}

void GaitManager::stopGaitImmediate()
{
    mMoveState = MOVESTATE::IDLE;
    mIsStopping = false;
}

GAITTYPE GaitManager::getGaitType()
{
    return mCurrGaitType;
}

void GaitManager::setGaitType(GAITTYPE gaitType, GAITGROUPSTATE groupState)
{
    mCurrGaitType = gaitType;
    mCurrGait = mGaits[gaitType];
    mCurrGaitGroupSize = mCurrGait.getGroupSize();

    changeAllGroupStates(groupState);    
}

void GaitManager::setWalkDir(float walkDir)
{
    mWalkDir = walkDir;
    mTarget->changeDir(walkDir, mCurrGaitGroupSize, millis());
}

void GaitManager::setRotateDir(ROTATEDIR rotateDir)
{
    if(mRotateDir != rotateDir)
        mRotateDir = rotateDir;
}

ROTATEDIR GaitManager::getRotateDir()
{
    return mRotateDir;
}

void GaitManager::changeAllGroupStates(GAITGROUPSTATE groupState)
{
    for(mGrpIdx = 0; mGrpIdx < mCurrGaitGroupSize; mGrpIdx++)
        mGroupState[mGrpIdx] = groupState;
}

MOVESTATE GaitManager::getMoveState()
{
    return mMoveState;
}

bool GaitManager::isWalking()
{
    return mMoveState == MOVESTATE::MOVE;
}

bool GaitManager::isMoving()
{
    return mMoveState != MOVESTATE::IDLE;
}

bool GaitManager::isStopping()
{
    return mIsStopping;
}

int GaitManager::getStepDur()
{
    return mCurrGait.getStepDur();
}