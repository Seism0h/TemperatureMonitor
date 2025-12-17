#ifndef HARDWAREINTERFACE_H
#define HARDWAREINTERFACE_H

#include <stdint.h>
#include <stdbool.h>
#include "systemDefinition.h"

// Data structures
// Temperature sensor structure
typedef struct {
    int16_t value;
} temperatureSensor_t; 

// LED state structure
typedef struct {
    bool state;
} ledState_t; // LED state structure

// LED request structure
typedef struct {
    bool state;
} ledRequest_t; // LED request structure

// Function prototypes
void setLED(uint8_t number, ledRequest_t request);

// Reads the temperature sensor value and adjusts based on hardware revision
void readTempSensor(temperatureSensor_t* sensor);

// Reads the state of the specified LED
void readLEDState(ledState_t* led, uint8_t number);

// Reads hardware specifications from EEPROM
void eepromRead(uint8_t dest[8]);

#endif // HARDWAREINTERFACE_H