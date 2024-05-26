#ifndef SENSOR
#define SENSOR

struct Sensors
{
    float gyro_z;
    int ir_sensor;
    float ultrasonic1;
    float ultrasonic2;
    float displacement;
    float disp_x;
    float disp_y;
    float velocity;
    unsigned long last_print_mil;
    int wheel1;
    int wheel2;
};


void SensorSetup(int a[]);
Sensors SensorStep(unsigned long currentMillis, unsigned long deltaMillis);

#endif