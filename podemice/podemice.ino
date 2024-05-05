#include "Sensors.h"
#include "Wire.h"
// #include "Control.h"
#include "API.h"

unsigned long lastPrintMillis = 0;
int iter = 0;

void setup(){
  Wire.begin();
  Serial.begin(9600);
  while (!Serial)
  {
  }
  int pins[] = {18,4,5,19,23, 32, 33};
  SensorSetup(pins);
  //ControlSetup(pins);
}

void loop(){
  unsigned long currentMillis = millis();
   unsigned long deltaMillis = currentMillis - lastPrintMillis;
   if(deltaMillis > 10){
    Sensors a = SensorStep(currentMillis, deltaMillis);
    iter++;
    if (iter % 10 == 0) {
      Serial.print("Orientation: ");
      Serial.print(a.gyro_z);
      Serial.print(" , IR: ");
      Serial.println(a.ir_sensor);
      Serial.print(" , Ultrasonic: ");
      Serial.println(a.ultrasonic1);
      iter = 0;
    }
    /*Serial.print(", Ultrasonics: ");
    Serial.print(a.ultrasonic1);
    Serial.print(", and ");
    Serial.println(a.ultrasonic2);*/
    lastPrintMillis = a.last_print_mil;
   }
}