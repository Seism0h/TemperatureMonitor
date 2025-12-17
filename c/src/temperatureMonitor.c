#include "include/temperatureMonitor.h"

// Cyclic temperature monitoring function
void temperatureMonitorCyclic(void) {
    temperatureSensor_t temp;
    readTempSensor(&temp);

    bool green = false, yellow = false, red = false;

    if (temp.value >= 105 || temp.value < 5) {
        red = true;
    } else if (temp.value >= 85 && temp.value < 105) {
        yellow = true;
    } else {
        green = true;
    }

    switchLEDS(green, yellow, red);
}

// Sets the state of the three LEDs based on the provided boolean values
void switchLEDS(bool green, bool yellow, bool red) {
    ledRequest_t ledGreenReq = { .state = green };
    ledRequest_t ledYellowReq = { .state = yellow };
    ledRequest_t ledRedReq = { .state = red };

    setLED(0, ledGreenReq);   // 0: Green
    setLED(1, ledYellowReq);  // 1: Yellow
    setLED(2, ledRedReq);     // 2: Red
}