#include "Arduino.h"


float dist = 0;
float wheel_circumference = 19.4778744523; // in cm
int sensor1;
int sensor2;
int n_holes = 20;
int prev_reading = -1;

void OdoSetup(int pin1/*, int pin2*/) {
    sensor1 = pin1;
    //sensor2 = pin2;
    pinMode(sensor1, INPUT);
    //pinMode(sensor2, INPUT);
}

// returns dist travelled since last reset in cm/s
float OdoLoop(unsigned long deltaMillis) {
    if (digitalRead(sensor1) == 1 && prev_reading == 0) {
        dist += (1.0/n_holes) * wheel_circumference;
    }
    prev_reading = digitalRead(sensor1);
    return dist;
}