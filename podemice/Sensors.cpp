#include "Sensor.h"
#include "Arduino.h"
#include "Gyro.h"
#include "IRSensor.h"
#include "Ultrasonic.h"

#define SENSOR_FREQ 100


unsigned long lastPrintMillis = 0;
struct Sensors sensors;
struct Ultrasonic us;

// pins = [ir_sensor_pin, echo1, trig1, echo1, trig2, encoder 1, encoder 2]
void SensorSetup (int pins[]) {
    GyroSetup();
    IRSetup(pins[0]);
    UltrasonicSetup(pins[2], pins[1], pins[4], pins[3]);
}

Sensors SensorStep() {
    unsigned long currentMillis = millis();
    unsigned long deltaMillis = currentMillis - lastPrintMillis;
    
    if(deltaMillis > SENSOR_FREQ){
        sensors.gyro_z = GyroLoop(currentMillis, deltaMillis);
        sensors.ir_sensor = IRLoop();
        lastPrintMillis = currentMillis;
        us = UltrasonicStep();
        sensors.ultrasonic1 = us.u1;
        sensors.ultrasonic2 = us.u2;
    }
    
    return sensors;
}