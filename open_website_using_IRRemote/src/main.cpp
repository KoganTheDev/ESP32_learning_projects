#include <Arduino.h>
#include <IRremote.hpp>

#define IR_RECEIVE_PIN 15 // Connect your IR sensor Data pin here

void setup() {
    Serial.begin(115200);
    // Start the receiver with feedback LED (usually the built-in LED on pin 2)
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
    Serial.println("--- ESP32 IR System Started ---");
}

void loop() {

    byte POWER_BUTTON = 0xBA45FF00;

    if (IrReceiver.decode()) {
        uint32_t rawCode = IrReceiver.decodedIRData.decodedRawData;
        
        
        if (rawCode == POWER_BUTTON) {
            Serial.println("COMMAND:OPEN_WEBSITE");
        }

        IrReceiver.resume(); 
    }
}