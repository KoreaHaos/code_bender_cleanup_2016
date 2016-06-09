#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3); // RX | TX

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

char c = ' ';
boolean NL = true;

void startup_bluetooth_serial() {
	BTSerial.begin(9600);
	//Serial1.begin(115200);
}

void send_bluetooth_message(String message_to_send) {
	BTSerial.println(message_to_send);
}

void display_hello_message_to_bluetooth_serial_out() {
      Serial.println("BlueTooth serial started at 9600");
      Serial.println("");
      Serial.println("Sending BlueTooth Serial Message...");
      BTSerial.println("Hi from arduino!");
}

void setup() {                
  startup_bluetooth_serial();
  inputString.reserve(200);
  Serial.println("setup function completed.");
  display_hello_message_to_bluetooth_serial_out();
}


void loop()
{
//	manage_led(have_valid_tag);
	// Read from the Bluetooth module and send to the Arduino Serial Monitor
	
	if (BTSerial.available())
	{
		c = BTSerial.read();
		Serial.write(c);
	}
	
	// ToDo : Determine if this is cut out able...
    // Read from the Serial Monitor and send to the Bluetooth module
    
    if (Serial.available())
    {
        c = Serial.read();
        BTSerial.write(c);   
        
        // Echo the user input to the main window. The ">" character indicates the user entered text.
        if (NL) { Serial.print(">");  NL = false; }
        Serial.write(c);
        if (c==10) { NL = true; }
    }
	
}

void serialEvent() {
	while (Serial.available()) {
		// get the new byte:
		char inChar = (char)Serial.read();
		
		// add it to the inputString:
		inputString += inChar;
		// if the incoming character is a newline, set a flag
		// so the main loop can do something about it:
		if (inChar == '\n') {
			stringComplete = true;
		} else if (inChar == '13') {
			stringComplete = true;
		}
	}
}
