#include <Arduino.h>
#include "Tools.h"
#include "../includes/HexapodConstants.h"

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

float clampTo360Deg(float deg)
{
    if(fabs(deg) > 360)
        deg = copysign(fmod(fabs(deg), 360), deg);

    return deg;
}

float clampTo360Rad(float rad)
{
    if(fabs(rad) > 2 * M_PI)
        rad = copysign(fmod(fabs(rad), 2 * M_PI), rad);

    return rad;
}

bool compareFloats(float a, float b, float precision)
{
    return fabs(a - b) <= precision;
}

float normalizeTimelapsed(unsigned long startTime, int dur)
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

Vec2 normalizeJoystickPos(Vec2 pos)
{
    return (pos - Vec2(JOYSTICK_ZERO_POS)) / Vec2(JOYSTICK_MAXDIST);
}

Vec3 rotateAroundY(Vec3 point, float rad)
{
    float cosRad = cos(rad);
    float sinRad = sin(rad);

    return Vec3(point.mX * cosRad - sinRad * point.mZ, point.mY, point.mZ * cosRad + sinRad * point.mX);
}

uint16_t radToUs(float rad, ServoUS servoUS) {
    return map(rad * RAD_TO_DEG, 0, 180, servoUS.minUS, servoUS.maxUS);
}

uint16_t degToUs(uint16_t deg, ServoUS servoUS) {
    if(deg > 180)
        deg = 180;
    else if (deg < 0)
        deg = 0;
        
    return map(deg, 0, 180, servoUS.minUS, servoUS.maxUS);
}

uint16_t degToPWM(uint16_t deg, ServoUS servoUS, uint16_t prescale) {
    uint16_t us = degToUs(deg, servoUS);

    return roundf(us / ((1000000.0 * (prescale + 1)) / (float)DRIVER_FREQ));
}

Vec2 degreesToJoyStickPos(float deg)
{
    float rad = (deg * M_PI) / 180;
    Vec2 result = Vec2(cos(rad) * JOYSTICK_MAXDIST + JOYSTICK_ZERO_POS,
                         sin(rad) * JOYSTICK_MAXDIST + JOYSTICK_ZERO_POS);

    return result;
}

float joyStickAngleToRad(uint8_t joyStickDeg) {
    if(joyStickDeg == 0)
        return -1;

    return ((joyStickDeg - 1) / 254.0) * M_PI * 2;
}