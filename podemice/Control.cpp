// This file is for all control logic

#include "Motors.h"
#include "Sensors.h"

// pins = [motor1, motor2]
void ControlSetup(int pins[]){
    MotorSetup(pins[0], pins[1]);
}


void ControlLoop(Sensors info){
    return;
}
