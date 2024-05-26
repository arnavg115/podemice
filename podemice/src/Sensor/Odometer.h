#ifndef ODOMETER
#define ODOMETER

void OdoSetup(int pin1, int pin2);

// returns dist travelled since last reset in cm/s
float OdoLoop(unsigned long deltaMillis, float *disp_x, float *disp_y, float gyro_z, int *wheel1, int *wheel2);
#endif