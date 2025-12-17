#ifndef TEMPERATURE_MONITOR_H
#define TEMPERATURE_MONITOR_H

#include "app.hpp"
#include "ledActuator.hpp"
#include "temperatureSensor.hpp"

// Temperature monitor application class
class temperatureMonitor : public app {
private:
    ledActuator* redLED;
    ledActuator* yellowLED;
    ledActuator* greenLED;
    temperatureSensor* tempSensor;

    void switchLEDs(bool red, bool yellow, bool green);

public:
    temperatureMonitor(systemManager& sysManager);
    ~temperatureMonitor() override = default;

    void init() override;
    void cyclic() override;
    void terminate() override;
};

#endif // TEMPERATURE_MONITOR_H