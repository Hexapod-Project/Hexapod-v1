#ifndef TOOLS_H
#define TOOLS_H

#include "Datatypes.h"

float toPositiveDeg(float deg);
float toPositiveRad(float rad);
float clampTo360Deg(float deg);
float clampTo360Rad(float rad);
bool compareFloats(float a, float b, float precision = 0.00001);
float normalizeTimelapsed(unsigned long startTime, int dur);
float getSmallestRad(float rad);
Vec2 normalizeJoystickPos(Vec2 pos);
Vec3 rotateAroundY(Vec3 point, float rad);
uint16_t radToPos(float rad);
uint16_t degToPos(float deg);
uint16_t radToUs(float rad);
uint16_t degToUs(uint16_t deg);
Vec2 degreesToJoyStickPos(float deg);
float jyStkAngleToRad(uint8_t jyStkDeg);

#endif