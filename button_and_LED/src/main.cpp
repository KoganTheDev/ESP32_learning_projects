#include <Arduino.h>

#define PIN_LED 2 // ESP32 builtin led
#define PIN_BUTTON 13 // GPIO 13 will be used for the button component 

void setup() {
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_BUTTON, INPUT);
}

void loop() {
    if (digitalRead(PIN_BUTTON) == LOW) // Button pressed
    {
    digitalWrite(PIN_LED, HIGH); // Turn on LED
    }
    else // Button presses
    {
    digitalWrite(PIN_LED, LOW);
    }
}
