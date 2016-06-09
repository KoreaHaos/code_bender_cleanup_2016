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

int red_signal_led = 3;
int ylw_signal_led = 2;
int grn_signal_led = 8;

int hello_delay = 500;

int count_times_read = 0;
int max_count_before_reset = 100;

float manually_set_threshold_to_activate = 1.00;

void say_hello()
{
	digitalWrite(red_signal_led, LOW);
	delay(hello_delay);
	digitalWrite(red_signal_led, HIGH);
	digitalWrite(ylw_signal_led, LOW);
	delay(hello_delay);
	digitalWrite(ylw_signal_led, HIGH);
	digitalWrite(grn_signal_led, LOW);
	delay(hello_delay);
	digitalWrite(grn_signal_led, HIGH);
}
void setup_signal_led_set()
{
	pinMode(red_signal_led, OUTPUT);
	digitalWrite(red_signal_led, HIGH);
	pinMode(ylw_signal_led, OUTPUT);
	digitalWrite(ylw_signal_led, HIGH);
	pinMode(grn_signal_led, OUTPUT);
	digitalWrite(grn_signal_led, HIGH);
}
void turn_off_all_led()
{
	digitalWrite(red_signal_led, HIGH);
	digitalWrite(ylw_signal_led, HIGH);
	digitalWrite(grn_signal_led, HIGH);
}
void signal_red()
{
	turn_off_all_led();
	digitalWrite(red_signal_led, LOW);
}
void signal_yellow()
{
	turn_off_all_led();
	digitalWrite(ylw_signal_led, LOW);
}
void signal_green()
{
	turn_off_all_led();
	digitalWrite(grn_signal_led, LOW);
}

void cycle_lights()
{
	for (int i = 0; i < 10; i++)
	{
		signal_red();
		delay(100);
		signal_yellow();
		delay(100);
		signal_green();
		delay(100);
	}

}

void do_activity_done_when_device_senses_activity()
{
	cycle_lights();
}

void setup()
{
	setup_signal_led_set();
	say_hello();
	Serial.begin(9600);
}


void loop()
{
	// Read Piezo ADC value in, and convert it to a voltage

	int piezoADC = analogRead(PIEZO_PIN);
	float piezoV = piezoADC / 1023.0 * 5.0;
	
	if (piezoV > manually_set_threshold_to_activate)
	{
		signal_yellow();
		do_activity_done_when_device_senses_activity();
	}
	else
	{
		Serial.println(piezoV); // Print the voltage.
		signal_red();	
	}
}




