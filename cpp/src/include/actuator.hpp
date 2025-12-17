#ifndef ACTUATOR_H
#define ACTUATOR_H

#include "sensor.hpp"

// Abstract base class
class actuator {
public:
    virtual ~actuator() = default;
};

template <typename ActuatorType, typename SensorInputType, typename SensorOutputType>
class actuatorInterface : public actuator, public sensorInterface<SensorInputType, SensorOutputType> {
public:
    virtual ~actuatorInterface() = default;
    
    virtual void write(ActuatorType value) = 0;
};

#endif // ACTUATOR_H