#include  "lab5.h"

#define LEFT_MD_A 22
#define LEFT_MD_B 23
#define RIGHT_MD_A 24
#define RIGHT_MD_B 25
#define LEFT_MOTOR_EN 4
#define RIGHT_MOTOR_EN 5
#define  FRONT_LED_PIN 10
#define REAR_LED_PIN  9

int init_done = false;

unsigned char text[] = "\n Welcome! Arduino Mega\n UART Test Program.\n";

//The setup function is called once at startup of the sketch
void setup()
{
    
    int i = 0;
    Serial.begin(115200);
    
    while (text[i] != '\0')
    Serial.write(text[i++]);
    
    Serial.write("Received  cmds: ");
    
    // Add your initialization code here
    pinMode(LEFT_MD_A, OUTPUT);
    pinMode(LEFT_MD_B, OUTPUT);
    pinMode(RIGHT_MD_A, OUTPUT);
    pinMode(RIGHT_MD_B, OUTPUT);
    pinMode(LEFT_MOTOR_EN, OUTPUT);
    pinMode(RIGHT_MOTOR_EN, OUTPUT);
    
    pinMode(FRONT_LED_PIN,  OUTPUT);
    pinMode(REAR_LED_PIN, OUTPUT);
    
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


void loop()
{
    if (Serial.available() > 0)
    {
        int command = Serial.read();
        Serial.print(command, DEC);
        Serial.print(" ");
        switch (command)
        {
            case 1:
            move_stop();
            delay(500);
            move_forward();
            break;
            case 2:
            move_stop();
            delay(500);
            turn_left();
            break;
            case 3:
            move_stop();
            delay(500);
            turn_right();
            break;
            case 4:
            move_stop();
            delay(500);
            move_backward();
            break;
            case 5:
            move_stop();
            break;
            case 6:
            front_led_control(true);
            break;
            case 7:
            front_led_control(false);
            break;
            case 8:
            rear_led_control(true);
            break;
            case 9:
            rear_led_control(false);
            break;
            default:
            move_stop();
            front_led_control(false);
            rear_led_control(false);
        }
    }
}