#ifndef ENUMS_H
#define ENUMS_H

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

enum GAITTYPE {
    TRIPOD,
    RIPPLE,
    TRIPLE,
    WAVE,
    Count
};

enum MOVESTATE {
    MOVE,
    IDLE
};

enum MOVETYPE {
    WALK,
    ROTATE
};

enum ROTATEDIR {
    CLOCKWISE = 1,
    COUNTERCW = -1
};

enum GAITGROUPSTATE {
    MOVING,
    STOPPING,
    STOPPED,
};

#endif