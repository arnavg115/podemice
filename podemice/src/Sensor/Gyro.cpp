#include "Wire.h"
#include "MPU9250.h"
#include "Arduino.h"

#define RAD_TO_DEG 57.295779513082320876798154814105

float sum;
int iters;
static float noise = 0;
float orientation = 0;

MPU9250 IMU(i2c0, 0x68);
int gyro_status;

void GyroSetup() {
    Wire.begin();
    gyro_status = IMU.begin();
    if (gyro_status < 0) {
        Serial.println("IMU initialization unsuccessful");
        Serial.println("Check IMU wiring or try cycling power");
        Serial.print("Status: ");
        Serial.println(gyro_status);
        while (1) {}
    }
    // setting the accelerometer full scale range to +/-8G
    IMU.setAccelRange(MPU9250::ACCEL_RANGE_2G);
    // setting the gyroscope full scale range to +/-500 deg/s
    IMU.setGyroRange(MPU9250::GYRO_RANGE_250DPS);
    // setting DLPF bandwidth to 20 Hz
    IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_41HZ);
    // setting SRD to 19 for a 50 Hz update rate
    // IMU.setSrd(19);
    IMU.calibrateMag();
}

float lowPass (float in, float val) {
    if (abs(in) < val) {
        return 0;
    }
    return in;
}

float GyroLoop(unsigned long currentMillis,  unsigned long deltaMillis) {
    
    IMU.readSensor();

    /*Serial.print("ang velo: ");
    Serial.println(IMU.getGyroZ_rads() * RAD_TO_DEG);
    Serial.print("\n");*/

    orientation += (lowPass((IMU.getGyroZ_rads() * RAD_TO_DEG), 0.1) * (deltaMillis / 1000.0)) * 1.2;

 
    return orientation;
}