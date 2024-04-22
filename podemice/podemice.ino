#include "Gyro.h";
#include "Wire.h";


void setup(){
  Wire.begin();
  Serial.begin(9600);
  GyroSetup();
}

void loop(){
  Serial.print("Orientation: ");
  Serial.println(GyroLoop());
}