#ifndef GAITGROUP_H
#define GAITGROUP_H

#include "../includes/Enums.h"

class GaitGroup
{
private:
    LEG *mLegIndices;
    int mLegIndicesSize;
    int mStartTime;
    int mPauseDur;

public:
    GaitGroup(){};
    GaitGroup(LEG *legIndices, int legIndicesSize, int pauseDur = 0);
    void setStartTime(int startTime, int stepDur = 0, int timeOffset = 0);
    int getStartTime();
    int getPauseDur();
    LEG *getLegIndices();
    int getLegIndicesSize();
};

#endif