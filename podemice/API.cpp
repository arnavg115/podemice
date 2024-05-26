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

int wait = 0;

int startWheel1 = 0;
int startWheel2 = 0;

// "wheel1" is the right wheel
// "wheel2" is the left wheel

// "motor1" is the right motor
// "motor2" is the left motor

bool API::moveForward(int dist) {
    int totalCM = dist * 18.5;

    /*if (!turning && data.ultrasonic1 && data.ultrasonic2 && offset < 0.1) {
        AdjustMotor1();
    } else if (!turning && data.ultrasonic1 && data.ultrasonic2 && offset > 0.1) {
        AdjustMotor2();
    } else {
        ToggleMotor1(1);
        ToggleMotor2(1);
    }*/

    //Serial.print("Wheel 1 - Wheel 2: ");
    //Serial.println((data.wheel1 - startWheel1) - (data.wheel2 - startWheel2));

    if ((data.wheel1 - startWheel1) - (data.wheel2 - startWheel2) >= 2) {
        //AdjustMotor2(235);
        //ToggleMotor1(1);
        AdjustMotor2(235);
        ToggleMotor1(1);
    } else if ((data.wheel1 - startWheel1) - (data.wheel2 - startWheel2) <= -2) {
        //AdjustMotor2(235);
        //ToggleMotor1(1);
        AdjustMotor1(235);
        ToggleMotor2(1);
    } else {
        ToggleMotor1(1);
        ToggleMotor2(1);
    }

    Serial.print("data dispx: ");
    Serial.println(data.disp_x);
    Serial.print("data dispy: ");
    Serial.println(data.disp_y);
    Serial.print("wheel1: ");
    Serial.println(data.wheel1);
    Serial.print("wheel2: ");
    Serial.println(data.wheel2);
    Serial.print("disp: ");
    Serial.println(data.displacement);
    if (max(abs(data.disp_x - startDispX), abs(data.disp_y - startDispY)) > totalCM - 0.5) {
        Serial.println("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
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
    //ToggleMotor1(-1);
    //ToggleMotor2(1);
    AdjustMotor1B(230);
    AdjustMotor2(230);
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
    //ToggleMotor1(1);
    //ToggleMotor2(-1);
    AdjustMotor2B(230);
    AdjustMotor1(230);
    if (abs(startAngle - data.gyro_z) > deg - 1) {
        ToggleMotor1(0);
        ToggleMotor2(0);
        turning = 0;
        status = 0;
        return true;
    }
    return false;
}

bool API::wallLeft() {
    return data.ultrasonic1 > 0 && data.ultrasonic1 < 6;
}

bool API::wallRight() {
    if (data.ultrasonic1 == 0) { // temp if statement delete later
        return true;
    }
    return data.ultrasonic2 > 0 && data.ultrasonic2 < 6;
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
        
        /*if (wait) {
            status = 0;
            delay(5000);
            wait = 1;
        } else {
            status = 0x8001;// 2; 
            wait = 0;
        }*/
        
        status = getCommand();
        
        Serial.println("just got new command: ");
        Serial.println(status);

        switch (status) {
        case 1:
            startAngle = data.gyro_z;
            break;
        case 2:
            startAngle = data.gyro_z;
            break;
        case 3:
            startAngle = data.gyro_z;
            break;
        default:
            startDisplacement = data.displacement;
            startDispX = data.disp_x;
            startDispY = data.disp_y;
            startWheel1 = 0;
            startWheel2 = 0;
            Serial.print((status & 0xf) * 18.5);
        }
    }
        //Serial.println(status);

    switch (status) {
        case 1:
            //startAngle = data.gyro_z;
            //Serial.println("turning around 2222222222222222222222222222222222222222222");
            API::turnLeft(180);
            break;
        case 2:
            //startAngle = data.gyro_z;
            //Serial.println("turning left 3333333333333333333333333333333333333333");
            API::turnLeft(90);
            break;
        case 3:
            //startAngle = data.gyro_z;
            //Serial.println("turning right 44444444444444444444444444444444444444444444");

            API::turnRight(90);
            break;
        case 0:
            ToggleMotor1(0);
            ToggleMotor2(0);
            delay(3000);
            break;
        default:
            //startDisplacement = data.displacement;
            //startDispX = data.disp_x;
            //startDispY = data.disp_y;
            //startWheel1 = 0;
            //startWheel2 = 0;
            //Serial.println("moving forward 555555555555555555555555555555555555555555555");

            API::moveForward(status & 0xf);
    }
    offset = data.ultrasonic1 - data.ultrasonic2;
}