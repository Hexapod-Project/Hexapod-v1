#ifndef TOOLS_H
#define TOOLS_H

#include "Datatypes.h"

float toPositiveDeg(float deg);
float toPositiveRad(float rad);
float clampTo360(float deg);
bool compareFloats(float a, float b, float precision = 0.00001);
float getTimeLapsedRatio(int startTime, int dur);
float getSmallestRad(float rad);
Vec2 getCentroid(Vec2* polygon, int size);

#endif