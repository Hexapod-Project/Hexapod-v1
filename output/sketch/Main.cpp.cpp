#include <Arduino.h>
#line 1 "/home/edwinlee/Documents/Projects/HexapodRobot/Main.cpp"
#include "src/Hexapod.h"
#include "includes/HexapodConstants.h"
#include <HardwareSerial.h>

Hexapod hexapod;

extern HardwareSerial Serial;

#line 9 "/home/edwinlee/Documents/Projects/HexapodRobot/Main.cpp"
void setup();
#line 18 "/home/edwinlee/Documents/Projects/HexapodRobot/Main.cpp"
void loop();
#line 9 "/home/edwinlee/Documents/Projects/HexapodRobot/Main.cpp"
void setup()
{    
    Serial.begin(9600);

    Serial.println("Setting up...");
    hexapod.setup();  
    hexapod.move(FORWARD);
}

void loop()
{
    hexapod.update();
}
