#include "haos_move_smart_car.h"

#define move_time 1000

void setup()
{
	init_movement();	
}

boolean have_not_moved_yet = true;

void move_car(int left_speed, int right_speed)
{
	move_car_analogue(left_speed, right_speed);
	delay(move_time);
}

void loop()
{
	if (have_not_moved_yet) {
		move_car(100, 100);
		move_car(-100, -100);
		move_car(100, -100);
		move_car(-100, 100);
		move_car(0, 0);
		have_not_moved_yet = false;
	}
}