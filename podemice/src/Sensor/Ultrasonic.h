#ifndef ULTRASONIC
#define ULTRASONIC

struct Ultrasonic
{
    float u1;
    float u2;
};

void UltrasonicSetup(int pin1, int pin2, int pin3, int pin4);
Ultrasonic UltrasonicStep();

#endif