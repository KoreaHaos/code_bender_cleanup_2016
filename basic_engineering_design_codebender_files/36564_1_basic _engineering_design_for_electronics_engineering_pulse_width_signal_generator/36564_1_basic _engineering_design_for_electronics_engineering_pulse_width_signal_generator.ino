#define PULSED_PIN_A 13
#define PULSED_PIN_B 12

#define DUTY_CYCLE 25 // Duration in ms of duty cycle.

#define PAUSE_BETWEEN_VARIATIONS 10 // Time in ms to pause between each change in PWM.
#define PAUSE_AT_END_OF_PWM_SWEEP 5000 // Time in ms to pause once the PWM sweep is done.

void setup()
{
  pinMode(PULSED_PIN_A, OUTPUT);
  pinMode(PULSED_PIN_B, OUTPUT);
}

void pulse_pin_at_percent_for_x_seconds(int percent_on, int pin_to_pulse, int num_seconds_to_pulse_it_for)
{
	int on_time = DUTY_CYCLE * percent_on/100.0;
	int off_time = DUTY_CYCLE - on_time;
	
	int milliseconds_to_pulse_for = num_seconds_to_pulse_it_for * 1000;
	
	int num_duty_cycles_to_pulse = milliseconds_to_pulse_for / DUTY_CYCLE;
	
	for (int i = 0; i < num_duty_cycles_to_pulse; i++)
	{
		digitalWrite(pin_to_pulse, HIGH);
		digitalWrite(PULSED_PIN_B, LOW);
		delay(on_time);
		digitalWrite(pin_to_pulse, LOW);
		digitalWrite(PULSED_PIN_B, HIGH);
		delay(off_time);
	}
}

void loop()
{

	for (int i = 10; i >= 0; i--)
	{
		pulse_pin_at_percent_for_x_seconds(i * 10, PULSED_PIN_A, 1);
		delay(PAUSE_BETWEEN_VARIATIONS);
	}
	
	// Pause at end of PWM sweep.
	delay(5000);
}