#include <Arduino.h>
#line 1 "/home/edwinlee/Documents/Projects/HexapodRobot/Main.cpp"
#include "src/Hexapod.h"
#include "includes/HexapodConstants.h"
#include <HardwareSerial.h>

Hexapod hexapod;

extern HardwareSerial Serial;
uint8_t input;

uint32_t startTime;
bool isWalking = false;

#line 13 "/home/edwinlee/Documents/Projects/HexapodRobot/Main.cpp"
void setup();
#line 19 "/home/edwinlee/Documents/Projects/HexapodRobot/Main.cpp"
void loop();
#line 13 "/home/edwinlee/Documents/Projects/HexapodRobot/Main.cpp"
void setup()
{
    Serial.begin(115200);
    hexapod.setup();
}

void loop()
{
    if (Serial.available())
    {
        input = Serial.read();

        switch (input)
        {
        case 'w':
            hexapod.startWalk(FORWARD);
            break;
        case 'a':
            hexapod.startWalk(LEFT);
            break;
        case 'd':
            hexapod.startWalk(RIGHT);
            break;
        case 'x':
            hexapod.startWalk(BACKWARD);
            break;
        case 's':
            hexapod.stopWalk();
            break;
        default:
        }
    }

    hexapod.update();
}
