#ifndef SYSTEMINTERNALS_H
#define SYSTEMINTERNALS_H

#include <stdint.h>
#include <stdbool.h>

// Internal system struct for ADC values
typedef struct {
    uint16_t value;
} adcValue_t;

// Internal system struct for bit values
typedef struct {
    bool value;
} bitValue_t;

// Hardware specification struct
typedef struct {
    uint8_t rev;
    char name[7];
} hwSpec_t;

// Union for hardware specification and raw bytes
typedef union {
    hwSpec_t spec;
    uint8_t eepromData[8];
} hwSpecUnion_t;

volatile adcValue_t tempSensor;
volatile bitValue_t ledGreen;
volatile bitValue_t ledYellow;
volatile bitValue_t ledRed;
hwSpecUnion_t hwSpecUnion;
#endif // SYSTEMINTERNALS_H