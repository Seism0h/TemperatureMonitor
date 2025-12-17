#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include "sensor.hpp"
#include <cstdint>

class temperatureSensor : public sensorInterface<uint16_t, int16_t> {
private:
    int16_t scaling; // scaling factor, which is actually a scaling divisor     

    void scale(); // scale before returning the value

public:
    temperatureSensor(int16_t scaling = 1);
    ~temperatureSensor() override = default;
    
    int16_t read() override;

};

#endif // TEMPERATURE_SENSOR_H