/*

who : Ben Haos
wat : 
where : Created on CodeBender for Metal Expression Project.
when : not done yet.
how : we'll see!

*/

// NFC Tutorial Source : https://www.addicore.com/v/vspfiles/downloadables/Product%20Downloadables/RFID_RC522/RFIDQuickStartGuide.pdf
// BlueTooth Tutorial SOURCE : http://www.martyncurrey.com/hc-05-fc-114-and-hc-06-fc-114-part-2-basic-at-commands/

#include <AddicoreRFID.h>
#include <SPI.h>
#include <SoftwareSerial.h>

#define	uchar	unsigned char
#define	uint	unsigned int

//bool have_valid_tag = false;

#define	card_a_id	57
#define	card_b_id	71
#define	card_c_id	197

//set pins for relay control

#define	card_a_pin	8
#define	card_b_pin	7
#define	card_c_pin	6

//set pins for NFC

const int NRSTPD = 5;
const int chipSelectPin = 10;

// create AddicoreRFID object to control the RFID module
AddicoreRFID myRFID;

//4 bytes tag serial number, the first 5 bytes for the checksum byte
uchar serNumA[5];

uchar fifobytes;
uchar fifoValue;

//Maximum length of the array
#define MAX_LEN 16

//set pins for BlueTooth
SoftwareSerial BTSerial(2, 3); // RX | TX

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

char c = ' ';

boolean NL = true;

void startup_usb_serial() {
	Serial.begin(9600);                        // RFID reader SOUT pin connected to Serial RX pin at 9600bps 
}

void startup_bluetooth_serial() {
	BTSerial.begin(9600);
	//Serial1.begin(115200);
}

void startup_nfc_reader() {
	// start the SPI library:
	SPI.begin();
	
	pinMode(chipSelectPin,OUTPUT);              // Set digital pin 10 as OUTPUT to connect it to the RFID /ENABLE pin 
	digitalWrite(chipSelectPin, LOW);         // Activate the RFID reader
	pinMode(NRSTPD,OUTPUT);                     // Set digital pin 10 , Not Reset and Power-down
	digitalWrite(NRSTPD, HIGH);
	
	myRFID.AddicoreRFID_Init();  
}

void display_hello_message_to_usb_serial_out() {
      Serial.println("Haos Metal Expression Electronic Control");
      Serial.println("");
}

void display_hello_message_to_bluetooth_serial_out() {
      Serial.println("BlueTooth serial started at 9600");
      Serial.println("");
      Serial.println("Sending BlueTooth Serial Message...");
      BTSerial.println("Hi from arduino!");
}

void assign_relay_pins() {
	pinMode(card_a_pin, OUTPUT);
	pinMode(card_b_pin, OUTPUT);
	pinMode(card_c_pin, OUTPUT);
}

void set_relay_pins_high() {
	digitalWrite(card_a_pin, HIGH);
	digitalWrite(card_b_pin, HIGH);
	digitalWrite(card_c_pin, HIGH);
}

void manage_relay(int relay_pin_to_send_ground_to) {
	set_relay_pins_high(); //Reset relay so all contacts are open.
	digitalWrite(relay_pin_to_send_ground_to, LOW);
}

int current_tags_id = 0;

void check_nfc_tag_for_change_and_react_if_change_found() {
	
	uchar i, tmp, checksum1;
	uchar status;
	uchar str[MAX_LEN];
	uchar RC_size;
	uchar blockAddr;	//Selection operation block address 0 to 63
	String mynum = "";
	
	str[1] = 0x4400;
	
	//Find tags, return tag type
	status = myRFID.AddicoreRFID_Request(PICC_REQIDL, str);

	if (status != MI_OK)
	{
		//Serial.println("no tag");
		//have_valid_tag = false;
		set_relay_pins_high();
		current_tags_id = 0;
		delay(1000);
	}

	//Anti-collision, return tag serial number 4 bytes
	status = myRFID.AddicoreRFID_Anticoll(str);
	
	/*
	*/
	
	
	if (status == MI_OK)
	{
            checksum1 = str[0] ^ str[1] ^ str[2] ^ str[3];

    	    if ( current_tags_id == str[0] ) {
    	    	//Serial.println("Same tag.");
    	    } else {
    	    	//Serial.println("Tag Detected!");
	            
	            String message_end = ".\n";
    	        String append_message = "an unknown ";
    	    	
	            Serial.print("Tag #");
	    	    Serial.print(str[0]);
	            Serial.print(" detected, this is ");
    	    	current_tags_id	= str[0];
	            if(str[0] == card_a_id)                      
	            {
	                append_message = "recognized as tag A";
	                manage_relay(card_a_pin);
	                //have_valid_tag = true;
	            } else if(str[0] == card_b_id)
	            {             
	                append_message = "recognized as tag B";
	                manage_relay(card_b_pin);
	               // have_valid_tag = true;
	            } else if(str[0] == card_c_id)
	            {
	            	append_message = "recognized as tag C";
	                manage_relay(card_c_pin);
	            //	have_valid_tag = true;
	            } else
	            {
	            //	have_valid_tag = false;
	            }
	            
	            String message_to_send = "" + append_message + message_end;
	            
	            Serial.print(message_to_send);
	            send_bluetooth_message(message_to_send);
    	    }
            delay(1000);
	}
    myRFID.AddicoreRFID_Halt();	//Command tag into hibernation ToDo : Figure this bit out.              
}


void send_bluetooth_message(String message_to_send) {
	BTSerial.println(message_to_send);
}

void setup() {                
	startup_usb_serial();
	startup_nfc_reader();
	startup_bluetooth_serial();
	inputString.reserve(200);
	
	assign_relay_pins();
	set_relay_pins_high(); // Make sure all the relays are off.
	
	display_hello_message_to_bluetooth_serial_out();
	Serial.println("setup function completed.");
}


void loop()
{
	check_nfc_tag_for_change_and_react_if_change_found();
	delay(1000);
	
	// Read from the Bluetooth module and send to the Arduino Serial Monitor
	
	/*
	
	if (BTSerial.available())
	{
		c = BTSerial.read();
		Serial.write(c);
	}
	
	// This is not utilized...
	
	// ToDo : Determine if this is cut out able...
    // Read from the Serial Monitor and send to the Bluetooth module
    
    if (Serial.available())
    {
        c = Serial.read();
        BTSerial.write(c);   
        
        // Echo the user input to the main window.
        // The ">" character indicates the user entered text.
        if (NL) { Serial.print(">");  NL = false; }
        Serial.write(c);
        if (c==10) { NL = true; }
    }
	*/
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
