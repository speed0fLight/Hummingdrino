#include "IMU.h"

// Initialize the IMU. Returns true if successful, otherwise false.
bool IMU::begin() {
	currentStatus = {};
	hasMpu6050Sample = false;
	hasQmc5883lSample = false;
	currentStatus.mpu6050Error =
		mpu6050.init(mpu6050Calibration, MPU6050_DEFAULT_ADDRESS);
	currentStatus.mpu6050Ready = currentStatus.mpu6050Error == 0;

	currentStatus.qmc5883lError =
		qmc5883l.init(qmc5883lCalibration, QMC5883L_DEFAULT_ADDRESS);
	currentStatus.qmc5883lReady = currentStatus.qmc5883lError == 0;

	return currentStatus.mpu6050Ready;
}

// Read the latest IMU data into the provided structure. Returns true if successful, otherwise false.
bool IMU::read(IMUReading& reading) {
	reading = {};
	if (!currentStatus.mpu6050Ready) {
		return false;
	}

	AccelData acceleration{};
	GyroData angularRate{};
	mpu6050.update();
	mpu6050.getAccel(&acceleration);
	mpu6050.getGyro(&angularRate);
	hasMpu6050Sample |= acceleration.timestamp != 0;

	reading.acceleration = {
		acceleration.accelX,
		acceleration.accelY,
		acceleration.accelZ,
		acceleration.timestamp,
	};
	reading.angularRate = {
		angularRate.gyroX,
		angularRate.gyroY,
		angularRate.gyroZ,
		angularRate.timestamp,
	};
	reading.accelerationAndAngularRateValid = hasMpu6050Sample;

	if (currentStatus.qmc5883lReady) {
		MagData magneticField{};
		qmc5883l.update();
		qmc5883l.getMag(&magneticField);
		hasQmc5883lSample |= magneticField.timestamp != 0;
		reading.magneticField = {
			magneticField.magX,
			magneticField.magY,
			magneticField.magZ,
			magneticField.timestamp,
		};
		reading.magneticFieldValid = hasQmc5883lSample;
	}

	return true;
}

const IMUStatus& IMU::status() const {
	return currentStatus;
}