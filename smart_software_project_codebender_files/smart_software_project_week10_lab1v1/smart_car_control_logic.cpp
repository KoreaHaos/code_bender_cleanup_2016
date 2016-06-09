#include "Arduino.h"
#include  "lab10.h"







unsigned char text[] = "\n Welcome! Arduino Mega\n Ultrasonic Sensors Test Program.\n";

void setup_smart_car_control_logic()
{
	Serial.begin(115200);
	
	int i = 0;
	
	while (text[i] != '\0')
	{
		Serial.write(text[i++]);
	}
	
	Serial.write("Received cmds: ");
}

void serialEvent()
{
    int command = Serial.read();
    
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
        case 10:
	       //buzz_signal_recieved();
	       ultrasonic_sensor_read();
	       break;
        case 11:
	       //buzz_signal_recieved();
	       infrared_sensor_read();
	       break;
        case 12:
	       turn_buzzer_on();
	       break;
        case 13:
	       turn_buzzer_off();
	       break;
	    
		case 14:
			line_tracing_disable();
			break;
		case 15:
			line_tracing_enable();
			break;
		case 16:
			buzz_ready();
			break;
		
        default:
			move_stop();
			front_led_control(false);
			rear_led_control(false);
			break;
    }
    
    
    /*
    
    ToDo : Output Command recieved.
    
    */
    
}
