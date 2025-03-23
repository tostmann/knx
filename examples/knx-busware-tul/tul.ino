/*

Support for WiFi/TPUART USB-Stick "TUL" from busware.de - https://busware.de/tul

*/

#include <knx.h>
#include <WiFi.h>

// WiFi
const char* ssid = "your SSID";
const char* password = "your Password";

void setup()
{
    Serial.begin(115200);
    ArduinoPlatform::SerialDebug = &Serial;

    pinMode(KNX_LED, OUTPUT);

    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\r\nWiFi connected");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    randomSeed(millis());

    // read adress table, association table, groupobject table and parameters from eeprom
    knx.readMemory();

    // print values of parameters if device is already configured
    if (knx.configured())
    {
        Serial.println("Coupler configured.");
    }

    // pin or GPIO the programming led is connected to. Default is LED_BUILTIN
    knx.ledPin(KNX_LED);
    // is the led active on HIGH or low? Default is LOW
    // knx.ledPinActiveOn(HIGH);
    // pin or GPIO programming button is connected to. Default is 0
    knx.buttonPin(9);

    // start the framework.
    knx.start();
}

void loop()
{
    // don't delay here to much. Otherwise you might lose packages or mess up the timing with ETS
    knx.loop();

    // only run the application code if the device was configured with ETS
    if (!knx.configured())
        return;
}
