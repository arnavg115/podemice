#include "Sensors.h"
#include "Wire.h"
#include "API.h"

unsigned long lastPrintMillis = 0;
int iter = 0;

void setup(){
  Wire.begin();
  Serial.begin(9600);
  while (!Serial)
  {
  }
  int pins[] = {18, 5, 4, 19, 23, 32, 33, 25, 26, 27, 33, 15, 13, 14};
  SensorSetup(pins);
}

void loop(){
  unsigned long currentMillis = millis();
   unsigned long deltaMillis = currentMillis - lastPrintMillis;
   if(deltaMillis > 10){
    Sensors a = SensorStep(currentMillis, deltaMillis);
    iter++;
    if (iter % 10 == 0) {
      Serial.print("Orientation: ");
      Serial.println(a.gyro_z);
      Serial.print(" , IR: ");
      Serial.println(a.ir_sensor);
      Serial.print(" , Ultrasonic: ");
      Serial.println(a.ultrasonic1);
      Serial.print(" and ");
      Serial.println(a.ultrasonic2);
      Serial.print(" , Odometer: ");
      Serial.println(a.displacement);
      iter = 0;
    }
    lastPrintMillis = a.last_print_mil;
   }
}