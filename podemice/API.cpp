#include "API.h"
#include "Motors.h"
#include "Sensors.h"
#include "Arduino.h"
#include "FloodFill.h"

Sensors data;
int turning = 0;
int status = 0;
float startDisplacement = 0;
float startDispX = 0;
float startDispY = 0;
float startAngle = 0;
float offset = 0;

bool API::moveForward(int dist) {
    int totalCM = dist * 18.5;
    ToggleMotor1(1);
    ToggleMotor2(1);

    if (!turning && data.ultrasonic1 && data.ultrasonic2 && offset < 0.1) {
        AdjustMotor1();
    } else if (!turning && data.ultrasonic1 && data.ultrasonic2 && offset > 0.1) {
        AdjustMotor2();
    } else {
        ToggleMotor1(1);
        ToggleMotor2(1);
    }

    if (max(abs(data.disp_x - startDispX), abs(data.disp_y - startDispY)) > totalCM - 0.5) {
        ToggleMotor1(0);
        ToggleMotor2(0);
        status = 0;
        return true;
    }
    return false;
}

bool API::turnLeft(unsigned char deg) {
    turning = 1;
    // float startAngle = data.gyro_z;
    ToggleMotor1(-1);
    ToggleMotor2(1);
    if (abs(startAngle - data.gyro_z) > deg - 1) {
        ToggleMotor1(0);
        ToggleMotor2(0);
        turning = 0;
        status = 0;
        return true;
    }
    return false;
}

bool API::turnRight(unsigned char deg) {
    turning = 1;
    ToggleMotor1(1);
    ToggleMotor2(-1);
    if (abs(startAngle - data.gyro_z) > deg - 3) {
        ToggleMotor1(0);
        ToggleMotor2(0);
        turning = 0;
        status = 0;
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
    return data.ir_sensor;
}

void ControlSetup(int pins[]){
    MotorSetup(pins[5], pins[7], pins[10], pins[8], pins[9], pins[11]);
}

void ControlStep(Sensors info){
    data = info;
    if (!status) {
        status = getCommand();
    }
    switch (status) {
        case 1:
            startAngle = data.gyro_z;
            API::turnLeft(180);
        case 2:
            startAngle = data.gyro_z;
            API::turnLeft(90);
        case 3:
            startAngle = data.gyro_z;
            API::turnRight(90);
        default:
            startDisplacement = data.displacement;
            startDispX = data.disp_x;
            startDispY = data.disp_y;
            API::moveForward(status & 0xff);
    }
    offset = data.ultrasonic1 - data.ultrasonic2;
}