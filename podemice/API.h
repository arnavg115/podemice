#include "Sensors.h"
#pragma once

class API {
    public:
        bool moveForward(int dist);

        bool turnLeft(unsigned char deg);
        bool turnRight(unsigned char deg);

        bool wallLeft();
        bool wallRight();
        bool wallFront();
};

void ControlSetup(int pins[]);
void ControlLoop(Sensors info);