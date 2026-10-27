#pragma once

#include <cstdint>

#include <FastIMU.h>

struct IMUVector3 {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	uint32_t timestampMicros = 0;
};

struct IMUReading {
    // IMU acceleration Vector3. Not sure what unit the library returns or if it needs manual calibration yet.
	IMUVector3 acceleration;
    // IMU angular rate Vector3. Not sure what unit the library returns or if it needs manual calibration yet.
	IMUVector3 angularRate;
    // IMU magnetic field Vector3. This only exists if the magnometer is present and can be used for a compass heading.
	IMUVector3 magneticField;
	// Valid after the first sample; check timestamps separately for freshness.
	bool accelerationAndAngularRateValid = false;
	bool magneticFieldValid = false;
};

struct IMUStatus {
	bool mpu6050Ready = false;
	int mpu6050Error = 0;
	bool qmc5883lReady = false;
	int qmc5883lError = 0;
};

class IMU {
public:
	bool begin();
	bool read(IMUReading& reading);
	int getErrorStatus();
	const IMUStatus& status() const;

private:
	MPU6050 mpu6050;
	QMC5883L qmc5883l;
	calData mpu6050Calibration{};
	calData qmc5883lCalibration{};
	IMUStatus currentStatus{};
	bool hasMpu6050Sample = false;
	bool hasQmc5883lSample = false;
};