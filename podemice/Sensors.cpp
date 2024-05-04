#include <sys/_types.h>
#include "Sensors.h"
#include "Arduino.h"
#include "src/Sensor/Gyro.h"
#include "src/Sensor/IRSensor.h"
#include "src/Sensor/Ultrasonic.h"

#define SENSOR_FREQ 1000


float gyroOutput[2];
struct Sensors sensors;
struct Ultrasonic us;

// pins = [ir_sensor_pin, echo1, trig1, echo1, trig2, encoder 1, encoder 2]
void SensorSetup (int pins[]) {
    GyroSetup();
    IRSetup(pins[0]);
    UltrasonicSetup(pins[2], pins[1], pins[4], pins[3]);
}

Sensors SensorStep(unsigned long currentMillis, unsigned long deltaMillis) {
    // unsigned long currentMillis = millis();
    // unsigned long deltaMillis = currentMillis - lastPrintMillis;
    
    // if(deltaMillis > 1000){
    //     //gyroOutput = GyroLoop(currentMillis, deltaMillis);
    sensors.gyro_z = GyroLoop(currentMillis, deltaMillis);

    sensors.last_print_mil = millis();

    sensors.ir_sensor = IRLoop();
    us = UltrasonicStep();
    sensors.ultrasonic1 = us.u1;
        // sensors.ultrasonic2 = us.u2;
    // }
    
    return sensors;
}