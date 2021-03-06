#include "lab3.h"

#define LEFT_MD_A 22
#define LEFT_MD_B 23

#define RIGHT_MD_A 24
#define RIGHT_MD_B 25

#define LEFT_MOTOR_EN 4
#define RIGHT_MOTOR_EN 5

int init_done = false;

int motor_speed = 254;

int change_in_direction_pause_time = 500;

void move_smart_car(int left_ms, int right_ms) {
    
    while (left_ms != 0 || right_ms != 0)
    {
        // Handle Left Side Wheels.
            
        // Run left wheel motors forward/counter-clockwise if ms is positive, 
        // reverse if negative, 
        // nothing if zero.
        if (left_ms > 0)
        {
            digitalWrite(LEFT_MD_A, HIGH);
            digitalWrite(LEFT_MD_B, LOW);
            left_ms = left_ms - 1;
            analogWrite(LEFT_MOTOR_EN, motor_speed);
        }
        else if (left_ms < 0)
        {
            digitalWrite(LEFT_MD_A, LOW);
            digitalWrite(LEFT_MD_B, HIGH);
            left_ms = left_ms + 1;
            analogWrite(LEFT_MOTOR_EN, motor_speed);
        }
        else
        {
        	analogWrite(LEFT_MOTOR_EN, 0);
        }
        
   
        // Handle Right Side Wheels.
        
        // Run right wheel motors forward/clockwise if ms is positive, 
        // reverse if negative, 
        // nothing if zero.
     	if (right_ms > 0)
     	{
            digitalWrite(RIGHT_MD_A, LOW);
            digitalWrite(RIGHT_MD_B, HIGH);
            right_ms = right_ms - 1;
            analogWrite(RIGHT_MOTOR_EN, motor_speed);
        }
        else if (right_ms < 0)
        {
            digitalWrite(RIGHT_MD_A, HIGH);
            digitalWrite(RIGHT_MD_B, LOW);
            right_ms = right_ms + 1;
            analogWrite(RIGHT_MOTOR_EN, motor_speed);
        }
        else
        {
        	analogWrite(RIGHT_MOTOR_EN, 0);
        }

        // Run the motors for one ms.
	    delay(1);
    }
    
    move_stop();
    delay(change_in_direction_pause_time);
}

void move_stop() {
	analogWrite(LEFT_MOTOR_EN, 0);
	analogWrite(RIGHT_MOTOR_EN, 0);
}



//The setup function is called once at startup of the sketch
void setup()
{
    // Initialization code here
    pinMode(LEFT_MD_A, OUTPUT);
    pinMode(LEFT_MD_B, OUTPUT);
    
    pinMode(RIGHT_MD_A, OUTPUT);
    pinMode(RIGHT_MD_B, OUTPUT);
    
    pinMode(LEFT_MOTOR_EN, OUTPUT);
    pinMode(RIGHT_MOTOR_EN, OUTPUT);

    // Start with everything off.
    digitalWrite(LEFT_MD_A, LOW);
    digitalWrite(LEFT_MD_B, LOW);
    
    digitalWrite(RIGHT_MD_A, LOW);
    digitalWrite(RIGHT_MD_B, LOW);
    
    digitalWrite(LEFT_MOTOR_EN, LOW);
    digitalWrite(RIGHT_MOTOR_EN, LOW);
}

void loop()
{
    if (init_done == false)
    {
        // Move forward for 2 seconds.
        move_smart_car(2000, 2000);

        // Turn right for 1.5 seconds.
        move_smart_car(1500, -1500);

        // Turn left for 1.5 seconds.
        move_smart_car(-1500, 1500);

        // Move backward for 2 seconds.
        move_smart_car(-2000, -2000);

		// Flag that instruction set is done.
        init_done = true;
    }
    else
    {
    	// Do not move.
    	move_smart_car(0, 0);
    }
}
