#include "Arduino.h"
#include "Motors.h"

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
    m1 = 25; // p1;
    m1bw = 32; // n1;
    m1enable = 33; // e1;
    m2 = 27; // p2;
    m2bw = 26; // n2;
    m2enable = 15; // e2;

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

void ToggleMotor1(int dir) {
    switch (dir) {
        case -1:
            dutyCycle1 = 255 * .98;
            ledcWrite(pwmChannel1, dutyCycle1);
            digitalWrite(m1bw, HIGH);
            digitalWrite(m1, LOW);
            break;
        case 0:
            digitalWrite(m1bw, LOW);
            digitalWrite(m1, LOW);
            break;
        case 1:
            dutyCycle1 = 255 * .98;
            ledcWrite(pwmChannel1, dutyCycle1);
            digitalWrite(m1bw, LOW);
            digitalWrite(m1, HIGH);
    }
}

void ToggleMotor2(int dir) {
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

void AdjustMotor1(int cycle) {
    dutyCycle1 = cycle * .98;
    digitalWrite(m1, HIGH);
    digitalWrite(m1bw, LOW);
    ledcWrite(pwmChannel1, dutyCycle1);   
}

void AdjustMotor2(int cycle) {
    dutyCycle2 = cycle;
    digitalWrite(m2, HIGH);
    digitalWrite(m2bw, LOW);
    ledcWrite(pwmChannel2, dutyCycle2);   
}

void AdjustMotor1B(int cycle) {
    dutyCycle1 = cycle * .98;
    digitalWrite(m1bw, HIGH);
    digitalWrite(m1, LOW);
    ledcWrite(pwmChannel1, dutyCycle1);   
}

void AdjustMotor2B(int cycle) {
    dutyCycle2 = cycle;
    digitalWrite(m2bw, HIGH);
    digitalWrite(m2, LOW);
    ledcWrite(pwmChannel2, dutyCycle2);   
}