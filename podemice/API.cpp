#include "API.h"
#include "Motors.h"
#include "Sensors.h"
#include "Arduino.h"

Sensors data;

bool API::moveForward(int dist) {
    int totalCM = dist * 18;
    float startDisplacement = data.displacement;
    ToggleMotor1(1);
    ToggleMotor2(1);
    if (data.displacement - startDisplacement > totalCM) {
        ToggleMotor1(0);
        ToggleMotor2(0);
        return true;
    }
    return false;
}

bool API::turnLeft(unsigned char deg) {
    float startAngle = data.gyro_z;
    ToggleMotor1(-1);
    ToggleMotor2(1);
    if (abs(startAngle - data.gyro_z) > deg) {
        ToggleMotor1(0);
        ToggleMotor2(0);
        return true;
    }
    return false;
}

bool API::turnRight(unsigned char deg) {
    float startAngle = data.gyro_z;
    ToggleMotor1(1);
    ToggleMotor2(-1);
    if (abs(startAngle - data.gyro_z) > deg) {
        ToggleMotor1(0);
        ToggleMotor2(0);
        return true;
    }
    return false;
}

bool API::wallLeft() {
    return data.ultrasonic1 < 6;
}

bool API::wallRight() {
    return data.ultrasonic2 < 6;
}

bool API::wallFront() {
    return data.IRSENSOR;
}

void ControlSetup(int pins[]){
    MotorSetup(pins[0], pins[1]);
}

void ControlStep(Sensors info){
    data = info;
}