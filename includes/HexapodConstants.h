#ifndef HEXAPODCONSTANTS_H
#define HEXAPODCONSTANTS_H

#include "../includes/Enums.h"
#include "../src/Datatypes.h"

//All distance/length units are in Centimeter(cm)
namespace HexapodConstants
{
    const int LEG_COUNT = 6;

    //Hexapod Dimensions
    const float BODY_WIDTH = 7;
    const float BODY_LENGTH = 16.9;

    const float HIP_DIST_FRONTRIGHT = 9.7;
    const float HIP_DIST_MIDRIGHT = 5.9;
    const float HIP_DIST_BACKRIGHT = 9.3;
    const float HIP_DIST_FRONTLEFT = 9.3;
    const float HIP_DIST_MIDLEFT = 5.7;
    const float HIP_DIST_BACKLEFT = 9.3;

    const float HIP_LENGTH = 3.8;
    const float FEMUR_LENGTH = 4.2;
    const float TIBIA_LENGTH = 8.1;

    const float HIP_LENGTH_SQR = 14.44;
    const float FEMUR_LENGTH_SQR = 17.64;
    const float TIBIA_LENGTH_SQR = 65.61;

    const float LEG_LENGTH = 16.1;
    const float FEMUR_TIBIA_DIFF = 3.9;

    //Leg Angles
    const float LEG_ANGLE_FRONTRIGHT = M_PI / 3;
    const float LEG_ANGLE_MIDRIGHT = 0;
    const float LEG_ANGLE_BACKRIGHT = M_PI * 5 / 3;
    const float LEG_ANGLE_FRONTLEFT = M_PI * 2 / 3;
    const float LEG_ANGLE_MIDLEFT = M_PI;
    const float LEG_ANGLE_BACKLEFT = M_PI * 4 / 3;

    //Leg Offsets
    const Vec3 LEG_OFFSET_FRONTRIGHT = Vec3(4.6, 2.3, 8.2);
    const Vec3 LEG_OFFSET_MIDRIGHT = Vec3(5.2, 2.3, 0);
    const Vec3 LEG_OFFSET_BACKRIGHT = Vec3(4.6, 2.3, -8.2);
    const Vec3 LEG_OFFSET_FRONTLEFT = Vec3(-4.8, 2.3, 8);
    const Vec3 LEG_OFFSET_MIDLEFT = Vec3(-5.9, 2.3, 0);
    const Vec3 LEG_OFFSET_BACKLEFT = Vec3(4.85, 2.3, -8.15);

    //Directions
    const float RIGHT_FORWARD = 3 * M_PI / 4;
    const float FORWARD = M_PI / 2;
    const float LEFT_FORWARD = M_PI / 4;
    const float RIGHT = M_PI;
    const float LEFT = 0;
    const float RIGHT_BACKWARD = 5 * M_PI / 4;
    const float BACKWARD = 3 * M_PI / 2;
    const float LEFT_BACKWARD = 7 * M_PI / 4;

    //Defaults
    const float START_POS_LOW = 2;
    const float START_POS_HIGH = 4;
    const float START_ANGLE = 90;

    const float START_FOOT_DIST = 13;

    //cos(LEG_ANGLE) * START_FOOT_DIST, 0, sin(LEG_ANGLE) * START_FOOT_DIST;
    const Vec3 START_FOOT_POS_FRONTRIGHT = Vec3(6.5, 0, 11.25);
    const Vec3 START_FOOT_POS_MIDRIGHT = Vec3(13, 0, 0);
    const Vec3 START_FOOT_POS_BACKRIGHT = Vec3(6.5, 0, -11.25);
    const Vec3 START_FOOT_POS_FRONTLEFT = Vec3(-6.5, 0, 11.25);
    const Vec3 START_FOOT_POS_MIDLEFT= Vec3(-6.5, 0, 0);
    const Vec3 START_FOOT_POS_BACKLEFT = Vec3(-6.5, 0, -11.25);
}

#endif