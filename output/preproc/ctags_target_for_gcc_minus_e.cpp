# 1 "/home/edwinlee/Documents/Projects/HexapodRobot/Main.cpp"
# 2 "/home/edwinlee/Documents/Projects/HexapodRobot/Main.cpp" 2
# 3 "/home/edwinlee/Documents/Projects/HexapodRobot/Main.cpp" 2
# 4 "/home/edwinlee/Documents/Projects/HexapodRobot/Main.cpp" 2
# 5 "/home/edwinlee/Documents/Projects/HexapodRobot/Main.cpp" 2

# 7 "/home/edwinlee/Documents/Projects/HexapodRobot/Main.cpp" 2
# 8 "/home/edwinlee/Documents/Projects/HexapodRobot/Main.cpp" 2
# 9 "/home/edwinlee/Documents/Projects/HexapodRobot/Main.cpp" 2
# 10 "/home/edwinlee/Documents/Projects/HexapodRobot/Main.cpp" 2
# 11 "/home/edwinlee/Documents/Projects/HexapodRobot/Main.cpp" 2


extern HardwareSerial Serial;
Hexapod hexapod;

BluetoothSerial btSerial;

const uint8_t BYTESIZE = 5;
byte buffer[BYTESIZE];

void setup()
{
    Serial.begin(115200);
    initBluetooth();
    //printBluetoothAddr();

    hexapod.setup();
}

void loop()
{
    checkBtData();
    hexapod.update();
}


bool initBluetooth()
{
    if (!btStart())
    {
        Serial.println("Failed to start bluetooth.");
        return false;
    }

    if (esp_bluedroid_init() != 0 /*!< esp_err_t value indicating success (no error) */)
    {
        Serial.println("Failed to initialize bluedroid.");
        return false;
    }

    if (esp_bluedroid_enable() != 0 /*!< esp_err_t value indicating success (no error) */)
    {
        Serial.println("Failed to enable bluedroid.");
        return false;
    }

    btSerial.begin("Hexxo");
    return true;
}

void printBluetoothAddr()
{
    const uint8_t *addr = esp_bt_dev_get_address();

    for (int i = 0; i < 6; i++)
    {
        char str[3];

        sprintf(str, "%02X", addr[i]);
        Serial.print(str);

        if (i < 5)
            Serial.print(":");
    }
    Serial.println();
}

void checkBtData()
{
    if (btSerial.available())
    {
        btSerial.readBytes(buffer, BYTESIZE);

        float moveDir = jyStkAngleToRad(buffer[MOVE_IDX]);
        float turnDir = jyStkAngleToRad(buffer[TURN_IDX]);
        float transDir = jyStkAngleToRad(buffer[TRANS_IDX]);
        float rotDir = jyStkAngleToRad(buffer[ROT_IDX]);

        hexapod.updateDirs(moveDir, turnDir, transDir, rotDir);
        hexapod.setMisc(buffer[MISC_IDX]);
    }
}
