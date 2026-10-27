#pragma once

#include <cstdint>

#include <PX4Flow.h>

struct PX4FlowVector2 {
	float x = 0.0f;
	float y = 0.0f;
	uint32_t timestampMicros = 0;
};

struct PX4FlowReading {
    PX4FlowVector2 rate;
    PX4FlowVector2 flow;
    int integrationTimespanMicros = 0;
    int sensorGroundDistanceMm = 0;
    int quality = 0;
};




// This is a mess of example code pieces from the example files in the PX4Flow library. 
// It's here so I remember it exists while making this part.

/*
#define PARAM_FOCAL_LENGTH_MM 16

float focal_length_px = (PARAM_FOCAL_LENGTH_MM) / (4.0f * 6.0f) * 1000.0f;
  
// Initialize PX4Flow library
PX4Flow sensor = PX4Flow(); 

void loop()
{
  long loop_start = millis();
  
  if (loop_start - last_check > 100) {
    // Fetch I2C data  
    sensor.update_integral();
    x_rate = sensor.gyro_x_rate_integral() / 10.0f;       // mrad
    y_rate = sensor.gyro_y_rate_integral() / 10.0f;       // mrad
    flow_x = sensor.pixel_flow_x_integral() / 10.0f;      // mrad
    flow_y = sensor.pixel_flow_y_integral() / 10.0f;      // mrad  
    int timespan = sensor.integration_timespan();               // microseconds
    int ground_distance = sensor.ground_distance_integral();    // mm
    int quality = sensor.quality_integral();
    
    if (quality > 100)
    {
      // Update flow rate with gyro rate
      float pixel_x = flow_x + x_rate; // mrad
      float pixel_y = flow_y + y_rate; // mrad
      
      // Scale based on ground distance and compute speed
      // (flow/1000) * (ground_distance/1000) / (timespan/1000000)
      float velocity_x = pixel_x * ground_distance / timespan;     // m/s
      float velocity_y = pixel_y * ground_distance / timespan;     // m/s 
    }
    
    last_check = loop_start;   
  }
}
 */