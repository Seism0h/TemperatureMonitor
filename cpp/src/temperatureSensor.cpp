#include "include/temperatureSensor.hpp"

// Constructor
temperatureSensor::temperatureSensor(int16_t scaling)
    : scaling(scaling) {
        rawValue = 0;
        sensorValue = 0;
}

// Read the scaled temperature value
int16_t temperatureSensor::read() {
    scale();
    return sensorValue;
}

// Scale the raw value using the scaling factor
void temperatureSensor::scale() {
    sensorValue = static_cast<int16_t>(rawValue / scaling);
}