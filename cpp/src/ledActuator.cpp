#include "include/ledActuator.hpp"

// Constructor
ledActuator::ledActuator(){}

// write value to the actuator (LED)
void ledActuator::write(bool value) {

    updateRawValue(value); // update raw value as well
    sensorValue = rawValue;

}

// read the current state of the LED
bool ledActuator::read() {
    
    return sensorValue;
}