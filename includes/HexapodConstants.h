#ifndef HEXAPODCONSTANTS_H
#define HEXAPODCONSTANTS_H

#define ENABLE_DEBUG_OUTPUT

#include "../includes/Enums.h"
#include "../src/Datatypes.h"
#include <math.h>

// All distance/length units are in Centimeter(cm)
const int LEG_COUNT = 6;

// Leg Angles
const float LEG_ANGLE_FRONTRIGHT = M_PI / 3;
const float LEG_ANGLE_MIDRIGHT = 0;
const float LEG_ANGLE_BACKRIGHT = M_PI * 2 - M_PI / 3;
const float LEG_ANGLE_FRONTLEFT = M_PI * 2 / 3;
const float LEG_ANGLE_MIDLEFT = M_PI;
const float LEG_ANGLE_BACKLEFT = M_PI + M_PI / 3;

const float AXIS_HEIGHT = 5.5f;

const float HIP_LENGTH = 3.65;
const float FEMUR_LENGTH = 7.9;
const float TIBIA_LENGTH = 10;

const float LEG_LENGTH = HIP_LENGTH + FEMUR_LENGTH + TIBIA_LENGTH;

const float HIP_LENGTH_SQR = HIP_LENGTH * HIP_LENGTH;
const float FEMUR_LENGTH_SQR = FEMUR_LENGTH * FEMUR_LENGTH;
const float TIBIA_LENGTH_SQR = TIBIA_LENGTH * TIBIA_LENGTH;

const float FEMURTIBIA_DIFF = fabs(FEMUR_LENGTH - TIBIA_LENGTH);
const float FEMUR_LENGTH_X2 = FEMUR_LENGTH * 2;
const float FEMURTIBIASQR_DIFF = FEMUR_LENGTH_SQR - TIBIA_LENGTH_SQR;
const float FEMURTIBIASQR_TOTAL = FEMUR_LENGTH_SQR + TIBIA_LENGTH_SQR;
const float FEMURTIBIA_PRODUCT_X2 = FEMUR_LENGTH * TIBIA_LENGTH * 2;

// The width of the head and back
/**
 * This is just used to determine the leg positions
 * Since it is an elongated hexagon, the width is the length of the hexagon's sides with radius of BODY_WIDTH
 */

const float BODY_Y_OFFSET = 0.5f;

// Leg Front Back X Offset
const float X_FB_LEG_OFFSET = cos(M_PI / 3) * 4.5;
const float X_MID_LEG_OFFSET = 4.5;
const float Y_LEG_OFFSET = AXIS_HEIGHT / 2 - BODY_Y_OFFSET;
// Leg Front Back Z offset
const float Z_FB_LEG_OFFSET = sin(M_PI / 3) * 4.5;

const uint8_t MAX_TIBIA_ANGLE = 90;

const uint8_t HIP_ANGLE_RANGE = 50;
const uint8_t MAX_HIP_ANGLE = 90 + HIP_ANGLE_RANGE;
const uint8_t MIN_HIP_ANGLE = 90 - HIP_ANGLE_RANGE;

const uint8_t START_HIP_ANGLE = 90;
const uint8_t START_FEMUR_ANGLE = 180;
const uint8_t START_TIBIA_ANGLE = MAX_TIBIA_ANGLE;

const float BODY_WIDTH = 8.5;
// The distance of the foot is the radius of a circle and the body's center is the origin
const float FOOT_DIST = BODY_WIDTH / 2 + HIP_LENGTH + FEMUR_LENGTH / 2.5;
const float FOOT_Y = 0;

// cos(LEG_ANGLE) * FOOT_DIST, 0, sin(LEG_ANGLE) * FOOT_DIST;
const Vec3 START_FOOT_POS_FRONTRIGHT = Vec3(cos(LEG_ANGLE_FRONTRIGHT) * FOOT_DIST, FOOT_Y, sin(LEG_ANGLE_FRONTRIGHT) * FOOT_DIST);
const Vec3 START_FOOT_POS_MIDRIGHT = Vec3(cos(LEG_ANGLE_MIDRIGHT) * FOOT_DIST, FOOT_Y, sin(LEG_ANGLE_MIDRIGHT) * FOOT_DIST);
const Vec3 START_FOOT_POS_BACKRIGHT = Vec3(cos(LEG_ANGLE_BACKRIGHT) * FOOT_DIST, FOOT_Y, sin(LEG_ANGLE_BACKRIGHT) * FOOT_DIST);
const Vec3 START_FOOT_POS_FRONTLEFT = Vec3(cos(LEG_ANGLE_FRONTLEFT) * FOOT_DIST, FOOT_Y, sin(LEG_ANGLE_FRONTLEFT) * FOOT_DIST);
const Vec3 START_FOOT_POS_MIDLEFT = Vec3(cos(LEG_ANGLE_MIDLEFT) * FOOT_DIST, FOOT_Y, sin(LEG_ANGLE_MIDLEFT) * FOOT_DIST);
const Vec3 START_FOOT_POS_BACKLEFT = Vec3(cos(LEG_ANGLE_BACKLEFT) * FOOT_DIST, FOOT_Y, sin(LEG_ANGLE_BACKLEFT) * FOOT_DIST);

const float RIGHT_FORWARD = 3 * M_PI / 4;
const float FORWARD = M_PI / 2;
const float LEFT_FORWARD = M_PI / 4;
const float RIGHT = M_PI;
const float LEFT = 0;
const float RIGHT_BACKWARD = 5 * M_PI / 4;
const float BACKWARD = 3 * M_PI / 2;
const float LEFT_BACKWARD = 7 * M_PI / 4;

// Defaults
const float CROUCH_HEIGHT = 3;
const float RISE_HEIGHT = 5;
const float BODY_TRANS_DIST = 2;
const float START_HEIGHT = CROUCH_HEIGHT;
const float START_ANGLE = M_PI_2;
const float MAX_PITCH = M_PI / 18;
const float MAX_ROLL = M_PI / 18;

// Walk properties
const int BASE_STEP_DURATION = 500;      // Duration in ms that one walk cycle takes to complete
const float MAXRAD_PERSTEP = M_PI_2 / 8; // Maximum angle of rotation per step

const float MIN_STEP_HEIGHT = 0.5;
const float STEP_DIST = 2;
const float BODY_TO_STEP_Y_RATIO = 0.667;

const int JOYSTICK_POSITIVE_MAXPOS = 255;
const int JOYSTICK_NEGATIVE_MAXPOS = 1;
const int JOYSTICK_MAXDIST = 127;
const int JOYSTICK_ZERO_POS = 128;

// Servo driver properties
const uint8_t SERVO_FREQ = 50;
const uint32_t DRIVER_FREQ = 27000000;

// Servo PWMs
const ServoUS SERVO_US[] = {
    ServoUS(593, 2561),
    ServoUS(605, 2583),
    ServoUS(610, 2500),
    ServoUS(529, 2501),
    ServoUS(513, 2479),
    ServoUS(554, 2462),
    ServoUS(514, 2446),
    ServoUS(571, 2517),
    ServoUS(567, 2489),
    ServoUS(585, 2525),
    ServoUS(509, 2443),
    ServoUS(573, 2493),
    ServoUS(528, 2502),
    ServoUS(650, 2584),
    ServoUS(623, 2481),
    ServoUS(435, 2433),
    ServoUS(502, 2456),
    ServoUS(587, 2479),
    ServoUS(476, 2446),
    ServoUS(528, 2488)
};

const float LEG_INTERPOLATION = 0.05f;

#endif