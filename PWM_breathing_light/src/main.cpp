#include <Arduino.h>
#include <esp32-hal-ledc.h>

#define PIN_LED   2    //define the led pin
#define CHN       0     //define the pwm channel
#define FRQ       1000  //define the pwm frequency
#define PWM_BIT   8     //define the pwm precision

void setup() 
{
    // Initialize the PWM channel (CHN) with frequency (FRQ) and resolution (PWM_BIT)
    ledcSetup(CHN, FRQ, PWM_BIT); 
    
    // Attach the physical pin (PIN_LED) to the configured channel (CHN)
    ledcAttachPin(PIN_LED, CHN); 
}

void loop() 
{
    for (int i = 0; i < 256; i++) { // Loop from 0 to 255 (inclusive)
        // ledcWrite takes the CHANNEL NUMBER (CHN) as the first argument
        ledcWrite(CHN, i); 
        delay(10);
    }
    for (int i = 255; i >= 0; i--) {  // Loop from 255 down to 0 (inclusive)
        // ledcWrite takes the CHANNEL NUMBER (CHN) as the first argument
        ledcWrite(CHN, i); 
        delay(10);
    }
}