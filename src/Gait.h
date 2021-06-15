#ifndef GAIT_H
#define GAIT_H

#include "GaitGroup.h"

class Gait
{
private:
    GaitGroup *mGaitGroups;
    int mGaitGroupSize;
    int mTimeOffset;
    int mStepDur;

public:
    void setGroups(GaitGroup *gaitGroups, int gaitGroupSize);
    int getGroupSize();
    void initStartTime(int startTime, int stepDur);
    void setTimeOffset(int timeOffset);
    int getTimeOffset();
    void setStepDur(int stepDur);
    int getStepDur();
    GaitGroup *getGroup(int idx);
};

#endif