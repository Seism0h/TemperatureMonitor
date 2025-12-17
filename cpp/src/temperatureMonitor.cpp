#include "include/temperatureMonitor.hpp"

temperatureMonitor::temperatureMonitor(systemManager& sysManager)
    : app(sysManager)
{
    // Here we obtain the LEDs from the system manager as actuators
    redLED = dynamic_cast<ledActuator*>(sysManager.getActuator(0));
    yellowLED = dynamic_cast<ledActuator*>(sysManager.getActuator(1));
    greenLED = dynamic_cast<ledActuator*>(sysManager.getActuator(2));

    // Here we obtain the temperature sensor from the system manager as a sensor
    tempSensor = dynamic_cast<temperatureSensor*>(sysManager.getSensor(0));
}

// Wrapper to turn on LEDs in a nice fashion
void temperatureMonitor::switchLEDs(bool red, bool yellow, bool green) {

    redLED->write(red);
    yellowLED->write(yellow);
    greenLED->write(green);
}

// Initialize all LEDs to off
void temperatureMonitor::init() {
    
    switchLEDs(false, false, false);
}

// Implement LED logic
void temperatureMonitor::cyclic() {
    int16_t temperature = tempSensor->read();
    // Implement LED logic
    if (temperature >= 105 || temperature < 5) {
        switchLEDs(true, false, false);
    } else if (temperature >= 85 && temperature < 105) {
        switchLEDs(false, true, false);
    } else {
        switchLEDs(false, false, true);
    }
}

void temperatureMonitor::terminate() {
    // Turn off LEDS when finished
    switchLEDs(false, false, false);
}