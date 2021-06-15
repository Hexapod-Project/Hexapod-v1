#include <Arduino.h>
#include "Tools.h"

float toPositiveDeg(float deg)
{
    if(deg < 0)
        deg = 360 + deg;

    return deg;
}

float toPositiveRad(float rad)
{
    if(rad < 0)
        rad = 6.284 + rad;

    return rad;
}

float clampTo360(float deg)
{
    if(deg > 360)
        deg -= 360;

    return deg;
}

bool compareFloats(float a, float b, float precision)
{
    return fabs(a - b) <= precision;
}

float getTimeLapsedRatio(int startTime, int dur)
{
    return (float)(millis() - startTime) / dur;
}

float getSmallestRad(float rad)
{
    if(rad > M_PI)
        rad -= M_PI * 2;
    else if (rad < -M_PI)
        rad += M_PI * 2;

    return rad;
}

Vec2 getCentroid(Vec2* polygon, int size)
{
    Vec2 sum;

    for(int i = 0; i < size; i++)
        sum += polygon[i];

    return sum/(float)size;
}