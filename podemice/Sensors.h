#ifndef SENSOR
#define SENSOR

struct Sensors
{
    float gyro_z;
    int ir_sensor;
    float ultrasonic1;
    float ultrasonic2;
    float displacement;
};


void SensorSetup(int a[]);
Sensors SensorStep();

#endif