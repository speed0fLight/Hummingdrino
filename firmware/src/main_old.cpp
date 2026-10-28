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

  /*
  Solo module setup and initialization.
  Shitfuck configs from config file into setup functions.
  */

  // Run inits and set init ready states
  imuReady = imu.begin();

  // Check states and explode if not ready (or just try something again)
  if (!imuReady)
  {
    Serial1.println("Failed to initialize inertial measurement unit.");

    return;
  }
}

void loop() {
  /*
  Run each module with inputs and outputs funnily (new verity variant)
  Do we run safety checks here before outputting to motors?
  I think a failsafe module with all safety checks is best.
  It can compile all required info to output to motors + all relevant safety from other modules.
  This will dictate if it wants to enable motors or not and forward to motors its output.
  */

  iterateSystems();


  
}

// put function definitions here:


 /*
  * iterateSystems: **Important**! This function iterates through
  * the flight controller components (IMU) and retrieves data.
  * Error codes and behavior
  * Error 2 - Reset the loop
  *
  */
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

