#include <Arduino.h>
#include <esp32-hal-ledc.h>


const byte ledPins[] = {15, 2, 4};      // Red, Green, Blue pins
const byte adcChns[] = {13, 12, 14};    // Potentiometer pins
const int pwmFreq = 1000;               // 1 kHz frequency
const int pwmRes = 8;                   // 8-bit resolution (0-255)

// Define PWM channels (0, 1, and 2)
const byte pwmChns[] = {0, 1, 2}; 

int colors[] = {0, 0, 0};

void setup() {
  for (int i = 0; i < 3; i++) {
    // 1. Setup the PWM channel: ledcSetup(channel, frequency, resolution)
    ledcSetup(pwmChns[i], pwmFreq, pwmRes);
    
    // 2. Attach the GPIO pin to that channel: ledcAttachPin(pin, channel)
    ledcAttachPin(ledPins[i], pwmChns[i]);
    
    pinMode(adcChns[i], INPUT);
  }
}

void loop() {
  for (int i = 0; i < 3; i++) {
    // Read ADC (0-4095)
    int val = analogRead(adcChns[i]);
    
    // Convert 12-bit ADC to 8-bit PWM (0-255)
    colors[i] = map(val, 0, 4095, 0, 255);
    
    // 3. Write to the CHANNEL, not the pin: ledcWrite(channel, value)
    // Use (255 - colors[i]) if your LED is Common Anode
    ledcWrite(pwmChns[i], colors[i]); 
  }
  delay(10);
}