/* 
This basic example turns the built in LED on for one second,
then off for one second, repeatedly.
*/

// Pin 13 has a LED connected so we give it a name:
int led = 13;

// the setup routine runs once when you press reset:
void setup()
{
	// initialize the digital pin as an output.
	pinMode(led, OUTPUT);
	// initialize serial communication at 9600 bits per second:
	Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop()
{
	for(int i=0; i < 10; i++){
		//Set the LED pin to HIGH. This gives power to the LED and turns it on
		digitalWrite(led, HIGH);
		//Wait for a second
		delay(1000);
		Serial.print(i, DEC);
		Serial.println(" loop");
	}
	//Set the LED pin to LOW. This turns it off
	Serial.println("off state start");
	digitalWrite(led, LOW);
	//Wait for a second
	delay(500);
	Serial.println("off state done");
}