#ifndef HEXAPODCONSTANTS_H
#define HEXAPODCONSTANTS_H

#include "../includes/Enums.h"
#include "../src/Datatypes.h"
#include <math.h>

//All distance/length units are in Centimeter(cm)
static const int LEG_COUNT = 6;

//Hexapod Dimensions
static const float BODY_WIDTH = 7;
static const float BODY_LENGTH = 16.9;

static const float HIP_DIST_FRONTRIGHT = 9.7;
static const float HIP_DIST_MIDRIGHT = 5.9;
static const float HIP_DIST_BACKRIGHT = 9.3;
static const float HIP_DIST_FRONTLEFT = 9.3;
static const float HIP_DIST_MIDLEFT = 5.7;
static const float HIP_DIST_BACKLEFT = 9.3;

static const float HIP_LENGTH = 3.8;
static const float FEMUR_LENGTH = 4.2;
static const float TIBIA_LENGTH = 8.1;

static const float HIP_LENGTH_SQR = HIP_LENGTH * HIP_LENGTH;
static const float FEMUR_LENGTH_SQR = FEMUR_LENGTH * FEMUR_LENGTH;
static const float TIBIA_LENGTH_SQR = TIBIA_LENGTH * TIBIA_LENGTH;

static const float FEMURTIBIA_DIFF = fabs(FEMUR_LENGTH - TIBIA_LENGTH);
static const float FEMUR_LENGTH_X2 = FEMUR_LENGTH * 2;
static const float FEMURTIBIASQR_DIFF = FEMUR_LENGTH_SQR - TIBIA_LENGTH_SQR;
static const float FEMURTIBIASQR_TOTAL = FEMUR_LENGTH_SQR + TIBIA_LENGTH_SQR;
static const float FEMURTIBIA_PRODUCT_X2 = FEMUR_LENGTH * TIBIA_LENGTH * 2;

static const float LEG_LENGTH = 16.1;
static const float FEMUR_TIBIA_DIFF = 3.9;

//Leg Angles
static const float LEG_ANGLE_FRONTRIGHT = 1.047;
static const float LEG_ANGLE_MIDRIGHT = 0;
static const float LEG_ANGLE_BACKRIGHT = 5.237;
static const float LEG_ANGLE_FRONTLEFT = 2.094;
static const float LEG_ANGLE_MIDLEFT = 3.142;
static const float LEG_ANGLE_BACKLEFT = 4.189;

static const float TIBIA_ANGLE_OFFSET = M_PI / 6;

static const float LEG_HEIGHT_OFFSET = 2.3;

//Leg Offsets
static const Vec3 LEG_OFFSET_FRONTRIGHT = Vec3(4.6, LEG_HEIGHT_OFFSET, 8.2);
static const Vec3 LEG_OFFSET_MIDRIGHT = Vec3(5.5, LEG_HEIGHT_OFFSET, 0);
static const Vec3 LEG_OFFSET_BACKRIGHT = Vec3(4.6, LEG_HEIGHT_OFFSET, -8.2);
static const Vec3 LEG_OFFSET_FRONTLEFT = Vec3(-4.6, LEG_HEIGHT_OFFSET, 8.2);
static const Vec3 LEG_OFFSET_MIDLEFT = Vec3(-5.5, LEG_HEIGHT_OFFSET, 0);
static const Vec3 LEG_OFFSET_BACKLEFT = Vec3(-4.6, LEG_HEIGHT_OFFSET, -8.2);

//Directions
static const float RIGHT_FORWARD = 2.356;
static const float FORWARD = 1.571;
static const float LEFT_FORWARD = 0.785;
static const float RIGHT = 3.142;
static const float LEFT = 0;
static const float RIGHT_BACKWARD = 3.927;
static const float BACKWARD = 4.712;
static const float LEFT_BACKWARD = 5.498;

//Defaults
static const float START_POS_LOW = 2;
static const float START_POS_HIGH = 4;
static const float START_ANGLE = 90;

static const uint16_t START_HIP_ANGLE = 90;
static const uint16_t START_FEMUR_ANGLE = 180;
static const uint16_t START_TIBIA_ANGLE = 180;

static const float START_FOOT_DIST = 12;

//cos(LEG_ANGLE) * START_FOOT_DIST, 0, sin(LEG_ANGLE) * START_FOOT_DIST;
static const Vec3 START_FOOT_POS_FRONTRIGHT = Vec3(cos(LEG_ANGLE_FRONTRIGHT) * START_FOOT_DIST, 0, sin(LEG_ANGLE_FRONTRIGHT) * START_FOOT_DIST);
static const Vec3 START_FOOT_POS_MIDRIGHT = Vec3(cos(LEG_ANGLE_MIDRIGHT) * START_FOOT_DIST, 0, sin(LEG_ANGLE_MIDRIGHT) * START_FOOT_DIST);
static const Vec3 START_FOOT_POS_BACKRIGHT = Vec3(cos(LEG_ANGLE_BACKRIGHT) * START_FOOT_DIST, 0, sin(LEG_ANGLE_BACKRIGHT) * START_FOOT_DIST);
static const Vec3 START_FOOT_POS_FRONTLEFT = Vec3(cos(LEG_ANGLE_FRONTLEFT) * START_FOOT_DIST, 0, sin(LEG_ANGLE_FRONTLEFT) * START_FOOT_DIST);
static const Vec3 START_FOOT_POS_MIDLEFT = Vec3(cos(LEG_ANGLE_MIDLEFT) * START_FOOT_DIST, 0, sin(LEG_ANGLE_MIDLEFT) * START_FOOT_DIST);
static const Vec3 START_FOOT_POS_BACKLEFT = Vec3(cos(LEG_ANGLE_BACKLEFT) * START_FOOT_DIST, 0, sin(LEG_ANGLE_BACKLEFT) * START_FOOT_DIST);

static const uint16_t HIP_MIN_ANGLE = 60;
static const uint16_t HIP_MAX_ANGLE = 120;

static const uint16_t BASE_STEP_DUR = 1000;
static const float STEP_HEIGHT = 2;
static const float STEP_DIST = 3;
static const float STEP_DIST_X2 = STEP_DIST * 2;

#endif