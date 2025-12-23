/**********************************************************************
  Filename    : Infrared Motion Sensor
  Description : LED lamp is controlled by Infrared Motion Sensor
  Author      : www.freenove.com
  Modification: 2024/06/19
**********************************************************************/

#include <Arduino.h>

int sensorPin = 14; // the number of the infrared motion sensor pin
int ledPin = 13;    // the number of the LED pin

void setup() {
  pinMode(sensorPin, INPUT); // initialize the sensor pin as input
  pinMode(ledPin, OUTPUT);   // initialize the LED pin as output
}

void loop() {
  // Turn on or off LED according to Infrared Motion Sensor
  digitalWrite(ledPin, digitalRead(sensorPin));
  delay(1000); // wait for a second
}