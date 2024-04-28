#include "Sensors.h"
#pragma once

class API {
public:
    static bool moveForward(int dist);

    static bool turnLeft(unsigned char deg);
    static bool turnRight(unsigned char deg);

    static bool wallLeft();
    static bool wallRight();
    static bool wallFront();
};

void ControlSetup(int pins[]);
void ControlStep(Sensors info);