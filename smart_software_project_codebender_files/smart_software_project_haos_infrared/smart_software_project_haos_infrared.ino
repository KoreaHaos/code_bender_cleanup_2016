/* This a basic example of this libraries utility. */

#include "haos_smartcar_infrared.h"
#include "haos_smartcar_serial.h"

void setup()
{
	init_serial_event_listener(0, 9600, 200);
	Serial.begin(115200);
	init_serial_event_listener(1, 115200, 200);
	
	//nit_analogue_infrared_sensors();
	
}

void loop()
{
		
}
