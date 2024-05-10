#include "Arduino.h"

int m1 = -1;
int m1bw = -1;
int m2 = -1;
int m2bw = -1;

void MotorSetup(int p1, int n1, int p2, int n2) {
    m1 = p1;
    m1bw = n1;
    m2 = p2;
    m2bw = n2;

    pinMode(m1, OUTPUT);
    pinMode(m1bw, OUTPUT);
    pinMode(m2, OUTPUT);
    pinMode(m2bw, OUTPUT);
}

void ToggleMotor1(char dir) {
    switch (dir) {
        case -1:
            digitalWrite(m1bw, HIGH);
            digitalWrite(m1, LOW);
            break;
        case 0:
            digitalWrite(m1bw, LOW);
            digitalWrite(m1, LOW);
            break;
        case 1:
            digitalWrite(m1bw, LOW);
            digitalWrite(m1, HIGH);
    }
}

void ToggleMotor2(char dir) {
    switch (dir) {
        case -1:
            digitalWrite(m2bw, HIGH);
            digitalWrite(m2, LOW);
            break;
        case 0:
            digitalWrite(m2bw, LOW);
            digitalWrite(m2, LOW);
            break;
        case 1:
            digitalWrite(m2bw, LOW);
            digitalWrite(m2, HIGH);
    }
}

/*
int m1 = 2;
int m1bw = 4; 
int m2 = 3;
int m2bw = 6;
bool m1_on = false;
bool m2_on = false;
unsigned long startTime = -1;

void MotorSetup(int p1, int p2, int p3, int p4) {
    m1 = p1;
    m1bw = p3;
    m2 = p2;
    m2bw = p4;
    pinMode(m1, OUTPUT);
    pinMode(m1bw, OUTPUT);
    pinMode(m2, OUTPUT);
    pinMode(m2bw, OUTPUT);
}

void ToggleMotor1(char dir) {
    switch (dir) {
        case -1:
            digitalWrite(m1bw, HIGH);
            break;
        case 0:
            digitalWrite(m1, LOW);
            digitalWrite(m1bw, LOW);
            break;
        case 1:
            digitalWrite(m1, HIGH);
        default:
            Serial.print("something has gone horribly wrong");
    }
}

void ToggleMotor2(char dir) {
    switch (dir) {
        case -1:
            digitalWrite(m2bw, HIGH);
            break;
        case 0:
            digitalWrite(m2, LOW);
            digitalWrite(m2bw, LOW);
            break;
        case 1:
            digitalWrite(m2, HIGH);
        default:
            Serial.print("something has gone horribly wrong");
    }
}*/