#include "GaitGroup.h"

GaitGroup::GaitGroup(LEG *legIndices, int legIndicesSize, int pauseDur)
{
    mLegIndices = legIndices;
    mLegIndicesSize = legIndicesSize;
    mPauseDur = pauseDur;
}

void GaitGroup::setStartTime(int startTime, int stepDur, int timeOffset)
{
    mStartTime = startTime + timeOffset + stepDur;
}

int GaitGroup::getStartTime()
{
    return mStartTime;
}

int GaitGroup::getPauseDur()
{
    return mPauseDur;
}

LEG* GaitGroup::getLegIndices()
{
    return mLegIndices;
}

int GaitGroup::getLegIndicesSize()
{
    return mLegIndicesSize;
}