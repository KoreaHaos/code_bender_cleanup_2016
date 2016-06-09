#ifndef smart_car_movement
#define smart_car_movement

//#include "Arduino.h"

void setup_ports_for_movement();

void move_forward();
void move_backward();
void turn_left();
void turn_right();
void move_stop();

void move_forward_speed(int left, int right);
void turn_left_speed(int left, int right);
void turn_right_speed(int left, int right);

void turn_pivot_left_speed(int left, int right);
void turn_pivot_right_speed(int left, int right);

void move_car_for_line_tracing(int left, int right);

#endif