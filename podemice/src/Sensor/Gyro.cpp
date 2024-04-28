#include "Wire.h"
#include "I2C.h"
#include "Arduino.h"

#define MPU9250_IMU_ADDRESS 0x68
#define MPU9250_MAG_ADDRESS 0x0C
 
#define GYRO_FULL_SCALE_250_DPS  0x00
#define GYRO_FULL_SCALE_500_DPS  0x08
#define GYRO_FULL_SCALE_1000_DPS 0x10
#define GYRO_FULL_SCALE_2000_DPS 0x18
 
#define ACC_FULL_SCALE_2G  0x00
#define ACC_FULL_SCALE_4G  0x08
#define ACC_FULL_SCALE_8G  0x10
#define ACC_FULL_SCALE_16G 0x18
 
#define TEMPERATURE_OFFSET 21 // As defined in documentation
 
#define INTERVAL_MS_PRINT 100
 
#define G 9.80665
 
struct gyroscope_raw {
  int16_t x, y, z;
} gyroscope;
 
struct accelerometer_raw {
  int16_t x, y, z;
} accelerometer;
  
struct {
  struct {
    float x, y, z;
  } accelerometer, gyroscope;
 
} normalized;
 
float o_sum;
float v_sum;
int iters;
static float o_noise = 0;
static float v_noise = 0;
float orientation = 0;
float velocity = 0;

bool isImuReady()
{
  uint8_t isReady; // Interruption flag

  I2Cread(MPU9250_IMU_ADDRESS, 58, 1, &isReady);

  return isReady & 0x01; // Read register and wait for the RAW_DATA_RDY_INT
}

void readRawImu()
{
  uint8_t buff[14];

  // Read output registers:
  // [59-64] Accelerometer
  // [67-72] Gyroscope
  I2Cread(MPU9250_IMU_ADDRESS, 59, 14, buff);

  // Accelerometer, create 16 bits values from 8 bits data
  accelerometer.x = (buff[0] << 8 | buff[1]);
  accelerometer.y = (buff[2] << 8 | buff[3]);
  accelerometer.z = (buff[4] << 8 | buff[5]);

  // Gyroscope, create 16 bits values from 8 bits data
  gyroscope.x = (buff[8] << 8 | buff[9]);
  gyroscope.y = (buff[10] << 8 | buff[11]);
  gyroscope.z = (buff[12] << 8 | buff[13]);
}

void normalize(gyroscope_raw gyroscope)
{
  // Sensitivity Scale Factor (MPU datasheet page 8)
  normalized.gyroscope.x = gyroscope.x / 32.8;
  normalized.gyroscope.y = gyroscope.y / 32.8;
  normalized.gyroscope.z = gyroscope.z / 32.8;
}

void normalize(accelerometer_raw accelerometer)
{
  // Sensitivity Scale Factor (MPU datasheet page 9)
  normalized.accelerometer.x = accelerometer.x * G / 16384;
  normalized.accelerometer.y = accelerometer.y * G / 16384;
  normalized.accelerometer.z = accelerometer.z * G / 16384;
}

float o_lowPass (float in, float val) {
  if (abs(in) < val) {
    return 0;
  }
  return in;
}

void GyroSetup()
{
  o_sum = 0;
  v_sum = 0;
  iters = 0;

  I2CwriteByte(MPU9250_IMU_ADDRESS, 27, GYRO_FULL_SCALE_1000_DPS); // Configure gyroscope range
  I2CwriteByte(MPU9250_IMU_ADDRESS, 28, ACC_FULL_SCALE_2G);        // Configure accelerometer range
 
  I2CwriteByte(MPU9250_IMU_ADDRESS, 55, 0x02); // Set by pass mode for the magnetometers
  I2CwriteByte(MPU9250_IMU_ADDRESS, 56, 0x01); // Enable interrupt pin for raw data
 
  //Start magnetometer
  I2CwriteByte(MPU9250_MAG_ADDRESS, 0x0A, 0x12); // Request continuous magnetometer measurements in 16 bits (mode 1)
}
 
float GyroLoop(unsigned long currentMillis, unsigned long deltaMillis)
{
  float result[2];
  if (isImuReady()) {
    readRawImu();
 
    normalize(gyroscope);
    normalize(accelerometer);
  }

  if (currentMillis < 5000) {
    o_sum += normalized.gyroscope.z;
    v_sum += normalized.accelerometer.x;
    iters++;
  } else if (!o_noise) {
    o_noise += o_sum / iters;
    v_noise += v_sum / iters;
  } else {
    orientation += o_lowPass(normalized.gyroscope.z - o_noise, 0.5) * (deltaMillis / 1000.0);
    velocity += (normalized.accelerometer.z - v_noise) * (deltaMillis / 1000);
  }

  //result[1] = orientation;
  //result[2] = velocity;
  
  return orientation;
}