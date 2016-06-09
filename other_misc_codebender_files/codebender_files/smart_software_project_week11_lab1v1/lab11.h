#ifndef lab11_H_
#define lab11_H_

#include "Arduino.h"

#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050_6Axis_MotionApps20.h>

#include "smart_car_buzzer.h"
#include "smart_car_led_control.h"
#include "smart_car_movement.h"
#include "smart_car_sensors.h"

#include "smart_car_control_logic.h"

void infrared_sensor_read();

void line_tracing_enable();
void line_tracing_disable();

#ifdef __cplusplus

extern "C" {
    #endif
    void loop();
    void setup();
    #ifdef __cplusplus
}

#endif

#endif

