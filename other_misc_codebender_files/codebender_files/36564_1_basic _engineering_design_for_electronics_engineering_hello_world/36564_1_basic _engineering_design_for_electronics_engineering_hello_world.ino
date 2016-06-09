/*

A basic hello world.

Why? Well i use this to make sure everything is working...

How ? Personally, i like to adjust the on or off time to confirm i am loading the script.

Source : https://www.arduino.cc/en/tutorial/blink

*/

void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1200);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1200);              // wait for a second
}