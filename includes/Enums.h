#pragma once

//This follows the CW order
enum LEG
{
    FRONTRIGHT,
    MIDRIGHT,
    BACKRIGHT,
    BACKLEFT,
    MIDLEFT,
    FRONTLEFT
};

enum TWEENTYPE
{
    LINEAR,
    SQUARE,
    CUBIC,
    SINE,
    COSINE
};

enum GAITTYPE
{
    TRIPOD,
    TRIPLE, //Tripod + Ripple
    WAVE,
    RIPPLE, //FR, MR, BR, BL, ML, FL
};

enum MOVESTATE
{
    MOVING,
    STOPSTARTED,
    STOPPING,
    STOPPED,
};

enum MOVETYPE
{
    WALK,
    ROTATE
};

enum ROTATEDIR
{
    CLOCKWISE = 1,
    COUNTERCLOCKWISE = -1
};

enum BTDATA_MISC
{
    NO_DATA,
    TRIPOD_GAIT,
    TRIPLE_GAIT,
    WAVE_GAIT,
    RIPPLE_GAIT,
    RISE,
    CROUCH,
    AUTOROT_ON,
    AUTOROT_OFF
};

enum BTDATA_INDICES {
    TRANS_IDX,
    MOVE_IDX,
    TURN_IDX,
    ROT_IDX,
    MISC_IDX
};