#include "Arduino.h"

int m1 = 2;
int m2 = 3;
unsigned long startTime = -1;

void MotorSetup(int p1, int p2){
    m1 = p1;
    m2 = p2;
    pinMode(m1, OUTPUT);
    pinMode(m2, OUTPUT);
}

void RunMotorFor(unsigned long time, unsigned long duration){
  if(startTime == -1){
    startTime = time;
  }
  if((time - startTime)< duration){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, HIGH);
  } else {
    startTime = -1;
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
  }

}