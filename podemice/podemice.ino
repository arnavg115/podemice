#include "Sensor.h"
#include "Wire.h"
#include "Control.h"


void setup(){
  Wire.begin();
  Serial.begin(9600);
  int pins[] = {5,7,8,9,10};
  SensorSetup(pins);
}

void loop(){
  Serial.print("Orientation: ");
  Sensors a = SensorStep();
  Serial.print(a.gyro_z);
  Serial.print(" , IR: ");
  Serial.println(a.ir_sensor);
  Serial.print(", Ultrasonics: ");
  Serial.print(a.ultrasonic1);
  Serial.print(", and ");
  Serial.println(a.ultrasonic2);
}