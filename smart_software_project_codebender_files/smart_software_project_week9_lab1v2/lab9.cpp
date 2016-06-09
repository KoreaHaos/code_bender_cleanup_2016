#include  "lab9.h"

void setup()
{
	setup_led_pins();
	setup_ports_for_movement();
	setup_buzzer_pin();
	setup_sensors();
	
	setup_smart_car_control_logic();
	
	buzz_ready();
}

void loop()
{
}
