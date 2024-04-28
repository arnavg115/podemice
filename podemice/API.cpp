#include "API.h"
#include "Motors.h"
#include "Sensors.h"

Sensors data;

bool API::moveForward(int dist) {
    int totalCM = dist * 18;
    float startDisplacement = data.displacement;
    ToggleMotor1(1);
    ToggleMotor2(1);
    while (data.displacement - startDisplacement < totalCM) {}
    ToggleMotor1(0);
    ToggleMotor2(0);
}

bool API::turnLeft(unsigned char deg) {
    return false;
}

bool API::turnRight(unsigned char deg) {
    return false;
}

bool API::wallLeft() {
    return false;
}

bool API::wallRight() {
    return false;
}

bool API::wallFront() {
    return false;
}

void ControlSetup(int pins[]){
    MotorSetup(pins[0], pins[1]);
}

void ControlLoop(Sensors info){
    data = info;
}