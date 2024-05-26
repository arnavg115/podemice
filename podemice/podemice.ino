#include "Sensors.h"
#include "Wire.h"
#include "API.h"
#include "Motors.h"

unsigned long lastPrintMillis = 0;
int iter = 0;

void setup(){
  Wire.begin();
  Serial.begin(9600);
  while (!Serial)
  {
  }
  int pins[] = {18, 4, 5, 19, 23, 32, 33, 25, 26, 27, 33, 12, 13, 14};
  SensorSetup(pins);
  MotorSetup(32, 25, 33, 26, 27, 15);
}

void loop(){
  unsigned long currentMillis = millis();
  unsigned long deltaMillis = currentMillis - lastPrintMillis;
  if(deltaMillis > 3){
    Sensors a = SensorStep(currentMillis, deltaMillis);
    iter++;
    if (iter % 200 == 0) {
      //Serial.print("Orientation: ");
      //Serial.println(a.gyro_z);
      Serial.print(" , IR: ");
      Serial.println(a.ir_sensor);
      //Serial.print(" , Ultrasonic: ");
      //Serial.print(a.ultrasonic1);
      //Serial.print(" and ");
      //Serial.println(a.ultrasonic2);
      //Serial.print(" , Odometer: ");
      //Serial.println(a.displacement);
      iter = 0;
    }
    lastPrintMillis = a.last_print_mil;
    ControlStep(a);
   }
}