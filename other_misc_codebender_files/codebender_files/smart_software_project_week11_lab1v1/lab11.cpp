#include  "lab11.h"

// These are ... 	ToDo : FILL IN THIS BIT!

#define S_DIN 42
#define S_SCLK 43
#define S_SYNCN 44
#define IN_SEN_EN 26

MPU6050 mpu;

uint8_t mpuIntStatus; // holds actual interrupt status byte from MPU
uint8_t devStatus; // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize; // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount; // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

//Quaternion q; // [w, x, y, z] quaternion container
//VectorFloat gravity; // [x, y, z] gravity vector
float ypr[3]; // [yaw, pitch, roll] yaw/pitch/roll container and gravity vector

// These ararays are the pin assignments for the InfraRed sensors.
// SensorA is for the Analog and SensorD is for the digital.

int SensorA[8] = {A0,A1,A2,A3,A4,A5,A6,A7};
int SensorD[8] = {30,31,32,33,34,35,36,37};


void DAC_setting(unsigned int data)
{
    int z;
    
    digitalWrite(S_SCLK,HIGH);
    delayMicroseconds(1);
    
    digitalWrite(S_SCLK,LOW);
    delayMicroseconds(1);
   
    digitalWrite(S_SYNCN,LOW);
    delayMicroseconds(1);
    
    
    
    for(z = 15; z >= 0; z--)
    {
        digitalWrite(S_DIN,(data>>z)&0x1);
        
        digitalWrite(S_SCLK,HIGH);
        delayMicroseconds(1);
        
        digitalWrite(S_SCLK,LOW);
        delayMicroseconds(1);
    }
    
    
    
    digitalWrite(S_SYNCN, HIGH);
}
	
void DAC_CH_Write(unsigned int ch, unsigned int da)
{
    unsigned int data = ((ch << 12) & 0x7000) | ((da << 4) & 0x0FF0);
    DAC_setting(data);
}




void infrared_sensor_read()
{
    int z;

    /*
	
	This for loop outputs the analog readings of the InfraRed sensors.
	
    */

    for(z = 7; z >= 0; z--)
    {
        unsigned int val = analogRead(SensorA[z]);
        Serial.print(val);
        Serial.print(" ");
    }
    
    Serial.println("");
    
    /*
	
	This for loop outputs the digital readings of the InfraRed sensors.
	It should be commented out until manual setup has been done.
    */
    
    for(z = 7; z >= 0; z--)
    {
        unsigned int val = digitalRead(SensorD[z]);
        Serial.print(val);
        Serial.print(" ");
    }
}

boolean line_tracing = false;

void line_tracing_enable()
{
    line_tracing = true;
    Serial.write("Line tracing is enabled..");
}

void line_tracing_disable()
{
    line_tracing = false;
    move_stop();
    Serial.write("Line tracing is disabled..");
}

void setup()
{
	//Wire.begin();
	
	setup_led_pins();
	setup_ports_for_movement();
	setup_buzzer_pin();
	setup_sensors();
	
	setup_smart_car_control_logic();
	
	int z;
    
    // ToDo : Add a feature to make this happen from the android app. !!!
    
    // For this script, these values need to be entered manually.
    // InfraRed Sensor Value on black.
    int dac_val_min[8] = {101, 132, 109, 107, 137, 163, 119, 67};
    
    // InfraRed Sensor Value on white.
    int dac_val_max[8] = {393, 571, 503, 514, 642, 616, 480, 358};

	pinMode(IN_SEN_EN,OUTPUT);
    pinMode(S_DIN,OUTPUT);
    pinMode(S_SCLK,OUTPUT);
    pinMode(S_SYNCN,OUTPUT);
    
    digitalWrite(S_SCLK,LOW);
    digitalWrite(S_SYNCN,HIGH);
    digitalWrite(IN_SEN_EN,HIGH);

    /*
    These two for loops should be commented out initially and then after reading
    a sensor reading from a white input and a black input and inserting the 
    values into dac_val_min[] and dac_val_max[] they should be uncommented.
	*/
    
    for (z=0; z<8; z++)
    {
        pinMode(SensorD[z], INPUT);
    }
    
    DAC_setting(0x9000); //for Write-Through Mode
    

	
    for (z=0; z<8; z++)
    {
        int mean_val = (dac_val_min[z]+dac_val_max[z])/2; //10-bit
        DAC_CH_Write(z, mean_val >> 2); //should be 8-bit
    }
	
	
	
	buzz_ready();
}



void loop()
{


    if (line_tracing == true)
    {
        unsigned char sensor_data = 0;
        int z;
        for(z=0;z<8;z++)
        {
            unsigned int val = digitalRead(SensorD[z]);
            sensor_data |= (val << z);
        }
        
        sensor_data = ~sensor_data;
        
        Serial.print(sensor_data, HEX);
        
        Serial.write(" ");
        
        switch (sensor_data)
        {
            //our move forward situations.
            case 0x18:
            case 0x10:
            case 0x08:
            case 0x38:
            case 0x1c:
            case 0x3c:
            move_forward_speed(100, 100);
            break;
            
            //our turn right situations.
            case 0x0c:
            case 0x04:
            case 0x06:
            case 0x0e:
            case 0x1e:
            case 0x0f:
            turn_right_speed(150, 10);
            break;
            
            //our turn left situations.
            case 0x30:
            case 0x20:
            case 0x60:
            case 0x70:
            case 0x78:
            case 0xf0:
            turn_left_speed(10, 150);
            break;
            
             //our spin right situations.
           case 0x07:
            case 0x03:
            case 0x02:
            case 0x01:
            turn_pivot_right_speed(-100, 100);
            break;
            
             //our spin left situations.
           case 0xc0:
            case 0x40:
            case 0x80:
            case 0xe0:
            turn_pivot_left_speed(100, -100);
            break;
            
            case 0x00:
            case 0xff:
            move_stop();
            break;
            default:
            move_stop();
            break;
        }
        delay(5);
    }
}


