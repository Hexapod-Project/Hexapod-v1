# 1 "/home/edwinlee/Documents/Projects/HexapodRobot/Main.cpp"
# 2 "/home/edwinlee/Documents/Projects/HexapodRobot/Main.cpp" 2
# 3 "/home/edwinlee/Documents/Projects/HexapodRobot/Main.cpp" 2
# 4 "/home/edwinlee/Documents/Projects/HexapodRobot/Main.cpp" 2

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
