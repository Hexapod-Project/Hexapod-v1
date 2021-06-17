#include "src/Hexapod.h"
#include "includes/HexapodConstants.h"
#include <HardwareSerial.h>

Hexapod hexapod;

extern HardwareSerial Serial;
uint8_t input;

uint32_t startTime;
bool isWalking = false;

void setup()
{
    Serial.begin(115200);
    hexapod.setup();
}

void loop()
{
    if (Serial.available() > 0)
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
            break;
        }
    }

    hexapod.update();
}