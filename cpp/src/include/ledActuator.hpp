#ifndef LED_ACTUATOR_H
#define LED_ACTUATOR_H

#include "actuator.hpp"

class ledActuator : public actuatorInterface<bool, bool, bool> { // ActuatorType is bool (on/off), SensorInputType is bool, SensorOutputType is bool
public:
    ledActuator();
    ~ledActuator() override = default;
    
    void write(bool value) override;
    bool read() override; 
};

#endif // LED_ACTUATOR_H