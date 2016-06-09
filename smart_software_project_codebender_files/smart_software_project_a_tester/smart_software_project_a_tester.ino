/*

#### Who?

* Benjamin Haos

#### What?

* A basic hello world type thingy for making sure the toolchain works.
* Used with Hanback HBE-SMARTCAR
    * ***STATUS:*** [Works but building in progress...]

#### Where?

* Built on CodeBender

#### When?

* Seoul, South Korea, Spring 2016

#### Why?

* Need to know things are working before getting to work.

#### How?

* On CodeBender:
	* Choose correct com port and Mega 2560 or Mega ADK

*/


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

void setup()
{
	setup_led_pins();
	front_led_control(false);
	rear_led_control(false);
}

void loop()
{
	front_led_control(true);
	rear_led_control(false);
	delay(1000);
	
	front_led_control(false);
	rear_led_control(true);
	delay(1000);
}
