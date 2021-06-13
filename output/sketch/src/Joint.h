#ifndef JOINT_H
#define JOINT_H

#include <Servo.h>
#include "Node.h"

class Joint : public Node
{
private:
    float mServoAngle;
    Servo mServo;

public:
    void attach(int pin);
    void write(float angle);
};

#endif