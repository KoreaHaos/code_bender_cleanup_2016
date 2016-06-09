/*

ToDo: Mod this to be more OO.
ToDo: Create getters and setters for motor speed.
ToDo: Create getter for ms since last motion?

ToDo: Figure out if the variables can be declared in the header file and then
		set either in the setup function or by getter/setters.

*/

#include "Arduino.h"

#define LEFT_MD_A 22
#define LEFT_MD_B 23
#define RIGHT_MD_A 24
#define RIGHT_MD_B 25
#define LEFT_MOTOR_EN 4
#define RIGHT_MOTOR_EN 5


// This function needs to be called during setup of IC.
void setup_ports_for_movement()
{
    pinMode(LEFT_MD_A, OUTPUT);
    pinMode(LEFT_MD_B, OUTPUT);
    
    pinMode(RIGHT_MD_A, OUTPUT);
    pinMode(RIGHT_MD_B, OUTPUT);
    
    pinMode(LEFT_MOTOR_EN, OUTPUT);
    pinMode(RIGHT_MOTOR_EN, OUTPUT);
    
    
    // Set everything to be off.
    digitalWrite(LEFT_MD_A, LOW);
    digitalWrite(LEFT_MD_B, LOW);
    
    digitalWrite(RIGHT_MD_A, LOW);
    digitalWrite(RIGHT_MD_B, LOW);
    
    digitalWrite(LEFT_MOTOR_EN, LOW);
    digitalWrite(RIGHT_MOTOR_EN, LOW);
}

void move_forward()
{
    // Setup pin output to rotate counterclockwise for left motor.
    digitalWrite(LEFT_MD_A, HIGH);
    digitalWrite(LEFT_MD_B, LOW);
    
    // Setup pin output to rotate clockwise for right motor
    digitalWrite(RIGHT_MD_A, LOW);
    digitalWrite(RIGHT_MD_B, HIGH);
    
    // Turn both motors on.
    analogWrite(LEFT_MOTOR_EN, 100);
    analogWrite(RIGHT_MOTOR_EN, 100);
}

void move_backward()
{
    // Setup pin output to rotate clockwise for left motor
    digitalWrite(LEFT_MD_A, LOW);
    digitalWrite(LEFT_MD_B, HIGH);
    
    // Setup pin output to rotate counterclockwise for right motor
    digitalWrite(RIGHT_MD_A, HIGH);
    digitalWrite(RIGHT_MD_B, LOW);
    
    // Turn both motors on.
    analogWrite(LEFT_MOTOR_EN, 100);
    analogWrite(RIGHT_MOTOR_EN, 100);
}

void turn_left() { //Rotate clockwise for right motor
    
    //Setup pin output to rotate right motor clockwise.
    digitalWrite(RIGHT_MD_A, LOW);
    digitalWrite(RIGHT_MD_B, HIGH);
    
    // Turn on right motor and turn off left motor.
    analogWrite(LEFT_MOTOR_EN,0);
    analogWrite(RIGHT_MOTOR_EN, 150);
}

void turn_right() { 
	
	//Setup pin output to rotate left motor counterclockwise.
    digitalWrite(LEFT_MD_A, HIGH);
    digitalWrite(LEFT_MD_B, LOW);
    
    // Turn on left motor and turn off right motor.
    analogWrite(LEFT_MOTOR_EN, 150);
    analogWrite(RIGHT_MOTOR_EN,0);
}

void move_stop() {
    
    // Turn off both motors.
 
    analogWrite(LEFT_MOTOR_EN, 0);
    analogWrite(RIGHT_MOTOR_EN, 0);
}


void make_left_wheels_forward(){
	    // Setup pin output to rotate counterclockwise for left motor.
	    // Forward on left wheels.
	    digitalWrite(LEFT_MD_A, HIGH);
	    digitalWrite(LEFT_MD_B, LOW);
}
void make_right_wheels_forward(){
	    // Setup pin output to rotate counterclockwise for left motor.
	    // Forward on left wheels.
	    digitalWrite(LEFT_MD_A, LOW);
	    digitalWrite(LEFT_MD_B, HIGH);
}
void make_left_wheels_backward(){
	    // Setup pin output to rotate counterclockwise for left motor.
	    // Forward on left wheels.
	    digitalWrite(LEFT_MD_A, LOW);
	    digitalWrite(LEFT_MD_B, HIGH);
}
void make_right_wheels_backward(){
	    // Setup pin output to rotate counterclockwise for left motor.
	    // Forward on left wheels.
	    digitalWrite(LEFT_MD_A, HIGH);
	    digitalWrite(LEFT_MD_B, LOW);
}

