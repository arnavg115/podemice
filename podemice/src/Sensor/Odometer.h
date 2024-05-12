#ifndef ODOMETER
#define ODOMETER
void OdoSetup(int pin1/*, int pin2*/);

// returns dist travelled since last reset in cm/s
float OdoLoop(unsigned long deltaMillis);
#endif