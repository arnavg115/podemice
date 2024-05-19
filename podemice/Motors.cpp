#include "Arduino.h"

int m1 = -1;
int m1bw = -1;
int m1enable = -1;
int m2 = -1;
int m2bw = -1;
int m2enable = -1;

const int freq = 30000;
const int pwmChannel1 = 0;
const int pwmChannel2 = 1;
const int resolution = 8;
int dutyCycle1 = 225;
int dutyCycle2 = 225;

void MotorSetup(int p1, int n1, int e1, int p2, int n2, int e2) {
    m1 = p1;
    m1bw = n1;
    m1enable = e1;
    m2 = p2;
    m2bw = n2;
    m2enable = e2;

    pinMode(m1, OUTPUT);
    pinMode(m1bw, OUTPUT);
    pinMode(m1enable, OUTPUT);
    pinMode(m2, OUTPUT);
    pinMode(m2bw, OUTPUT);
    pinMode(m2enable, OUTPUT);

    ledcSetup(pwmChannel1, freq, resolution);
    ledcSetup(pwmChannel2, freq, resolution);
    ledcAttachPin(m1enable, pwmChannel1);
    ledcAttachPin(m2enable, pwmChannel2);

}

void ToggleMotor1(char dir) {
    switch (dir) {
        case -1:
            dutyCycle1 = 225;
            ledcWrite(pwmChannel1, dutyCycle1);
            digitalWrite(m1bw, HIGH);
            digitalWrite(m1, LOW);
            break;
        case 0:
            digitalWrite(m1bw, LOW);
            digitalWrite(m1, LOW);
            break;
        case 1:
            dutyCycle1 = 255;
            ledcWrite(pwmChannel1, dutyCycle1);
            digitalWrite(m1bw, LOW);
            digitalWrite(m1, HIGH);
    }
}

void ToggleMotor2(char dir) {
    switch (dir) {
        case -1:
            dutyCycle2 = 255;
            ledcWrite(pwmChannel2, dutyCycle2);
            digitalWrite(m2bw, HIGH);
            digitalWrite(m2, LOW);
            break;
        case 0:
            digitalWrite(m2bw, LOW);
            digitalWrite(m2, LOW);
            break;
        case 1:
            dutyCycle2 = 255;
            ledcWrite(pwmChannel2, dutyCycle2);
            digitalWrite(m2bw, LOW);
            digitalWrite(m2, HIGH);
    }
}

void AdjustMotor1() {
    dutyCycle1 = 225;
    digitalWrite(m1, HIGH);
    digitalWrite(m1bw, LOW);
    ledcWrite(pwmChannel1, dutyCycle1);   
}

void AdjustMotor2() {
    dutyCycle2 = 225;
    digitalWrite(m2, HIGH);
    digitalWrite(m2bw, LOW);
    ledcWrite(pwmChannel2, dutyCycle2);   
}