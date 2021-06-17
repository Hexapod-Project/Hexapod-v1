# 1 "/home/edwinlee/Documents/Projects/HexapodRobot/Main.cpp"
# 2 "/home/edwinlee/Documents/Projects/HexapodRobot/Main.cpp" 2
# 3 "/home/edwinlee/Documents/Projects/HexapodRobot/Main.cpp" 2
# 4 "/home/edwinlee/Documents/Projects/HexapodRobot/Main.cpp" 2

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
