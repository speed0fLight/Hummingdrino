/*
#include <Arduino.h>
#include <Wire.h>

#include "sensors/IMU.h"

// put function declarations here:
int myFunction(int, int);

static IMU imu;
static IMUReading latestImuReading;
static bool imuReady = false;

// Setup the gyro, compass, accelerometer
void setup() {
  Serial1.begin(115200);
  Wire.begin();
  Wire.setClock(400000);



  // Run inits and set init ready states
  imuReady = imu.begin();

  // Check states and explode if not ready (or just try something again)
  if (!imuReady)
  {
    Serial1.println("Failed to initialize inertial measurement unit.");

    return;
  }
}

// put function definitions here:



int iterateSystems() {
  
   // ------ IMU (Gyro + Accelerometer + Compass + Barometer) ------
  if (!imu.read(latestImuReading)) {
    imuReady = false;
    Serial1.println("IMU read fail.");
  } else {
    Serial1.println("IMU reading acceleration: " + String(latestImuReading.acceleration.x) + ", " + String(latestImuReading.acceleration.y) + ", " + String(latestImuReading.acceleration.z));
    Serial1.println("IMU reading angular rate: " + String(latestImuReading.angularRate.x) + ", " + String(latestImuReading.angularRate.y) + ", " + String(latestImuReading.angularRate.z));
  }

  return 0;
}

void loop() {


  iterateSystems();


  
}
*/