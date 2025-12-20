#include <Arduino.h>
#include <esp32-hal-ledc.h>

#define PIN_ANALOG_IN   4
#define PIN_LED         12
#define CHAN            0
#define LIGHT_MIN       372
#define LIGHT_MAX       2048

void setup() {
    // Initialize channel 0, 1000Hz, 12-bit resolution
    ledcSetup(CHAN, 1000, 12);
    // Attach GPIO 12 to Channel 0
    ledcAttachPin(PIN_LED, CHAN); 
}

void loop() {
  int adcVal = analogRead(PIN_ANALOG_IN); 
  
  // Constrain and Map
  // Reversed 4095 and 0 so that MIN light = MAX brightness
  int pwmVal = map(constrain(adcVal, LIGHT_MIN, LIGHT_MAX), LIGHT_MIN, LIGHT_MAX, 4095, 0);  

  // Write to the CHANNEL
  ledcWrite(CHAN, pwmVal);    
  delay(10);
}