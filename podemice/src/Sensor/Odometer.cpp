#include "Arduino.h"
#define DEG_TO_RAD 0.01745329251


float dist = 0;
float wheel_circumference = 19.4778744523; // in cm
int sensor1;
int sensor2;
int n_holes = 20;
int prev_reading1 = -1;
int prev_reading2 = -1;

void OdoSetup(int pin1, int pin2) {
    sensor1 = pin1;
    sensor2 = pin2;
    pinMode(sensor1, INPUT);
    pinMode(sensor2, INPUT);
}

// returns dist travelled since last reset in cm/s
float OdoLoop(unsigned long deltaMillis, float *disp_x, float *disp_y, float gyro_z) {
    if (digitalRead(sensor1) == 1 && prev_reading1 == 0) {
        dist += (1.0/n_holes) * wheel_circumference / 2;
        *disp_x = ((1.0/n_holes) * wheel_circumference) / 2 * sin(gyro_z * DEG_TO_RAD);

    }
    if (digitalRead(sensor2) == 1 && prev_reading2 == 0) {
        dist += (1.0/n_holes) * wheel_circumference / 2;
        *disp_y = ((1.0/n_holes) * wheel_circumference) / 2 * cos(gyro_z * DEG_TO_RAD);

    }
    prev_reading1 = digitalRead(sensor1);
    prev_reading2 = digitalRead(sensor2);
    return dist;
}