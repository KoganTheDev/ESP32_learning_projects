#include <Arduino.h>

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    Serial.printf("TOUCH VALUE: %d\n", touchRead(T0)); // T0 = GPIO4
}