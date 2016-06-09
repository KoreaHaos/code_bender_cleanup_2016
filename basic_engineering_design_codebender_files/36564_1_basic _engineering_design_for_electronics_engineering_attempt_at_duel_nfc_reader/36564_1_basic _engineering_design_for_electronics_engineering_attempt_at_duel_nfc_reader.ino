// Example sketch to read the ID from an Addicore 13.56MHz RFID tag
// as found in the RFID AddiKit found at: 
// http://www.addicore.com/RFID-AddiKit-with-RC522-MIFARE-Module-RFID-Cards-p/126.htm

/*
who : Ben Haos
wat : A quick refactor of code found in a tutorial for setting up an nfc reader
wat : Hooked two NFC readers to Arduino in parallel(?) to see what would happen...
wat : They both read but seem to cancle out one another...
where : Created on CodeBender.
when : May 29th 2016
how : Just did it? How is always so hard.

*/

// Tutorial Source : https://www.addicore.com/v/vspfiles/downloadables/Product%20Downloadables/RFID_RC522/RFIDQuickStartGuide.pdf

#include <AddicoreRFID.h>
#include <SPI.h>

#define	uchar	unsigned char
#define	uint	unsigned int

//4 bytes tag serial number, the first 5 bytes for the checksum byte
uchar serNumA[5];

uchar fifobytes;
uchar fifoValue;

AddicoreRFID myRFID; // create AddicoreRFID object to control the RFID module

/////////////////////////////////////////////////////////////////////
//set the pins
/////////////////////////////////////////////////////////////////////
//const int chipSelectPin = 10;

const int chipSelectPin_one = 10;
const int chipSelectPin_two = 9;


const int NRSTPD_ONE = 5;
const int NRSTPD_TWO = 6;


//Maximum length of the array
// The variable MAX_LEN is ... 
#define MAX_LEN 16

void startup_serial() {
	Serial.begin(9600);                        // RFID reader SOUT pin connected to Serial RX pin at 9600bps 
}

int toggle_status = 0;

void toggle_nfc_reader_pin_thingy() {
	
	if (toggle_status == 0 ) {
		digitalWrite(chipSelectPin_one, HIGH);
		digitalWrite(chipSelectPin_two, LOW);
		digitalWrite(NRSTPD_ONE, HIGH);
		digitalWrite(NRSTPD_TWO, LOW);
		
		
		toggle_status = 1;
		Serial.println("toggle switched to 1");
	} else {
		digitalWrite(chipSelectPin_two, HIGH);
		digitalWrite(chipSelectPin_one, LOW);
		digitalWrite(NRSTPD_ONE, LOW);
		digitalWrite(NRSTPD_TWO, HIGH);
		toggle_status = 0;
		Serial.println("toggle switched to 0");
	}
}

void startup_nfc_reader() {
	// start the SPI library: (wat's this?)
	SPI.begin();
	
	pinMode(chipSelectPin_one, OUTPUT);		// Set digital pin 10 as OUTPUT to connect it to the RFID /ENABLE pin 
	pinMode(chipSelectPin_two, OUTPUT);		// Set digital pin 10 as OUTPUT to connect it to the RFID /ENABLE pin 
	//digitalWrite(chipSelectPin, LOW);	// Activate the RFID reader
	
	pinMode(NRSTPD_ONE,OUTPUT);                     // Set digital pin 10 , Not Reset and Power-down
	//digitalWrite(NRSTPD, HIGH);
	
	pinMode(NRSTPD_TWO,OUTPUT);                     // Set digital pin 10 , Not Reset and Power-down
	//digitalWrite(NRSTPD_ONE, LOW);
	
	myRFID.AddicoreRFID_Init();  
}



// This is the original algorthim from the tutorial example. It is useful for
// debuging and understanding.

void check_for_nfc_tag_and_serial_serial_print_output_if_found() {
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
	}

	//Anti-collision, return tag serial number 4 bytes
	status = myRFID.AddicoreRFID_Anticoll(str);
	if (status == MI_OK)
	{
            checksum1 = str[0] ^ str[1] ^ str[2] ^ str[3];
            Serial.println("The tag's number is  : ");
    	    //Serial.print(2);
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
            
            // Should really check all pairs, but for now we'll just use the first
            if(str[0] == 156)                      //You can change this to the first byte of your tag by finding the card's ID through the Serial Monitor
            {
                Serial.print("Hello Craig!\n");
            } else if(str[0] == 244) {             //You can change this to the first byte of your tag by finding the card's ID through the Serial Monitor
                Serial.print("Hello Erin!\n");
            }
            Serial.println();
            delay(1000);
            //toggle_nfc_reader_pin_thingy();
	}
    myRFID.AddicoreRFID_Halt();		   //Command tag into hibernation ToDo : Figure this bit out.
    
}

void setup() {                
  startup_serial();
  startup_nfc_reader();
  Serial.println("Setup function completed.");
  toggle_nfc_reader_pin_thingy();
}

void loop()
{
	check_for_nfc_tag_and_serial_serial_print_output_if_found();
	toggle_nfc_reader_pin_thingy();
	delay(2000);
}