#include "Arduino.h"

#define  FRONT_LED_PIN 10
#define REAR_LED_PIN  9


void setup_led_pins()
{
    pinMode(FRONT_LED_PIN, OUTPUT);
    pinMode(REAR_LED_PIN, OUTPUT);
    
    digitalWrite(FRONT_LED_PIN, LOW);
    digitalWrite(REAR_LED_PIN, LOW);
}

void front_led_control(bool value) {
    if (value)
    {
        digitalWrite(FRONT_LED_PIN, HIGH);
    }
    else
    {
        digitalWrite(FRONT_LED_PIN, LOW);
    }
}

void rear_led_control(bool value) {
    if (value)
    {
        digitalWrite(REAR_LED_PIN,  HIGH);
    }
    else
    {
        digitalWrite(REAR_LED_PIN, LOW);
    }
}
