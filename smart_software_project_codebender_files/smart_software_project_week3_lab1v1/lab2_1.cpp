/* Author: Benjamin Haos  */
/* Date: Mar 14, 2016 */

#include "lab2_1.h"

#define FRONT_LED_PIN  10
#define REAR_LED_PIN  9

void setup()
{
  pinMode(FRONT_LED_PIN, OUTPUT);
  pinMode(REAR_LED_PIN, OUTPUT);
}

void loop()
{
  digitalWrite(FRONT_LED_PIN, HIGH);
  digitalWrite(REAR_LED_PIN, LOW);
  delay(1000);

  digitalWrite(FRONT_LED_PIN, LOW);
  digitalWrite(REAR_LED_PIN, HIGH);
  delay(1000);
}
