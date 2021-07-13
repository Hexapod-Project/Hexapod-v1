#ifndef GAIT_H
#define GAIT_H

#include "GaitGroup.h"

struct Gait {
    GaitGroup* mGaitGroups;
    int mGaitGroupsSize;

    Gait(){};
    Gait(GaitGroup* gaitGroups, int gaitGroupSize);
};
#endif