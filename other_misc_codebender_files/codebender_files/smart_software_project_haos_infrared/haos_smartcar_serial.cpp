#include "Arduino.h"

boolean send_string_serial_message(int serial_comm_channel, String message_to_send)
{
	boolean message_accepted_and_queued = false;

	switch (serial_comm_channel)
	{
		case 0:
			while(!Serial){
				// beep?
			}
			 Serial.println(message_to_send);
			break;
		case 1:
			while(!Serial1){
				// beep?
			}
			//Serial1.write(message_to_send);
			break;
		case 2:
			while(!Serial2){
				// beep?
			}
			//Serial2.write(message_to_send);
			break;
		case 3:
			while(!Serial3){
				// beep?
			}
			//Serial3.write(message_to_send);
			break;
		default:
			break;
	}

	return message_accepted_and_queued;
}

boolean serial_has_message()
{
	boolean return_response = false;
	return return_response;
}

String inputString0 = "";         // a string to hold incoming data
boolean string0Complete = false;  // whether the string is complete
String inputString1 = "";         // a string to hold incoming data
boolean string1Complete = false;  // whether the string is complete
String inputString2 = "";         // a string to hold incoming data
boolean string2Complete = false;  // whether the string is complete
String inputString3 = "";         // a string to hold incoming data
boolean string3Complete = false;  // whether the string is complete


void init_serial_event_listener(int serial_comm_channel, int serial_comm_speed, int serial_string_reserve_size)
{

	switch (serial_comm_channel)
	{
		case 0:
			Serial.begin(serial_comm_speed);
			send_string_serial_message(0, "Hello Computer from comm. zero!");
			break;
		case 1:
			Serial1.begin(serial_comm_speed);
			send_string_serial_message(1, "Hello Computer from comm. one!");
			break;
		case 2:
			Serial2.begin(serial_comm_speed);
			send_string_serial_message(2, "Hello Computer from comm. two!");
			break;
		case 3:
			Serial3.begin(serial_comm_speed);
			send_string_serial_message(3, "Hello Computer from comm. three!");
			break;
		default:
			break;
	}
	
}

void serialEvent()
{
//statements
}
void serialEvent1()
{
//statements
}

void serialEvent2()
{
//statements
}

void serialEvent3()
{
//statements
}





