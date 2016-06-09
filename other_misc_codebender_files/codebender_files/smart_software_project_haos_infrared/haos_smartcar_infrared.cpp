#include "Arduino.h"

#define S_DIN 42
#define S_SCLK 43
#define S_SYNCN 44
#define IN_SEN_EN 26

// Arduino Mega 2560 InfraRed sensors pin assignments ararays.
int arduino_mega_2560_analog_pins_for_infrared[8] = {A0,A1,A2,A3,A4,A5,A6,A7};
int arduino_mega_2560_digitl_pins_for_infrared[8] = {30,31,32,33,34,35,36,37};

// The arrays to set the pin assignments to.
int SensorAnalog[8];
int SensorDigitl[8];

int dac_val_min_wav_ret[8]; 
int dac_val_max_wav_ret[8];

boolean sense_analogue;
boolean sense_digitils;

boolean sensors_are_said_to_be__reading_black;

boolean duel_read_mode;

void create_infrared_sensor_pin_array(int * array_to_populate, int * array_to_use_for_population)
{
	for (int z = 0; z < 8; z++)
	{
		array_to_populate[z] = array_to_use_for_population[z];
	}
}

void set_sensors_read_function_to_analogue(boolean to_do_or_not_to_do_that_is_the_question)
{
	sense_analogue = to_do_or_not_to_do_that_is_the_question;
	if ( !duel_read_mode )
	{
		sense_digitils = !to_do_or_not_to_do_that_is_the_question;
	}
	
}

void set_sensors_read_function_to_digital(boolean to_do_or_not_to_do_that_is_the_question)
{
	sense_digitils = to_do_or_not_to_do_that_is_the_question;
	if ( !duel_read_mode )
	{
		sense_analogue = !to_do_or_not_to_do_that_is_the_question;
	}
}

void init_analogue_infrared_sensors()
{
	create_infrared_sensor_pin_array(SensorAnalog, arduino_mega_2560_analog_pins_for_infrared);
}

void initilize_dac_min_max_arrays()
{
	for (int z = 0; z < 8; z++)
	{
		dac_val_min_wav_ret[z] = 0; 
		dac_val_max_wav_ret[z] = 0;
	}
}

void setup_ports_to_recieve_digital_output_from_sensors()
{
	for (int z = 0; z < 8; z++)
	{
	    pinMode(SensorDigitl[z], INPUT);
	}
}	

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

void send_signal_for_write_through_mode_to_ir_sensor_package()
{
	DAC_setting(0x9000);
}

void DAC_CH_Write(unsigned int ch, unsigned int da)
{
    unsigned int data = ((ch << 12) & 0x7000) | ((da << 4) & 0x0FF0);
    DAC_setting(data);
}

void set_digital_cutoff_point_values()
{
    for (int z = 0; z < 8; z++)
    {
        int mean_val = (dac_val_min_wav_ret[z] + dac_val_min_wav_ret[z])/2; //10-bit
        DAC_CH_Write(z, mean_val >> 2); //should be 8-bit
    }
}

void init_digital_infrared_sensors()
{
	create_infrared_sensor_pin_array(SensorDigitl, arduino_mega_2560_digitl_pins_for_infrared);
	initilize_dac_min_max_arrays();
	setup_ports_to_recieve_digital_output_from_sensors();
	send_signal_for_write_through_mode_to_ir_sensor_package();
}


int * infra_sensor_read(int infra_sensor_reading_request[8])
{
	//int z;
	if (sense_analogue)
	{
		for(int z = 7; z >= 0; z--)
		{
			infra_sensor_reading_request[z] = analogRead(SensorAnalog[z]);
		}
	}
	if (sense_digitils)
	{
		for(int z = 7; z >= 0; z--)
		{
			infra_sensor_reading_request[z] = digitalRead(SensorDigitl[z]);
		}
	}
	return infra_sensor_reading_request;
}

//int dac_val_min_wav_ret[8]; 
//int dac_val_max_wav_ret[8];

void set_sensor_reads_for_white_values()
{
	infra_sensor_read(dac_val_max_wav_ret);			
}

void set_sensor_reads_for_black_values()
{
	infra_sensor_read(dac_val_min_wav_ret);			
}