boolean left_wheels_are_moving_forward = true;
boolean right_wheels_are_moving_forward = true;

void move_car_for_line_tracing(int left, int right)
{
    
    
    /*
    */
    
    if ((left < 0 && left_wheels_are_moving_forward) || (right < 0 && right_wheels_are_moving_forward)){
    	move_stop();
    	delay(500);
    	
    	if (left < 0)
    	{
    		left_wheels_are_moving_forward = false;	
    	}
    	if (right < 0)
    	{
    		right_wheels_are_moving_forward = false;	
    	}
    }
    
    if ((left >= 0 && ! left_wheels_are_moving_forward) || (right >= 0 && ! right_wheels_are_moving_forward)){
    	move_stop();
    	delay(500);
    	
    	if (left < 0)
    	{
    		left_wheels_are_moving_forward = true;	
    	}
    	if (right < 0)
    	{
    		right_wheels_are_moving_forward = true;	
    	}
    }
    
    if (left >= 0 && right >= 0) {
	    make_left_wheels_forward();
	    make_right_wheels_forward();
	    // For Forward on both wheels.
	    // Setup pin output to rotate counterclockwise for left motor.
	    // Forward on left wheels.
	    //digitalWrite(LEFT_MD_A, HIGH);
	    //digitalWrite(LEFT_MD_B, LOW);
	    
	    // Setup pin output to rotate clockwise for right motor
	    // Forward on right wheels.
	    //digitalWrite(RIGHT_MD_A, LOW);
	    //digitalWrite(RIGHT_MD_B, HIGH);
    } else if (left < 0 && right >= 0) {
	    make_left_wheels_backward();
	    make_right_wheels_forward();

	    // Setup pin output to rotate clockwise for left motor.
	    // Reverse on left wheels.
	    //digitalWrite(LEFT_MD_A, LOW);
	    //digitalWrite(LEFT_MD_B, HIGH);
	    
	    // Setup pin output to rotate clockwise for right motor
	    // Forward on right wheels.
	    //digitalWrite(RIGHT_MD_A, LOW);
	   // digitalWrite(RIGHT_MD_B, HIGH);

	    left = abs(left);
	    
   	
    } else if (left >= 0 && right < 0) {
	    make_left_wheels_forward();
	    make_right_wheels_backward();

	    // For pivots to the right
	    // Setup pin output to rotate counterclockwise for left motor.
	    // Forward on left wheels.
	    //digitalWrite(LEFT_MD_A, HIGH);
	   // digitalWrite(LEFT_MD_B, LOW);
	    
	    // Setup pin output to rotate counterclockwise for right motor
	    // Reverse on right wheels.
	    //digitalWrite(RIGHT_MD_A, HIGH);
	    //digitalWrite(RIGHT_MD_B, LOW);
	    
	    right = abs(right);
    	
    } else {
	    make_left_wheels_backward();
	    make_right_wheels_backward();
	    // for reverse
	    // Setup pin output to rotate clockwise for left motor.
	    // Reverse on left wheels.
	    //digitalWrite(LEFT_MD_A, LOW);
	    //digitalWrite(LEFT_MD_B, HIGH);
	    
	    // Setup pin output to rotate counterclockwise for right motor
	    // Reverse on right wheels.
	    //digitalWrite(RIGHT_MD_A, HIGH);
	    //digitalWrite(RIGHT_MD_B, LOW);
    	
    	right = abs(right);
    	left = abs(left);
    }
    
    
    // Turn both motors on.
    analogWrite(LEFT_MOTOR_EN, left);
    analogWrite(RIGHT_MOTOR_EN, right);

}

/*
void move_forward_speed(int left, int right)
{
	move_car_for_line_tracing(left, right);
}


void turn_car(int left, int right)
{
	move_car_for_line_tracing(left, right);
}

void turn_left_speed(int left, int right)
{
	move_car_for_line_tracing(left, right);
}

void turn_right_speed(int left, int right)
{
	move_car_for_line_tracing(left, right);
}


void pivot_car(int left, int right)
{
	move_car_for_line_tracing(left, right);
}

*/
/*

void turn_pivot_left_speed(int left, int right)
{
	move_car_for_line_tracing(left, right);
}

void turn_pivot_right_speed(int left, int right)
{
	move_car_for_line_tracing(left, right);
}

*/

