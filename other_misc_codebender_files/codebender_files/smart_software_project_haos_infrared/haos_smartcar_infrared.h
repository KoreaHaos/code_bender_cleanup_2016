#ifndef HAOS_HAOS_SMARTCAR_INFRARED_H
#define HAOS_HAOS_SMARTCAR_INFRARED_H

void init_analogue_infrared_sensors();
bool init_digital_infrared_sensors();

int * infra_sensor_read(int infra_sensors_readings[8], int sensors_pin_assig[8], bool read_analog);

#endif
