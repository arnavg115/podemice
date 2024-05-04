#include "Arduino.h"
#include "Ultrasonic.h"

int trigPin1;
int trigPin2;
int echoPin1;
int echoPin2;

float duration1;
float duration2;

float distance1;
float distance2;

struct Ultrasonic ultrasonic;

void UltrasonicSetup(int pin1, int pin2, int pin3, int pin4) {
    trigPin1 = pin1;
    echoPin1 = pin2;
    trigPin2 = pin3;
    echoPin2 = pin4;

	pinMode(trigPin1, OUTPUT);  
	pinMode(echoPin1, INPUT);

    // pinMode(trigPin2, OUTPUT);  
	// pinMode(echoPin2, INPUT);
}

Ultrasonic UltrasonicStep() {
    digitalWrite(trigPin1, LOW);  
	// digitalWrite(trigPin2, LOW);  
	delayMicroseconds(2);  
	digitalWrite(trigPin1, HIGH);  
	// digitalWrite(trigPin2, HIGH);  
	delayMicroseconds(10);  
	digitalWrite(trigPin1, LOW);  
	// digitalWrite(trigPin2, LOW);  

    duration1 = pulseIn(echoPin1, HIGH, 5000);  
    // duration2 = pulseIn(echoPin2, HIGH);  

    distance1 = (duration1 * .0343)/2;  
    // distance2 = (duration2 * .0343)/2;  

    ultrasonic.u1 = distance1;
    // ultrasonic.u2 = distance2;
    
    return ultrasonic;
}
 