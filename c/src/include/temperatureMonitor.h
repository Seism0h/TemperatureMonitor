#ifndef TEMPERATUREMONITOR_H
#define TEMPERATUREMONITOR_H

#include <stdint.h>
#include <stdbool.h>
#include "hardwareInterfaces.h"

// Function prototypes
// Cyclic temperature monitoring function
void temperatureMonitorCyclic(void);

// Sets the state of the three LEDs based on the provided boolean values
void switchLEDS(bool green, bool yellow, bool red);

#endif // TEMPERATUREMONITOR_H