#pragma once

#include <cstdint>

#include <PX4Flow.h>

struct PX4FlowVector2 {
	float x = 0.0f;
	float y = 0.0f;
	uint32_t timestampMicros = 0;
};

struct PX4FlowReading {
	PX4FlowVector2 gyroRate;
	PX4FlowVector2 pixelFlow;
	PX4FlowVector2 velocityCalculated;
	int integrationTimespanMicros = 0;
	int sensorGroundDistanceMm = 0;
	int quality = 0;
};

struct PX4FlowStatus {
	bool Ready = false;
	int Error = 0;
};

class PX4FlowSensor {
public:
	bool begin(float focalLengthMm);
	bool read(PX4FlowReading& reading);
	const PX4FlowStatus& status() const;

private:
	PX4Flow px4flow;
	PX4FlowStatus currentStatus{};
};