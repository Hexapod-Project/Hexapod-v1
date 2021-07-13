#ifndef GAITGROUP_H
#define GAITGROUP_H

#include "../includes/Enums.h"

struct GaitGroup
{
    LEG* mLegIndices;
    int mLegIndicesSize;
    int mStartTime;
    float mStepTimeOffset = 0;
    float mStepDuration;

    GaitGroup(){};
    GaitGroup(LEG* legIndices, int legIndicesSize, float stepTimeOffset = 0);
};

#endif