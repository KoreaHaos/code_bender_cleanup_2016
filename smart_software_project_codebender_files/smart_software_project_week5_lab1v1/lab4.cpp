//smart_software_project_week5_lab1v1
// Variable for initial comm. message.

#include  "lab4.h"


unsigned char text[] = "\r\n Welcome! Arduino Mega 2560 \r\n UART0 Test Program.\r\n";
void setup()
{
    Serial.begin(115200);   // Set the baud rate for serial port.
    
    // Display welcome message.
    
    int index=0;
    
    while(text[index] !='\0')   // Loop through text array until all letters sent.
    {
        Serial.write(text[index++]);
    }
    
    // Display a prompt for programs output.
    Serial.print("ECHO Team Five - Haos # >> ");
}

void loop()
{
    // Synopsis : If serial recieves input, write it back to output.
    // If Serial.available() is greater than zero, the buffer contains data.
    
    if(Serial.available() > 0) {
        
        // write the data read from serial.
        Serial.write(Serial.read());
    }
}
