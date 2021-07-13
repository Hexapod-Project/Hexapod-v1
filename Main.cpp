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