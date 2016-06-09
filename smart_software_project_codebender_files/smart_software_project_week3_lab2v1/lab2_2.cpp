#include "lab2_2.h"

#define FRONT_LED_PIN  10
#define REAR_LED_PIN  9

//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
	pinMode(FRONT_LED_PIN, OUTPUT);
	  pinMode(REAR_LED_PIN, OUTPUT);
}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here

	  int led_val = 0;
	  int led_total_time = 3 * 1000;  // 3 seconds.
	  int led_varience = 255; // max output for led.

	  analogWrite(FRONT_LED_PIN,led_val);
	  analogWrite(REAR_LED_PIN,led_varience - led_val);

	  for (int i = 0; i < led_varience; i++) {
	    led_val = i;
	    analogWrite(FRONT_LED_PIN,led_val);
	    analogWrite(REAR_LED_PIN,led_varience - led_val);
	    delay(led_total_time/led_varience);
	  }

	  for (int i = led_varience; i > 0; i--) {
	    led_val = i;
	    analogWrite(FRONT_LED_PIN,led_val);
	    analogWrite(REAR_LED_PIN,led_varience - led_val);
	    delay(led_total_time/led_varience);
	  }
}
