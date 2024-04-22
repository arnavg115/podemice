#include "Arduino.h"

static int pinNum = 5;

void IRSetup(int pin){
  pinNum = pin;
  pinMode(pinNum, INPUT);
}

// returns 1 if surface is closer than threshold, 0 otherwise
int IRLoop(){
    return 1-digitalRead(pinNum);
}