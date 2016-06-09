// Example sketch to read the ID from an Addicore 13.56MHz RFID tag
// as found in the RFID AddiKit found at: 
// http://www.addicore.com/RFID-AddiKit-with-RC522-MIFARE-Module-RFID-Cards-p/126.htm

/*

who : Ben Haos
wat : 
where : Created on CodeBender to interact with app created on app inventor.
when : not done yet.
how : we'll see!

*/

// NFC Tutorial Source : https://www.addicore.com/v/vspfiles/downloadables/Product%20Downloadables/RFID_RC522/RFIDQuickStartGuide.pdf
// BlueTooth Tutorial SOURCE : http://www.martyncurrey.com/hc-05-fc-114-and-hc-06-fc-114-part-2-basic-at-commands/

// App Inventor App : 
/* NFC BITS */

#include <AddicoreRFID.h>
#include <SPI.h>

#define	uchar	unsigned char
#define	uint	unsigned int

bool have_valid_tag = false;

//4 bytes tag serial number, the first 5 bytes for the checksum byte
uchar serNumA[5];

uchar fifobytes;
uchar fifoValue;

AddicoreRFID myRFID; // create AddicoreRFID object to control the RFID module

/////////////////////////////////////////////////////////////////////
//set the pins
/////////////////////////////////////////////////////////////////////
const int chipSelectPin = 10;
const int NRSTPD = 5;

//Maximum length of the array
#define MAX_LEN 16

#define LED_GREEN_PIN 8
#define LED_RED_PIN 9

/* BLUETOOTH BITS */

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3); // RX | TX

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

char c = ' ';
boolean NL = true;


void light_green_led() {
	digitalWrite(LED_GREEN_PIN, HIGH);
}

void shutdown_green_led() {
	digitalWrite(LED_GREEN_PIN, LOW);	
}

void light_red_led() {
	digitalWrite(LED_RED_PIN, HIGH);
}

void shutdown_red_led() {
	digitalWrite(LED_RED_PIN, LOW);	
}

void manage_led(bool green_should_be_lit) {
	if (green_should_be_lit){
		shutdown_red_led();
		light_green_led();
	} else {
		shutdown_green_led();
		light_red_led();
	}
}

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
