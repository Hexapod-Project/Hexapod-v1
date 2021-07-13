#include "GaitGroup.h"
#include "../includes/HexapodConstants.h"

GaitGroup::GaitGroup(LEG *legIndices, int legIndicesSize, float stepTimeOffset)
{
    mLegIndices = legIndices;
    mLegIndicesSize = legIndicesSize;
    mStepTimeOffset = stepTimeOffset;
    mStepDuration = BASE_STEP_DURATION * (1 + (mLegIndicesSize - 1) * mStepTimeOffset);
};
