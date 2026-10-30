#include <Arduino.h>

#include "PX4Flow.h"

// Initialize the PX4Flow sensor; integral readings are angular, so focal length is not used.
bool PX4FlowSensor::begin(float focalLengthMm) {
	(void)focalLengthMm;

	currentStatus = {};
	px4flow = PX4Flow();

	if (!px4flow.update_integral()) {
		currentStatus.Error = 1;
		return false;
	}

	currentStatus.Ready = true;
	return true;
}

// Read the latest frame into the provided structure. Returns true if successful, otherwise false.
bool PX4FlowSensor::read(PX4FlowReading& reading) {
	reading = {};
	if (!currentStatus.Ready) {
		return false;
	}

	if (!px4flow.update_integral()) {
		currentStatus.Error = 1;
		return false;
	}

	const uint32_t timestampMicros = micros();
	const float gyroX = px4flow.gyro_x_rate_integral() / 10.0f;
	const float gyroY = px4flow.gyro_y_rate_integral() / 10.0f;
	const float flowX = px4flow.pixel_flow_x_integral() / 10.0f;
	const float flowY = px4flow.pixel_flow_y_integral() / 10.0f;
	const uint32_t integrationTimespan = px4flow.integration_timespan();
	const int groundDistance = px4flow.ground_distance_integral();

	reading.gyroRate = {gyroX, gyroY, timestampMicros};
	reading.pixelFlow = {flowX, flowY, timestampMicros};
	reading.integrationTimespanMicros =
		static_cast<int>(integrationTimespan);
	reading.sensorGroundDistanceMm = groundDistance;
	reading.quality = px4flow.quality_integral();

	if (reading.quality > 100 && groundDistance > 0 &&
		integrationTimespan > 0) {
		reading.velocityCalculated = {
			(flowX + gyroX) * groundDistance / integrationTimespan,
			(flowY + gyroY) * groundDistance / integrationTimespan,
			timestampMicros,
		};
	}

	currentStatus.Error = 0;
	return true;
}

const PX4FlowStatus& PX4FlowSensor::status() const {
	return currentStatus;
}
