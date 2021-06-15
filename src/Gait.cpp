#include "Gait.h"

void Gait::setGroups(GaitGroup *gaitGroups, int gaitGroupSize)
{
    mGaitGroups = gaitGroups;
    mGaitGroupSize = gaitGroupSize;
}

void Gait::initStartTime(int startTime, int stepDur)
{
    for (int grpIdx = 0; grpIdx < mGaitGroupSize; grpIdx++)
    {
        if (grpIdx > 0)
        {
            GaitGroup prevGroup = mGaitGroups[grpIdx - 1];
            int pauseDur = prevGroup.getPauseDur();
            mGaitGroups[grpIdx].setStartTime(prevGroup.getStartTime() + pauseDur, stepDur, mTimeOffset);
        }
        else
            mGaitGroups[grpIdx].setStartTime(startTime);
    }
}

void Gait::setTimeOffset(int timeOffset)
{
    mTimeOffset = timeOffset;
}

int Gait::getTimeOffset()
{
    return mTimeOffset;
}

int Gait::getGroupSize()
{
    return mGaitGroupSize;
}

GaitGroup *Gait::getGroup(int idx)
{
    return &mGaitGroups[idx];
}

void Gait::setStepDur(int stepDur)
{
    mStepDur = stepDur;
}

int Gait::getStepDur()
{
    return mStepDur;
}