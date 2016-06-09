#ifndef HAOS_HAOS_SMARTCAR_SERIAL_H
#define HAOS_HAOS_SMARTCAR_SERIAL_H

#include <Arduino.h> //needed for Serial.println
#include <string.h> //needed for memcpy

void init_serial_event_listener(int serial_comm_channel, int serial_comm_speed, int serial_string_reserve_size);
bool serial_has_message();
bool send_string_serial_message(int serial_comm_channel, String message_to_send);

/*
void init_smart_car_serial_usb();
void init_smart_car_serial_blt();

bool serial_has_message_from_usb();
bool serial_has_message_from_blt();

bool send_dec_message(int int_to_send, int comm_cnl_to_use);
bool send_str_message(String strng_to_send, , int comm_cnl_to_use);

*/
#endif
