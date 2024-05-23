#include <sys/_types.h>
#include "Sensors.h"
#include "Arduino.h"
#include "src/Sensor/Gyro.h"
#include "src/Sensor/IRSensor.h"
#include "src/Sensor/Ultrasonic.h"
#include "src/Sensor/Odometer.h"

#define SENSOR_FREQ 1000

struct Sensors sensors;
struct Ultrasonic us;

void SensorSetup (int pins[]) {
    // GyroSetup();
    IRSetup(pins[0]);
    UltrasonicSetup(pins[2], pins[1], pins[4], pins[3]);
    OdoSetup(pins[12], pins[13]);
    sensors.disp_x = 0;
    sensors.disp_y = 0;
}

Sensors SensorStep(unsigned long currentMillis, unsigned long deltaMillis) {
    if(deltaMillis > 1000){
        // sensors.gyro_z = GyroLoop(currentMillis, deltaMillis);
        sensors.displacement = OdoLoop(deltaMillis, &(sensors.disp_x), &(sensors.disp_y), sensors.gyro_z);

        sensors.last_print_mil = millis();

        sensors.ir_sensor = IRLoop();
        us = UltrasonicStep();
        sensors.ultrasonic1 = us.u1;
        sensors.ultrasonic2 = us.u2;
    }
    
    return sensors;
}