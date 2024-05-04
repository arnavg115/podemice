#ifndef SENSOR
#define SENSOR

struct Sensors
{
    float gyro_z;
    int ir_sensor;
    float ultrasonic1;
    float ultrasonic2;
    float displacement;
    float velocity;
    unsigned long last_print_mil;
};


void SensorSetup(int a[]);
Sensors SensorStep(unsigned long currentMillis, unsigned long deltaMillis);

#endif