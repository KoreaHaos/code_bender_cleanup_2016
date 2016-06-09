/******************************************************************************
Piezo_Vibration_Sensor.ino
Example sketch for SparkFun's Piezo Vibration Sensor
  (https://www.sparkfun.com/products/9197)
Jim Lindblom @ SparkFun Electronics
April 29, 2016

- Connect a 1Mohm resistor across the Piezo sensor's pins.
- Connect one leg of the Piezo to GND
- Connect the other leg of the piezo to A0

Vibrations on the Piezo sensor create voltags, which are sensed by the Arduino's
A0 pin. Check the serial monitor to view the voltage generated.

Development environment specifics:
Arduino 1.6.7
******************************************************************************/
const int PIEZO_PIN = A0; // Piezo output

void setup() 
{
  Serial.begin(9600);
}
float highest = 0.0;
int count = 0;
int max_count = 100;
void loop() 
{
  // Read Piezo ADC value in, and convert it to a voltage
  int piezoADC = analogRead(PIEZO_PIN);
  float piezoV = piezoADC / 1023.0 * 5.0;
  if (highest < piezoV) {
  	highest = piezoV;
  	count = 0;
  } else {
  	count++;
  	if (count >= max_count) {
  	Serial.print("reset * * * * * "); // Print the voltage.
  		highest = 0.0;	
  	}
  }
  Serial.print(piezoV); // Print the voltage.
  Serial.print(", highest = "); // Print the voltage.
  Serial.println(highest); // Print the voltage.
}