#include "src/Hexapod.h"
#include "src/Datatypes.h"
#include "src/Tools.h"
#include "includes/HexapodConstants.h"
#include "includes/Enums.h"
#include "HardwareSerial.h"
#include "BluetoothSerial.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp32-hal-bt.h"

extern HardwareSerial Serial;
Hexapod hexapod;

BluetoothSerial SerialBT;

const uint8_t BUFFER_LEN = 5;
byte buffer[BUFFER_LEN];

const uint8_t REQUEST_SYNC_FLAG = 255;
const String HEXAPOD_STATES_HEADER = "HS";

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

    if (esp_bluedroid_init() != ESP_OK)
    {
        Serial.println("Failed to initialize bluedroid.");
        return false;
    }

    if (esp_bluedroid_enable() != ESP_OK)
    {
        Serial.println("Failed to enable bluedroid.");
        return false;
    }

    SerialBT.begin("Hexxo");
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
    if (SerialBT.available())
    {
        SerialBT.readBytes(buffer, BUFFER_LEN);

        if (buffer[MISC_IDX] != REQUEST_SYNC_FLAG)
        {
            float moveDir = jyStkAngleToRad(buffer[MOVE_IDX]);
            float turnDir = jyStkAngleToRad(buffer[TURN_IDX]);
            float transDir = jyStkAngleToRad(buffer[TRANS_IDX]);
            float rotDir = jyStkAngleToRad(buffer[ROT_IDX]);

            hexapod.updateDirs(moveDir, turnDir, transDir, rotDir);
            hexapod.setMisc(buffer[MISC_IDX]);
        }
        else
            //Send hexapod states
            SerialBT.print(HEXAPOD_STATES_HEADER + "|" + (String)hexapod.getGaitTypeMisc() +
                           "|" + (String)hexapod.getStanceMisc() + "\n");
    }
}