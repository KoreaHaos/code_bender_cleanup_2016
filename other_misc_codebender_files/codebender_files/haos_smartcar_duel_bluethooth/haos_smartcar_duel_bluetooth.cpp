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

void display_hello_message_to_usb_serial_out() {
      Serial.println("Sketch HC-0x_FC-114_01_9600");
      Serial.println("Arduino with HC-0x FC-114 is ready");
      Serial.println("Make sure Both NL & CR are set");
      Serial.println("");
}

void display_hello_message_to_bluetooth_serial_out() {
      Serial.println("BlueTooth serial started at 9600");
      Serial.println("");
      Serial.println("Sending BlueTooth Serial Message...");
      BTSerial.println("Hi from arduino!");
}

void check_for_nfc_tag_and_serial_print_output_if_found() {
	uchar i, tmp, checksum1;
	uchar status;
	uchar str[MAX_LEN];
	uchar RC_size;
	uchar blockAddr;	//Selection operation block address 0 to 63
	String mynum = "";

        str[1] = 0x4400;
	
	//Find tags, return tag type
	status = myRFID.AddicoreRFID_Request(PICC_REQIDL, str);
	// Serial.println("looping..."); // <-- This shows that the loop does 
	//                                      not stop or halt here.
	
	if (status == MI_OK)
	{
            /*
            
            Serial.println("RFID tag detected");
    	    Serial.print(str[0],BIN);
            Serial.print(" , ");
    	    Serial.print(str[1],BIN);
            Serial.println(" ");
            */
            //send_bluetooth_message("tag detected!");
	} else {
		//Serial.println("xXx " + status);
		Serial.println("zXz ");
		have_valid_tag = false;
	}

	//Anti-collision, return tag serial number 4 bytes
	status = myRFID.AddicoreRFID_Anticoll(str);
	if (status == MI_OK)
	{
            checksum1 = str[0] ^ str[1] ^ str[2] ^ str[3];
            /*
            Serial.println("The tag's number is  : ");
    	    Serial.print(str[0]);
            Serial.print(" , ");
    	    Serial.print(str[1],BIN);
            Serial.print(" , ");
    	    Serial.print(str[2],BIN);
            Serial.print(" , ");
    	    Serial.print(str[3],BIN);
            Serial.print(" , ");
    	    Serial.print(str[4],BIN);
            Serial.print(" , ");
            Serial.println(checksum1,BIN);
            */
            
            // ToDo :  Have it check all pairs, right it just uses the first
            
            String message_end = "Tag Detected.\n";
            String append_message = "Unknown ";
            if(str[0] == 32)                      
            {
                append_message = "Tag #1 ";
                have_valid_tag = true;
            } else if(str[0] == 112)
            {             
                append_message = "Tag #2 ";
                have_valid_tag = true;
            } else if(str[0] == 144)
            {
            	append_message = "Tag #3 ";
            	have_valid_tag = true;
            } else
            {
            	have_valid_tag = false;
            }
            
            String message_to_send = "" + append_message + message_end;
            Serial.print(message_to_send);
            send_bluetooth_message(message_to_send);
            //Serial.println();
            delay(3000);
	}
    myRFID.AddicoreRFID_Halt();		   //Command tag into hibernation ToDo : Figure this bit out.              
}

void send_bluetooth_message(String message_to_send) {
	BTSerial.println(message_to_send);
}

void setup() {                
  startup_usb_serial();
  startup_nfc_reader();
  startup_bluetooth_serial();
  inputString.reserve(200);
  Serial.println("setup function completed.");
  display_hello_message_to_bluetooth_serial_out();
  
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);
  shutdown_green_led();
  shutdown_red_led();
}


void loop()
{
	check_for_nfc_tag_and_serial_print_output_if_found();
	manage_led(have_valid_tag);
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
