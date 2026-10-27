#include <Arduino.h>
#include <Wire.h>

#include "sensors/IMU.h"

// put function declarations here:
int myFunction(int, int);

static IMU imu;
static IMUReading latestImuReading;
static bool imuReady = false;

void setup() {
  Serial3.begin(115200);
  Wire.begin();
  Wire.setClock(400000);

  /*
  Solo module setup and initialization.
  Shitfuck configs from config file into setup functions.
  */

  // Rn we hardware test yippie!!1!1!

  imuReady = imu.begin();
  const IMUStatus& imuStatus = imu.status();
  if (!imuStatus.mpu6050Ready) {
    Serial3.print("MPU6050 initialization failed: ");
    Serial3.println(imuStatus.mpu6050Error);
  }
  if (!imuStatus.qmc5883lReady) {
    Serial3.print("QMC5883L initialization failed: ");
    Serial3.println(imuStatus.qmc5883lError);
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
  if (!imuReady) {
    delay(100);
    return;
  }

  if (!imu.read(latestImuReading)) {
    imuReady = false;
    Serial3.println("IMU read fail.");
  } else {
    Serial3.println("IMU reading acceleration: " + String(latestImuReading.acceleration.x) + ", " + String(latestImuReading.acceleration.y) + ", " + String(latestImuReading.acceleration.z));
    Serial3.println("IMU reading angular rate: " + String(latestImuReading.angularRate.x) + ", " + String(latestImuReading.angularRate.y) + ", " + String(latestImuReading.angularRate.z));
  }
  
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}