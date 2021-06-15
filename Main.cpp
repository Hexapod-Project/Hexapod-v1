#include "src/Hexapod.h"
#include "includes/HexapodConstants.h"
#include <HardwareSerial.h>

Hexapod hexapod;

extern HardwareSerial Serial;

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