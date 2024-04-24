#ifndef SENSOR
#define SENSOR

struct Sensors
{
    float gyro_z;
    int ir_sensor;
    float UltraSonic1;
    float UltraSonic2;
};


void SensorSetup(int a[]);
Sensors SensorStep();

#endif