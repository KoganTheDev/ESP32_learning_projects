#include <Arduino.h>
#include "BluetoothSerial.h"

/**********************************************************************
  Filename    : SerialToSerialBT
  Description : Use ESP32 Bluetooth to communicate with Serial
  Auther      : www.freenove.com
**********************************************************************/

BluetoothSerial SerialBT;
String buffer;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); // Bluetooth device name
  Serial.println("\nThe device started, now you can pair it with bluetooth!");
}

void loop() {
  // If data is received from the hardware Serial (USB), send it to Bluetooth
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  
  // If data is received from Bluetooth, send it to the hardware Serial (USB)
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  
  delay(20);
}