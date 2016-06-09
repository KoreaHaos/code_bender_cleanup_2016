#include "Arduino.h"

#define LEFT_MD_A 22
#define LEFT_MD_B 23
#define RIGHT_MD_A 24
#define RIGHT_MD_B 25
#define LEFT_MOTOR_EN 4
#define RIGHT_MOTOR_EN 5

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
    //Rotate counterclockwise for left motor
    digitalWrite(LEFT_MD_A, HIGH);
    digitalWrite(LEFT_MD_B, LOW);
    //Rotate clockwise for right motor
    digitalWrite(RIGHT_MD_A, LOW);
    digitalWrite(RIGHT_MD_B, HIGH);
    //Now turn left and right motors ON!
    analogWrite(LEFT_MOTOR_EN, 100);
    analogWrite(RIGHT_MOTOR_EN, 100);
}

void move_backward()
{
    //Rotate clockwise for left motor
    digitalWrite(LEFT_MD_A, LOW);
    digitalWrite(LEFT_MD_B, HIGH);
    //Rotate counterclockwise for right motor
    digitalWrite(RIGHT_MD_A, HIGH);
    digitalWrite(RIGHT_MD_B, LOW);
    //Now turn left and right motors ON!
    analogWrite(LEFT_MOTOR_EN, 100);
    analogWrite(RIGHT_MOTOR_EN, 100);
}

void turn_left() { //Rotate clockwise for right motor
    digitalWrite(RIGHT_MD_A, LOW);
    digitalWrite(RIGHT_MD_B, HIGH);
    analogWrite(LEFT_MOTOR_EN,
    0);
    analogWrite(RIGHT_MOTOR_EN, 150);
}

void turn_right() { //Rotate counterclockwise for left motor
    digitalWrite(LEFT_MD_A, HIGH);
    digitalWrite(LEFT_MD_B, LOW);
    analogWrite(LEFT_MOTOR_EN, 150);
    analogWrite(RIGHT_MOTOR_EN,
    0);
}

void move_stop() {
    analogWrite(LEFT_MOTOR_EN, 0);
    analogWrite(RIGHT_MOTOR_EN, 0);
}
